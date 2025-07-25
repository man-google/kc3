/* kc3
 * Copyright from 2022 to 2025 kmx.io <contact@kmx.io>
 *
 * Permission is hereby granted to use this software granted the above
 * copyright notice and this permission paragraph are included in all
 * copies and substantial portions of this software.
 *
 * THIS SOFTWARE IS PROVIDED "AS-IS" WITHOUT ANY GUARANTEE OF
 * PURPOSE AND PERFORMANCE. IN NO EVENT WHATSOEVER SHALL THE
 * AUTHOR BE CONSIDERED LIABLE FOR THE USE AND PERFORMANCE OF
 * THIS SOFTWARE.
 */
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "assert.h"
#include "alloc.h"
#include "buf.h"
#include "buf_file.h"
#include "endian.h"
#include "file.h"
#include "ht.h"
#include "sym.h"
#include "list.h"
#include "str.h"
#include "tag.h"
#include "tag_init.h"
#include "types.h"
#include "marshall.h"

#define DEF_MARSHALL(type)                                             \
  s_marshall * marshall_ ## type (s_marshall *m, bool heap, type src)  \
  {                                                                    \
    s_buf *buf;                                                        \
    type le;                                                           \
    sw r;                                                              \
    assert(m);                                                         \
    le = _Generic(src,                                                 \
                  s16:     htole16(src),                               \
                  u16:     htole16(src),                               \
                  s32:     htole32(src),                               \
                  u32:     htole32(src),                               \
                  s64:     htole64(src),                               \
                  u64:     htole64(src),                               \
                  default: src);                                       \
    buf = heap ? &m->heap : &m->buf;                                   \
    if ((r = buf_write_ ## type(buf, le)) <= 0)                        \
      return NULL;                                                     \
    if (heap)                                                          \
      m->heap_pos += r;                                                \
    else                                                               \
      m->buf_pos += r;                                                 \
    return m;                                                          \
  }

DEF_MARSHALL(bool)

s_marshall * marshall_heap_pointer (s_marshall *m, bool heap, void *p,
                                    bool *present)
{
  s_buf *buf;
  s_tag key = {0};
  sw r;
  s_tag tag = {0};
  u64 offset;
  assert(m);
  buf = heap ? &m->heap : &m->buf;
  tag_init_tuple(&key, 2);
  key.data.tuple.tag[0].data.u64 = (u64) p;
  if (ht_get(&m->ht, &key, &tag)) {
    *present = true;
    goto ok;
  }
  *present = false;
  tag_init_tuple(&tag, 2);
  tag.data.tuple.tag[0].data.u64 = (u64) p;
  tag.data.tuple.tag[0].type = TAG_U64;
  tag.data.tuple.tag[1].data.u64 =
    (u64) m->heap_pos + sizeof(s_marshall_header);
  tag.data.tuple.tag[1].type = TAG_U64;
  if (! ht_add(&m->ht, &tag))
    goto ko;
 ok:
  if (tag.type != TAG_TUPLE ||
      tag.data.tuple.count != 2 ||
      tag.data.tuple.tag[1].type != TAG_U64) {
    err_puts("marshall_heap_pointer: invalid offset in hash table");
    err_inspect_tag(&tag);
    err_write_1("\n");
    assert(! "marshall_heap_pointer: invalid offset in hash table");
    goto ko;
  }
  offset = tag.data.tuple.tag[1].data.u64;
  if ((r = buf_write_u64(buf, offset)) <= 0)
    goto ko;
  tag_clean(&key);
  tag_clean(&tag);
  if (heap) {
    m->heap_pos += r;
    m->heap_count++;
  }
  else
    m->buf_pos += r;
  return m;
 ko:
  tag_clean(&key);
  tag_clean(&tag);
  return NULL;
}

s_marshall * marshall_character (s_marshall *m, bool heap,
                                 character src)
{
  sw r;
  s_buf *buf;
  assert(m);
  buf = heap ? &m->heap : &m->buf;
  if ((r = buf_write_character_utf8(buf, src)) <= 0)
    return NULL;
  if (heap)
    m->heap_pos += r;
  else
    m->buf_pos += r;
  return m;
}

void marshall_clean (s_marshall *m)
{
  assert(m);
  buf_clean(&m->buf);
  buf_clean(&m->heap);
  ht_clean(&m->ht);
}

void marshall_delete (s_marshall *m)
{
  marshall_clean(m);
  free(m);
}

s_marshall * marshall_init (s_marshall *m)
{
  s_marshall tmp = {0};
  if (! ht_init(&tmp.ht, &g_sym_Tag, 1024) ||
    ! buf_init_alloc(&tmp.heap, 1024024))
    return NULL;
  if (! buf_init_alloc(&tmp.buf, 1024024)) {
    buf_delete(&tmp.heap);
    return NULL;
  }
  *m = tmp;
  return m;
}

s_marshall * marshall_list (s_marshall *m, bool heap,
                            const s_list *list)
{
  assert(m);
  assert(list);
  if (! marshall_tag(m, heap, &list->tag) ||
      ! marshall_tag(m, heap, &list->next))
    return NULL;
  return m;
}

s_marshall * marshall_plist (s_marshall *m, bool heap,
                             const p_list plist)
{
  assert(m);
  bool present = false;
  if (! m)
    return NULL;
  if (! marshall_heap_pointer(m, heap, plist, &present))
    return NULL;
  if (! present && plist)
    return marshall_list(m, true, plist);
  return m;
}

s_marshall * marshall_new (void)
{
  s_marshall *m;
  if (! (m = alloc(sizeof(s_marshall))))
    return NULL;
  if (marshall_init(m) == NULL) {
    free(m);
    return NULL;
  }
  return m;
}

DEF_MARSHALL(s8)
DEF_MARSHALL(s16)
DEF_MARSHALL(s32)
DEF_MARSHALL(s64)

s_marshall * marshall_str (s_marshall *m, bool heap, const s_str *src)
{
  sw r;
  s_buf *buf;
  
  assert(m);
  assert(src);
  if (! marshall_u32(m, heap, src->size))
    return NULL;
  if (! src->size)
    return m;
  buf = heap ? &m->heap : &m->buf;
  if ((r = buf_write(buf, src->ptr.pchar, src->size)) <= 0)
    return NULL;
  if (heap)
    m->heap_pos += r;
  else
    m->buf_pos += r;
  return m;
}

DEF_MARSHALL(sw)

s_marshall * marshall_tag (s_marshall *m, bool heap, const s_tag *tag)
{
  u8 type;
  assert(m);
  assert(tag);
  type = tag->type;
  marshall_u8(m, heap, type);
  switch (tag->type) {
  case TAG_VOID: return m;
  case TAG_ARRAY: return marshall_array(m, heap, &tag->data.array);
  case TAG_BOOL:  return marshall_bool(m, heap, tag->data.bool_);
  case TAG_CALL:  return marshall_call(m, heap, &tag->data.call);
  case TAG_CHARACTER:
    return marshall_character(m, heap, tag->data.character);
  case TAG_DO_BLOCK:
    return marshall_do_block(m, heap, &tag->data.do_block);
  case TAG_F32:   return marshall_f32(m, heap, tag->data.f32);
  case TAG_F64:   return marshall_f64(m, heap, tag->data.f64);
  case TAG_F128:  return marshall_f128(m, heap, tag->data.f128);
  case TAG_FACT:  return marshall_fact(m, heap, &tag->data.fact);
  case TAG_IDENT: return marshall_ident(m, heap, &tag->data.ident);
  case TAG_INTEGER:
    return marshall_integer(m, heap, &tag->data.integer);
  case TAG_MAP:   return marshall_map(m, heap, &tag->data.map);
  case TAG_PCALLABLE:
    return marshall_pcallable(m, heap, tag->data.pcallable);
  case TAG_PCOMPLEX:
    return marshall_pcomplex(m, heap, tag->data.pcomplex);
  case TAG_PCOW:  return marshall_pcow(m, heap, tag->data.pcow);
  case TAG_PLIST: return marshall_plist(m, heap, tag->data.plist);
  case TAG_PSTRUCT:
    return marshall_pstruct(m, heap, tag->data.pstruct);
  case TAG_PSTRUCT_TYPE:
    return marshall_pstruct_type(m, heap, tag->data.pstruct_type);
  case TAG_PSYM:  return marshall_psym(m, heap, tag->data.psym);
  case TAG_PTAG:
    return marshall_ptag(m, heap, tag->data.ptag);
  case TAG_PTR:   return marshall_ptr(m, heap, tag->data.ptr);
  case TAG_PTR_FREE:
    return marshall_ptr_free(m, heap, tag->data.ptr_free);
  case TAG_PVAR:  return marshall_pvar(m, heap, tag->data.pvar);
  case TAG_QUOTE: return marshall_quote(m, heap, &tag->data.quote);
  case TAG_RATIO: return marshall_ratio(m, heap, &tag->data.ratio);
  case TAG_S8:    return marshall_s8(m, heap, tag->data.s8);
  case TAG_S16:   return marshall_s16(m, heap, tag->data.s16);
  case TAG_S32:   return marshall_s32(m, heap, tag->data.s32);
  case TAG_S64:   return marshall_s64(m, heap, tag->data.s64);
  case TAG_STR:   return marshall_str(m, heap, &tag->data.str);
  case TAG_SW:    return marshall_sw(m, heap, tag->data.sw);
  case TAG_TIME:  return marshall_time(m, heap, &tag->data.time);
  case TAG_TUPLE: return marshall_tuple(m, heap, &tag->data.tuple);
  case TAG_U8:    return marshall_u8(m, heap, tag->data.u8);
  case TAG_U16:   return marshall_u16(m, heap, tag->data.u16);
  case TAG_U32:   return marshall_u32(m, heap, tag->data.u32);
  case TAG_U64:   return marshall_u64(m, heap, tag->data.u64);
  case TAG_UNQUOTE:
    return marshall_unquote(m, heap, &tag->data.unquote);
  case TAG_UW:    return marshall_uw(m, heap, tag->data.uw);
  }
  err_write_1("marshall_tag: unknown tag type : ");
  err_inspect_u8_decimal(&type);
  err_write_1("\n");
  assert(! "marshall_tag: unknown tag type");
  return NULL;
}

sw marshall_to_buf (s_marshall *m, s_buf *out)
{
  s_marshall_header mh = {0};
  sw r;
  sw result = 0;
  assert(m);
  assert(out);
  mh.le_magic = htole64(MARSHALL_MAGIC);
  mh.le_heap_count = htole64(m->heap_count);
  mh.le_heap_size = htole64(m->heap_pos);
  mh.le_buf_size = htole64(m->buf_pos);
  if ((r = buf_write(out, &mh, sizeof(mh))) != sizeof(mh))
    return -1;
  result += r;
  if ((r = buf_xfer(out, &m->heap, m->heap_pos)) != m->heap_pos)
    return -1;
  result += r;
  if ((r = buf_xfer(out, &m->buf, m->buf_pos)) != m->buf_pos)
    return -1;
  result += r;
  return result;
}

sw marshall_to_file (s_marshall *m, const char *path)
{
  FILE *fp;
  s_buf out;
  sw r;
  sw result = 0;
  assert(m);
  assert(path);
  if (! buf_init_alloc(&out, 1024 * 1024))
    return -1;
  if (! (fp = file_open(path, "wb")) ||
      ! buf_file_open_w(&out, fp) ||
      (r = marshall_to_buf(m, &out)) <= 0) {
    buf_clean(&out);
    return -1;
  }
  result = r;
  buf_file_close(&out);
  buf_clean(&out);
  return result;
}

s_str * marshall_to_str (s_marshall *m, s_str *dest)
{
  s_buf out;
  sw r;
  assert(m);
  assert(dest);
  if (! buf_init_alloc(&out, 1024 * 1024))
    return NULL;
  if ((r = marshall_to_buf(m, &out)) <= 0) {
    buf_clean(&out);
    return NULL;
  }
  if (! buf_read_to_str(&out, dest)) {
    buf_clean(&out);
    return NULL;
  }
  buf_clean(&out);
  return dest;
}

s_marshall * marshall_tuple (s_marshall *m, bool heap,
                             const s_tuple *tuple)
{
  uw i;
  assert(m);
  assert(tuple);
  if (! marshall_uw(m, heap, tuple->count))
    return NULL;
  i = 0;
  while (i < tuple->count) {
    if (! marshall_tag(m, heap, tuple->tag + i))
      return NULL;
    i++;
  }
  return m;
}

DEF_MARSHALL(u8)
DEF_MARSHALL(u16)
DEF_MARSHALL(u32)
DEF_MARSHALL(u64)
DEF_MARSHALL(uw)

// more complex types :

#define DEF_MARSHALL_STUB(name, type)                                  \
  PROTO_MARSHALL(name, type)                                           \
  {                                                                    \
    (void) m;                                                          \
    (void) heap;                                                       \
    (void) src;                                                        \
    err_puts("marshall_" # name ": not implemented");                  \
    return NULL;                                                       \
  }

DEF_MARSHALL_STUB(array, const s_array *)
DEF_MARSHALL_STUB(call, const s_call *)
DEF_MARSHALL_STUB(do_block, const s_do_block *)
DEF_MARSHALL_STUB(f32, f32)
DEF_MARSHALL_STUB(f64, f64)
DEF_MARSHALL_STUB(f128, f128)
DEF_MARSHALL_STUB(fact, const s_fact *)
DEF_MARSHALL_STUB(ident, const s_ident *)
DEF_MARSHALL_STUB(integer, const s_integer *)
DEF_MARSHALL_STUB(map, const s_map *)
DEF_MARSHALL_STUB(pcallable, p_callable)
DEF_MARSHALL_STUB(pcomplex, p_complex)
DEF_MARSHALL_STUB(pcow, p_cow)
DEF_MARSHALL_STUB(pstruct, p_struct)
DEF_MARSHALL_STUB(pstruct_type, p_struct_type)
DEF_MARSHALL_STUB(ptag, p_tag)
DEF_MARSHALL_STUB(ptr, u_ptr_w)
DEF_MARSHALL_STUB(ptr_free, u_ptr_w)
DEF_MARSHALL_STUB(psym, p_sym)
DEF_MARSHALL_STUB(pvar, p_var)
DEF_MARSHALL_STUB(quote, const s_quote *)
DEF_MARSHALL_STUB(ratio, const s_ratio *)
DEF_MARSHALL_STUB(struct, const s_struct *)
DEF_MARSHALL_STUB(struct_type, const s_struct_type *)
DEF_MARSHALL_STUB(sym, const s_sym *)
DEF_MARSHALL_STUB(time, const s_time *)
DEF_MARSHALL_STUB(unquote, const s_unquote *)
DEF_MARSHALL_STUB(var, const s_var *)
