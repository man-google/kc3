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
#include "assert.h"
#include "complex.h"
#include "integer.h"
#include "ratio.h"
#include "tag.h"

s_tag * tag_add (s_tag *a, s_tag *b, s_tag *dest)
{
  s_complex c = {0};
  s_integer tmp = {0};
  s_integer tmp2 = {0};
  s_ratio r = {0};
  assert(a);
  assert(b);
  assert(dest);
  a = tag_resolve_cow(a);
  b = tag_resolve_cow(b);
  switch (a->type) {
  case TAG_F32:
    switch (b->type) {
    case TAG_PCOMPLEX:
      complex_init_f32(&c, a->data.f32);
      return tag_init_pcomplex(dest, complex_new_add(&c,
                                                     b->data.pcomplex));
    case TAG_F32:
      return tag_init_f32(dest, a->data.f32 + b->data.f32);
    case TAG_F64:
      return tag_init_f64(dest, (f64) a->data.f32 + b->data.f64);
    case TAG_F128:
      return tag_init_f128(dest, (f128) a->data.f32 + b->data.f128);
    case TAG_INTEGER:
      return tag_init_f32(dest, a->data.f32 +
                          integer_to_f32(&a->data.integer));
    case TAG_RATIO:
      ratio_init_f32(&r, a->data.f32);
      dest->type = TAG_RATIO;
      ratio_add(&r, &b->data.ratio, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S8:
      return tag_init_f32(dest, a->data.f32 + (f32) b->data.s8);
    case TAG_S16:
      return tag_init_f32(dest, a->data.f32 + (f32) b->data.s16);
    case TAG_S32:
      return tag_init_f32(dest, a->data.f32 + (f32) b->data.s32);
    case TAG_S64:
      return tag_init_f32(dest, a->data.f32 + (f32) b->data.s64);
    case TAG_SW:
      return tag_init_f32(dest, a->data.f32 + (f32) b->data.sw);
    case TAG_U8:
      return tag_init_f32(dest, a->data.f32 + (f32) b->data.u8);
    case TAG_U16:
      return tag_init_f32(dest, a->data.f32 + (f32) b->data.u16);
    case TAG_U32:
      return tag_init_f32(dest, a->data.f32 + (f32) b->data.u32);
    case TAG_U64:
      return tag_init_f32(dest, a->data.f32 + (f32) b->data.u64);
    case TAG_UW:
      return tag_init_f32(dest, a->data.f32 + (f32) b->data.uw);
    default:
      goto ko;
  }
  case TAG_F64:
    switch (b->type) {
    case TAG_PCOMPLEX:
      complex_init_f64(&c, a->data.f64);
      return tag_init_pcomplex(dest, complex_new_add(&c,
                                                     b->data.pcomplex));
    case TAG_F32:
      return tag_init_f64(dest, a->data.f64 + (f64) b->data.f32);
    case TAG_F64:
      return tag_init_f64(dest, a->data.f64 + b->data.f64);
    case TAG_F128:
      return tag_init_f128(dest, (f128) a->data.f64 + b->data.f128);
    case TAG_INTEGER:
      return tag_init_f64(dest, a->data.f64 +
                          integer_to_f64(&a->data.integer));
    case TAG_RATIO:
      ratio_init_f64(&r, a->data.f64);
      dest->type = TAG_RATIO;
      ratio_add(&r, &b->data.ratio, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S8:
      return tag_init_f64(dest, a->data.f64 + (f64) b->data.s8);
    case TAG_S16:
      return tag_init_f64(dest, a->data.f64 + (f64) b->data.s16);
    case TAG_S32:
      return tag_init_f64(dest, a->data.f64 + (f64) b->data.s32);
    case TAG_S64:
      return tag_init_f64(dest, a->data.f64 + (f64) b->data.s64);
    case TAG_SW:
      return tag_init_f64(dest, a->data.f64 + (f64) b->data.sw);
    case TAG_U8:
      return tag_init_f64(dest, a->data.f64 + (f64) b->data.u8);
    case TAG_U16:
      return tag_init_f64(dest, a->data.f64 + (f64) b->data.u16);
    case TAG_U32:
      return tag_init_f64(dest, a->data.f64 + (f64) b->data.u32);
    case TAG_U64:
      return tag_init_f64(dest, a->data.f64 + (f64) b->data.u64);
    case TAG_UW:
      return tag_init_f64(dest, a->data.f64 + (f64) b->data.uw);
    default:
      goto ko;
  }
  case TAG_F128:
    switch (b->type) {
    case TAG_PCOMPLEX:
      complex_init_f128(&c, a->data.f128);
      return tag_init_pcomplex(dest, complex_new_add(&c,
                                                     b->data.pcomplex));
    case TAG_F32:
      return tag_init_f128(dest, a->data.f128 + (f128) b->data.f32);
    case TAG_F64:
      return tag_init_f128(dest, a->data.f128 + (f128) b->data.f64);
    case TAG_F128:
      return tag_init_f128(dest, a->data.f128 + b->data.f128);
    case TAG_INTEGER:
      return tag_init_f128(dest, a->data.f128 +
                          integer_to_f128(&a->data.integer));
    case TAG_RATIO:
      ratio_init_f128(&r, a->data.f128);
      dest->type = TAG_RATIO;
      ratio_add(&r, &b->data.ratio, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S8:
      return tag_init_f128(dest, a->data.f128 + (f128) b->data.s8);
    case TAG_S16:
      return tag_init_f128(dest, a->data.f128 + (f128) b->data.s16);
    case TAG_S32:
      return tag_init_f128(dest, a->data.f128 + (f128) b->data.s32);
    case TAG_S64:
      return tag_init_f128(dest, a->data.f128 + (f128) b->data.s64);
    case TAG_SW:
      return tag_init_f128(dest, a->data.f128 + (f128) b->data.sw);
    case TAG_U8:
      return tag_init_f128(dest, a->data.f128 + (f128) b->data.u8);
    case TAG_U16:
      return tag_init_f128(dest, a->data.f128 + (f128) b->data.u16);
    case TAG_U32:
      return tag_init_f128(dest, a->data.f128 + (f128) b->data.u32);
    case TAG_U64:
      return tag_init_f128(dest, a->data.f128 + (f128) b->data.u64);
    case TAG_UW:
      return tag_init_f128(dest, a->data.f128 + (f128) b->data.uw);
    default:
      goto ko;
  }
  case TAG_INTEGER:
    switch (b->type) {
    case TAG_PCOMPLEX:
      if (! complex_init_integer(&c, &a->data.integer))
        return NULL;
      if (! tag_init_pcomplex(dest,
                              complex_new_add(&c, b->data.pcomplex))) {
        complex_clean(&c);
        return NULL;
      }
      complex_clean(&c);
      return dest;
    case TAG_F32:
      return tag_init_f32(dest, (f32) integer_to_f64(&a->data.integer) +
                          b->data.f32);
    case TAG_F64:
      return tag_init_f64(dest, integer_to_f64(&a->data.integer) +
                          b->data.f64);
    case TAG_F128:
      return tag_init_f128(dest, integer_to_f128(&a->data.integer) +
                          b->data.f128);
    case TAG_INTEGER:
      dest->type = TAG_INTEGER;
      integer_add(&a->data.integer, &b->data.integer,
                  &dest->data.integer);
      return tag_integer_reduce(dest);
    case TAG_RATIO:
      ratio_init_integer(&r, &a->data.integer);
      dest->type = TAG_RATIO;
      ratio_add(&r, &b->data.ratio, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S8:
      integer_init_s8(&tmp, b->data.s8);
      dest->type = TAG_INTEGER;
      integer_add(&a->data.integer, &tmp, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_S16:
      integer_init_s16(&tmp, b->data.s16);
      dest->type = TAG_INTEGER;
      integer_add(&a->data.integer, &tmp, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_S32:
      integer_init_s32(&tmp, b->data.s32);
      dest->type = TAG_INTEGER;
      integer_add(&a->data.integer, &tmp, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_S64:
      integer_init_s64(&tmp, b->data.s64);
      dest->type = TAG_INTEGER;
      integer_add(&a->data.integer, &tmp, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_SW:
      integer_init_sw(&tmp, b->data.sw);
      dest->type = TAG_INTEGER;
      integer_add(&a->data.integer, &tmp, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_U8:
      integer_init_u8(&tmp, b->data.u8);
      dest->type = TAG_INTEGER;
      integer_add(&a->data.integer, &tmp, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_U16:
      integer_init_u16(&tmp, b->data.u16);
      dest->type = TAG_INTEGER;
      integer_add(&a->data.integer, &tmp, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_U32:
      integer_init_u32(&tmp, b->data.u32);
      dest->type = TAG_INTEGER;
      integer_add(&a->data.integer, &tmp, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_U64:
      integer_init_u64(&tmp, b->data.u64);
      dest->type = TAG_INTEGER;
      integer_add(&a->data.integer, &tmp, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_UW:
      integer_init_uw(&tmp, b->data.uw);
      dest->type = TAG_INTEGER;
      integer_add(&a->data.integer, &tmp, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    default:
      goto ko;
    }
  case TAG_PCOMPLEX:
    switch (b->type) {
    case TAG_F32:
      complex_init_f32(&c, b->data.f32);
      return tag_init_pcomplex(dest, complex_new_add(a->data.pcomplex,
                                                     &c));
    case TAG_F64:
      complex_init_f64(&c, b->data.f64);
      return tag_init_pcomplex(dest, complex_new_add(a->data.pcomplex,
                                                     &c));
    case TAG_F128:
      complex_init_f128(&c, b->data.f128);
      return tag_init_pcomplex(dest, complex_new_add(a->data.pcomplex,
                                                     &c));
    case TAG_INTEGER:
      if (! complex_init_integer(&c, &b->data.integer))
        return NULL;
      if (! tag_init_pcomplex(dest, complex_new_add(a->data.pcomplex,
                                                    &c))) {
                                                   
        complex_clean(&c);
        return NULL;
      }
      complex_clean(&c);
      return dest;
    case TAG_PCOMPLEX:
      return tag_init_pcomplex(dest, complex_new_add(a->data.pcomplex,
                                                     b->data.pcomplex));
    case TAG_RATIO:
      if (! complex_init_ratio(&c, &b->data.ratio))
        return NULL;
      if (! tag_init_pcomplex(dest, complex_new_add(a->data.pcomplex,
                                                    &c))) {
                                                   
        complex_clean(&c);
        return NULL;
      }
      complex_clean(&c);
      return dest;
    case TAG_S8:
      complex_init_s8(&c, b->data.s8);
      return tag_init_pcomplex(dest, complex_new_add(a->data.pcomplex,
                                                     &c));
    case TAG_S16:
      complex_init_s16(&c, b->data.s16);
      return tag_init_pcomplex(dest, complex_new_add(a->data.pcomplex,
                                                     &c));
    case TAG_S32:
      complex_init_s32(&c, b->data.s32);
      return tag_init_pcomplex(dest, complex_new_add(a->data.pcomplex,
                                                     &c));
    case TAG_S64:
      complex_init_s64(&c, b->data.s64);
      return tag_init_pcomplex(dest, complex_new_add(a->data.pcomplex,
                                                     &c));
    case TAG_SW:
      complex_init_sw(&c, b->data.sw);
      return tag_init_pcomplex(dest, complex_new_add(a->data.pcomplex,
                                                     &c));
    case TAG_U8:
      complex_init_u8(&c, b->data.u8);
      return tag_init_pcomplex(dest, complex_new_add(a->data.pcomplex,
                                                     &c));
    case TAG_U16:
      complex_init_u16(&c, b->data.u16);
      return tag_init_pcomplex(dest, complex_new_add(a->data.pcomplex,
                                                     &c));
    case TAG_U32:
      complex_init_u32(&c, b->data.u32);
      return tag_init_pcomplex(dest, complex_new_add(a->data.pcomplex,
                                                     &c));
    case TAG_U64:
      complex_init_u64(&c, b->data.u64);
      return tag_init_pcomplex(dest, complex_new_add(a->data.pcomplex,
                                                     &c));
    case TAG_UW:
      complex_init_uw(&c, b->data.uw);
      return tag_init_pcomplex(dest, complex_new_add(a->data.pcomplex,
                                                     &c));
    default:
      break;
    }
    break;
  case TAG_RATIO:
    switch (b->type) {
    case TAG_PCOMPLEX:
      if (! complex_init_ratio(&c, &a->data.ratio))
        return NULL;
      if (! tag_init_pcomplex(dest,
                              complex_new_add(&c, b->data.pcomplex))) {
        complex_clean(&c);
        return NULL;
      }
      complex_clean(&c);
      return dest;
    case TAG_F32:
      ratio_init_f32(&r, b->data.f32);
      dest->type = TAG_RATIO;
      ratio_add(&a->data.ratio, &r, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_F64:
      ratio_init_f64(&r, b->data.f64);
      dest->type = TAG_RATIO;
      ratio_add(&a->data.ratio, &r, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_F128:
      ratio_init_f128(&r, b->data.f128);
      dest->type = TAG_RATIO;
      ratio_add(&a->data.ratio, &r, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_INTEGER:
      ratio_init_integer(&r, &b->data.integer);
      dest->type = TAG_RATIO;
      ratio_add(&a->data.ratio, &r, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_RATIO:
      if (! ratio_add(&a->data.ratio, &b->data.ratio,
                      &dest->data.ratio))
        return NULL;
      dest->type = TAG_RATIO;
      return dest;
    case TAG_S8:
      ratio_init_s8(&r, b->data.s8);
      dest->type = TAG_RATIO;
      ratio_add(&a->data.ratio, &r, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S16:
      ratio_init_s16(&r, b->data.s16);
      dest->type = TAG_RATIO;
      ratio_add(&a->data.ratio, &r, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S32:
      ratio_init_s32(&r, b->data.s32);
      dest->type = TAG_RATIO;
      ratio_add(&a->data.ratio, &r, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S64:
      ratio_init_s64(&r, b->data.s64);
      dest->type = TAG_RATIO;
      ratio_add(&a->data.ratio, &r, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_SW:
      ratio_init_sw(&r, b->data.sw);
      dest->type = TAG_RATIO;
      ratio_add(&a->data.ratio, &r, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_U8:
      ratio_init_u8(&r, b->data.u8);
      dest->type = TAG_RATIO;
      ratio_add(&a->data.ratio, &r, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_U16:
      ratio_init_u16(&r, b->data.u16);
      dest->type = TAG_RATIO;
      ratio_add(&a->data.ratio, &r, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_U32:
      ratio_init_u32(&r, b->data.u32);
      dest->type = TAG_RATIO;
      ratio_add(&a->data.ratio, &r, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_U64:
      ratio_init_u64(&r, b->data.u64);
      dest->type = TAG_RATIO;
      ratio_add(&a->data.ratio, &r, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_UW:
      ratio_init_uw(&r, b->data.uw);
      dest->type = TAG_RATIO;
      ratio_add(&a->data.ratio, &r, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    default:
      goto ko;
    }
  case TAG_S8:
    switch (b->type) {
    case TAG_PCOMPLEX:
      complex_init_s8(&c, a->data.s8);
      return tag_init_pcomplex(dest, complex_new_add(&c,
                                                     b->data.pcomplex));
    case TAG_F32:
      return tag_init_f32(dest, (f32) a->data.s8 + b->data.f32);
    case TAG_F64:
      return tag_init_f64(dest, (f64) a->data.s8 + b->data.f64);
    case TAG_F128:
      return tag_init_f128(dest, (f128) a->data.s8 + b->data.f128);
    case TAG_INTEGER:
      integer_init_s8(&tmp, a->data.s8);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &b->data.integer, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_RATIO:
      ratio_init_s8(&r, a->data.s8);
      dest->type = TAG_RATIO;
      ratio_add(&r, &b->data.ratio, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S8:
      tag_init_s16(dest, (s16) a->data.s8 + (s16) b->data.s8);
      return tag_integer_reduce(dest);
    case TAG_S16:
      tag_init_s32(dest, (s32) a->data.s8 + (s32) b->data.s16);
      return tag_integer_reduce(dest);
    case TAG_S32:
      tag_init_s64(dest, (s64) a->data.s8 + (s64) b->data.s32);
      return tag_integer_reduce(dest);
    case TAG_S64:
      integer_init_s8(&tmp, a->data.s8);
      integer_init_s64(&tmp2, b->data.s64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_SW:
      integer_init_s8(&tmp, a->data.s8);
      integer_init_sw(&tmp2, b->data.sw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U8:
      tag_init_s16(dest, (s16) a->data.s8 + (s16) b->data.u8);
      return tag_integer_reduce(dest);
    case TAG_U16:
      tag_init_s32(dest, (s32) a->data.s8 + (s32) b->data.u16);
      return tag_integer_reduce(dest);
    case TAG_U32:
      tag_init_s64(dest, (s64) a->data.s8 + (s64) b->data.u32);
      return tag_integer_reduce(dest);
    case TAG_U64:
      integer_init_s8(&tmp, a->data.s8);
      integer_init_u64(&tmp2, b->data.u64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_UW:
      integer_init_s8(&tmp, a->data.s8);
      integer_init_uw(&tmp2, b->data.uw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    default:
      goto ko;
  }
  case TAG_S16:
    switch (b->type) {
    case TAG_PCOMPLEX:
      complex_init_s16(&c, a->data.s16);
      return tag_init_pcomplex(dest, complex_new_add(&c,
                                                     b->data.pcomplex));
    case TAG_F32:
      return tag_init_f32(dest, (f32) a->data.s16 + b->data.f32);
    case TAG_F64:
      return tag_init_f64(dest, (f64) a->data.s16 + b->data.f64);
    case TAG_F128:
      return tag_init_f128(dest, (f128) a->data.s16 + b->data.f128);
    case TAG_INTEGER:
      integer_init_s16(&tmp, a->data.s16);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &b->data.integer, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_RATIO:
      ratio_init_s16(&r, a->data.s16);
      dest->type = TAG_RATIO;
      ratio_add(&r, &b->data.ratio, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S8:
      tag_init_s32(dest, (s32) a->data.s16 + (s32) b->data.s8);
      return tag_integer_reduce(dest);
    case TAG_S16:
      tag_init_s32(dest, (s32) a->data.s16 + (s32) b->data.s16);
      return tag_integer_reduce(dest);
    case TAG_S32:
      tag_init_s64(dest, (s64) a->data.s16 + (s64) b->data.s32);
      return tag_integer_reduce(dest);
    case TAG_S64:
      integer_init_s16(&tmp, a->data.s16);
      integer_init_s64(&tmp2, b->data.s64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_SW:
      integer_init_s16(&tmp, a->data.s16);
      integer_init_sw(&tmp2, b->data.sw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U8:
      tag_init_s32(dest, (s32) a->data.s16 + (s32) b->data.u8);
      return tag_integer_reduce(dest);
    case TAG_U16:
      tag_init_s32(dest, (s32) a->data.s16 + (s32) b->data.u16);
      return tag_integer_reduce(dest);
    case TAG_U32:
      tag_init_s64(dest, (s64) a->data.s16 + (s64) b->data.u32);
      return tag_integer_reduce(dest);
    case TAG_U64:
      integer_init_s16(&tmp, a->data.s16);
      integer_init_u64(&tmp2, b->data.u64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_UW:
      integer_init_s16(&tmp, a->data.s16);
      integer_init_uw(&tmp2, b->data.uw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    default:
      goto ko;
    }
  case TAG_S32:
    switch (b->type) {
    case TAG_PCOMPLEX:
      complex_init_s32(&c, a->data.s32);
      return tag_init_pcomplex(dest, complex_new_add(&c,
                                                     b->data.pcomplex));
    case TAG_F32:
      return tag_init_f32(dest, (f32) a->data.s32 + b->data.f32);
    case TAG_F64:
      return tag_init_f64(dest, (f64) a->data.s32 + b->data.f64);
    case TAG_F128:
      return tag_init_f128(dest, (f128) a->data.s32 + b->data.f128);
    case TAG_INTEGER:
      integer_init_s32(&tmp, a->data.s32);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &b->data.integer, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_RATIO:
      ratio_init_s32(&r, a->data.s32);
      dest->type = TAG_RATIO;
      ratio_add(&r, &b->data.ratio, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S8:
      tag_init_s64(dest, (s64) a->data.s32 + (s64) b->data.s8);
      return tag_integer_reduce(dest);
    case TAG_S16:
      tag_init_s64(dest, (s64) a->data.s32 + (s64) b->data.s16);
      return tag_integer_reduce(dest);
    case TAG_S32:
      tag_init_s64(dest, (s64) a->data.s32 + (s64) b->data.s32);
      return tag_integer_reduce(dest);
    case TAG_S64:
      integer_init_s32(&tmp, a->data.s32);
      integer_init_s64(&tmp2, b->data.s64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_SW:
      integer_init_s32(&tmp, a->data.s32);
      integer_init_sw(&tmp2, b->data.sw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U8:
      tag_init_s64(dest, (s64) a->data.s32 + (s64) b->data.u8);
      return tag_integer_reduce(dest);
    case TAG_U16:
      tag_init_s64(dest, (s64) a->data.s32 + (s64) b->data.u16);
      return tag_integer_reduce(dest);
    case TAG_U32:
      tag_init_s64(dest, (s64) a->data.s32 + (s64) b->data.u32);
      return tag_integer_reduce(dest);
    case TAG_U64:
      integer_init_s32(&tmp, a->data.s32);
      integer_init_u64(&tmp2, b->data.u64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_UW:
      integer_init_s32(&tmp, a->data.s32);
      integer_init_uw(&tmp2, b->data.uw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    default:
      goto ko;
  }
  case TAG_S64:
    switch (b->type) {
    case TAG_PCOMPLEX:
      complex_init_s64(&c, a->data.s64);
      return tag_init_pcomplex(dest, complex_new_add(&c,
                                                     b->data.pcomplex));
    case TAG_F32:
      return tag_init_f32(dest, (f32) a->data.s64 + b->data.f32);
    case TAG_F64:
      return tag_init_f64(dest, (f64) a->data.s64 + b->data.f64);
    case TAG_F128:
      return tag_init_f128(dest, (f128) a->data.s64 + b->data.f128);
    case TAG_INTEGER:
      integer_init_s64(&tmp, a->data.s64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &b->data.integer, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_RATIO:
      ratio_init_s64(&r, a->data.s64);
      dest->type = TAG_RATIO;
      ratio_add(&r, &b->data.ratio, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S8:
      integer_init_s64(&tmp, a->data.s64);
      integer_init_s8(&tmp2, b->data.s8);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_S16:
      integer_init_s64(&tmp, a->data.s64);
      integer_init_s16(&tmp2, b->data.s16);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_S32:
      integer_init_s64(&tmp, a->data.s64);
      integer_init_s32(&tmp2, b->data.s32);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_S64:
      integer_init_s64(&tmp, a->data.s64);
      integer_init_s64(&tmp2, b->data.s64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_SW:
      integer_init_s64(&tmp, a->data.s64);
      integer_init_sw(&tmp2, b->data.sw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U8:
      integer_init_s64(&tmp, a->data.s64);
      integer_init_u8(&tmp2, b->data.u8);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U16:
      integer_init_s64(&tmp, a->data.s64);
      integer_init_u16(&tmp2, b->data.u16);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U32:
      integer_init_s64(&tmp, a->data.s64);
      integer_init_u32(&tmp2, b->data.u32);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U64:
      integer_init_s64(&tmp, a->data.s64);
      integer_init_u64(&tmp2, b->data.u64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_UW:
      integer_init_s64(&tmp, a->data.s64);
      integer_init_uw(&tmp2, b->data.uw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    default:
      goto ko;
  }
  case TAG_SW:
    switch (b->type) {
    case TAG_PCOMPLEX:
      complex_init_sw(&c, a->data.sw);
      return tag_init_pcomplex(dest, complex_new_add(&c,
                                                     b->data.pcomplex));
    case TAG_F32:
      return tag_init_f32(dest, (f32) a->data.sw + b->data.f32);
    case TAG_F64:
      return tag_init_f64(dest, (f64) a->data.sw + b->data.f64);
    case TAG_F128:
      return tag_init_f128(dest, (f128) a->data.sw + b->data.f128);
    case TAG_INTEGER:
      integer_init_sw(&tmp, a->data.sw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &b->data.integer, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_RATIO:
      ratio_init_sw(&r, a->data.sw);
      dest->type = TAG_RATIO;
      ratio_add(&r, &b->data.ratio, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S8:
      integer_init_sw(&tmp, a->data.sw);
      integer_init_s8(&tmp2, b->data.s8);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_S16:
      integer_init_sw(&tmp, a->data.sw);
      integer_init_s16(&tmp2, b->data.s16);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_S32:
      integer_init_sw(&tmp, a->data.sw);
      integer_init_s32(&tmp2, b->data.s32);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_S64:
      integer_init_sw(&tmp, a->data.sw);
      integer_init_s64(&tmp2, b->data.s64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_SW:
      integer_init_sw(&tmp, a->data.sw);
      integer_init_sw(&tmp2, b->data.sw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U8:
      integer_init_sw(&tmp, a->data.sw);
      integer_init_u8(&tmp2, b->data.u8);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U16:
      integer_init_sw(&tmp, a->data.sw);
      integer_init_u16(&tmp2, b->data.u16);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U32:
      integer_init_sw(&tmp, a->data.sw);
      integer_init_u32(&tmp2, b->data.u32);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U64:
      integer_init_sw(&tmp, a->data.sw);
      integer_init_u64(&tmp2, b->data.u64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_UW:
      integer_init_sw(&tmp, a->data.sw);
      integer_init_uw(&tmp2, b->data.uw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    default:
      goto ko;
  }
  case TAG_U8:
    switch (b->type) {
    case TAG_PCOMPLEX:
      complex_init_u8(&c, a->data.u8);
      return tag_init_pcomplex(dest, complex_new_add(&c,
                                                     b->data.pcomplex));
    case TAG_F32:
      return tag_init_f32(dest, (f32) a->data.u8 + b->data.f32);
    case TAG_F64:
      return tag_init_f64(dest, (f64) a->data.u8 + b->data.f64);
    case TAG_F128:
      return tag_init_f128(dest, (f128) a->data.u8 + b->data.f128);
    case TAG_INTEGER:
      integer_init_u8(&tmp, a->data.u8);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &b->data.integer, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_RATIO:
      ratio_init_u8(&r, a->data.u8);
      dest->type = TAG_RATIO;
      ratio_add(&r, &b->data.ratio, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S8:
      tag_init_s16(dest, (s16) a->data.u8 + (s16) b->data.s8);
      return tag_integer_reduce(dest);
    case TAG_S16:
      tag_init_s32(dest, (s32) a->data.u8 + (s32) b->data.s16);
      return tag_integer_reduce(dest);
    case TAG_S32:
      tag_init_s64(dest, (s64) a->data.u8 + (s64) b->data.s32);
      return tag_integer_reduce(dest);
    case TAG_S64:
      integer_init_u8(&tmp, a->data.u8);
      integer_init_s64(&tmp2, b->data.s64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_SW:
      integer_init_u8(&tmp, a->data.u8);
      integer_init_sw(&tmp2, b->data.sw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U8:
      tag_init_u16(dest, (u16) a->data.u8 + (u16) b->data.u8);
      return tag_integer_reduce(dest);
    case TAG_U16:
      tag_init_u32(dest, (u32) a->data.u8 + (u32) b->data.u16);
      return tag_integer_reduce(dest);
    case TAG_U32:
      tag_init_u64(dest, (u64) a->data.u8 + (u64) b->data.u32);
      return tag_integer_reduce(dest);
    case TAG_U64:
      integer_init_u8(&tmp, a->data.u8);
      integer_init_u64(&tmp2, b->data.u64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_UW:
      integer_init_u8(&tmp, a->data.u8);
      integer_init_uw(&tmp2, b->data.uw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    default:
      goto ko;
  }
  case TAG_U16:
    switch (b->type) {
    case TAG_PCOMPLEX:
      complex_init_u16(&c, a->data.u16);
      return tag_init_pcomplex(dest, complex_new_add(&c,
                                                     b->data.pcomplex));
    case TAG_F32:
      return tag_init_f32(dest, (f32) a->data.u16 + b->data.f32);
    case TAG_F64:
      return tag_init_f64(dest, (f64) a->data.u16 + b->data.f64);
    case TAG_F128:
      return tag_init_f128(dest, (f128) a->data.u16 + b->data.f128);
    case TAG_INTEGER:
      integer_init_u16(&tmp, a->data.u16);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &b->data.integer, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_RATIO:
      ratio_init_u16(&r, a->data.u16);
      dest->type = TAG_RATIO;
      ratio_add(&r, &b->data.ratio, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S8:
      tag_init_s32(dest, (s32) a->data.u16 + (s32) b->data.s8);
      return tag_integer_reduce(dest);
    case TAG_S16:
      tag_init_s32(dest, (s32) a->data.u16 + (s32) b->data.s16);
      return tag_integer_reduce(dest);
    case TAG_S32:
      tag_init_s64(dest, (s64) a->data.u16 + (s64) b->data.s32);
      return tag_integer_reduce(dest);
    case TAG_S64:
      integer_init_u16(&tmp, a->data.u16);
      integer_init_s64(&tmp2, b->data.s64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_SW:
      integer_init_u16(&tmp, a->data.u16);
      integer_init_sw(&tmp2, b->data.sw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U8:
      tag_init_u32(dest, (u32) a->data.u16 + (u32) b->data.u8);
      return tag_integer_reduce(dest);
    case TAG_U16:
      tag_init_u32(dest, (u32) a->data.u16 + (u32) b->data.u16);
      return tag_integer_reduce(dest);
    case TAG_U32:
      tag_init_u64(dest, (u64) a->data.u16 + (u64) b->data.u32);
      return tag_integer_reduce(dest);
    case TAG_U64:
      integer_init_u32(&tmp, (u32) a->data.u16);
      integer_init_u64(&tmp2, b->data.u64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_UW:
      integer_init_u16(&tmp, a->data.u16);
      integer_init_uw(&tmp2, b->data.uw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    default:
      goto ko;
  }
  case TAG_U32:
    switch (b->type) {
    case TAG_PCOMPLEX:
      complex_init_u32(&c, a->data.u32);
      return tag_init_pcomplex(dest, complex_new_add(&c,
                                                     b->data.pcomplex));
    case TAG_F32:
      return tag_init_f32(dest, (f32) a->data.u32 + b->data.f32);
    case TAG_F64:
      return tag_init_f64(dest, (f64) a->data.u32 + b->data.f64);
    case TAG_F128:
      return tag_init_f128(dest, (f128) a->data.u32 + b->data.f128);
    case TAG_INTEGER:
      integer_init_u32(&tmp, a->data.u32);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &b->data.integer, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_RATIO:
      ratio_init_u32(&r, a->data.u32);
      dest->type = TAG_RATIO;
      ratio_add(&r, &b->data.ratio, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S8:
      tag_init_s64(dest, (s64) a->data.u32 + (s64) b->data.s8);
      return tag_integer_reduce(dest);
    case TAG_S16:
      tag_init_s64(dest, (s64) a->data.u32 + (s64) b->data.s16);
      return tag_integer_reduce(dest);
    case TAG_S32:
      tag_init_s64(dest, (s64) a->data.u32 + (s64) b->data.s32);
      return tag_integer_reduce(dest);
    case TAG_S64:
      integer_init_u32(&tmp, a->data.u32);
      integer_init_s64(&tmp2, b->data.s64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_SW:
      integer_init_u32(&tmp, a->data.u32);
      integer_init_sw(&tmp2, b->data.sw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U8:
      tag_init_u64(dest, (u64) a->data.u32 + (u64) b->data.u8);
      return tag_integer_reduce(dest);
    case TAG_U16:
      tag_init_u64(dest, (u64) a->data.u32 + (u64) b->data.u16);
      return tag_integer_reduce(dest);
    case TAG_U32:
      tag_init_u64(dest, (u64) a->data.u32 + (u64) b->data.u32);
      return tag_integer_reduce(dest);
    case TAG_U64:
      integer_init_u32(&tmp, a->data.u32);
      integer_init_u64(&tmp2, b->data.u64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_UW:
      integer_init_u32(&tmp, a->data.u32);
      integer_init_uw(&tmp2, b->data.uw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    default:
      goto ko;
  }
  case TAG_U64:
    switch (b->type) {
    case TAG_PCOMPLEX:
      complex_init_u64(&c, a->data.u64);
      return tag_init_pcomplex(dest, complex_new_add(&c,
                                                     b->data.pcomplex));
    case TAG_F32:
      return tag_init_f32(dest, (f32) a->data.u64 + b->data.f32);
    case TAG_F64:
      return tag_init_f64(dest, (f64) a->data.u64 + b->data.f64);
    case TAG_F128:
      return tag_init_f128(dest, (f128) a->data.u64 + b->data.f128);
    case TAG_INTEGER:
      integer_init_u64(&tmp, a->data.u64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &b->data.integer, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_RATIO:
      ratio_init_u64(&r, a->data.u64);
      dest->type = TAG_RATIO;
      ratio_add(&r, &b->data.ratio, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S8:
      integer_init_u64(&tmp, a->data.u64);
      integer_init_s8(&tmp2, b->data.s8);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_S16:
      integer_init_u64(&tmp, a->data.u64);
      integer_init_s16(&tmp2, b->data.s16);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_S32:
      integer_init_u64(&tmp, a->data.u64);
      integer_init_s32(&tmp2, b->data.s32);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_S64:
      integer_init_u64(&tmp, a->data.u64);
      integer_init_s64(&tmp2, b->data.s64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_SW:
      integer_init_u64(&tmp, a->data.u64);
      integer_init_sw(&tmp2, b->data.sw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U8:
      integer_init_u64(&tmp, a->data.u64);
      integer_init_u8(&tmp2, b->data.u8);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U16:
      integer_init_u64(&tmp, a->data.u64);
      integer_init_u16(&tmp2, b->data.u16);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U32:
      integer_init_u64(&tmp, a->data.u64);
      integer_init_u32(&tmp2, b->data.u32);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U64:
      integer_init_u64(&tmp, a->data.u64);
      integer_init_u64(&tmp2, b->data.u64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_UW:
      integer_init_u64(&tmp, a->data.u64);
      integer_init_uw(&tmp2, b->data.uw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    default:
      goto ko;
    }
  case TAG_UW:
    switch (b->type) {
    case TAG_PCOMPLEX:
      complex_init_uw(&c, a->data.uw);
      return tag_init_pcomplex(dest, complex_new_add(&c,
                                                     b->data.pcomplex));
    case TAG_F32:
      return tag_init_f32(dest, (f32) a->data.uw + b->data.f32);
    case TAG_F64:
      return tag_init_f64(dest, (f64) a->data.uw + b->data.f64);
    case TAG_F128:
      return tag_init_f128(dest, (f128) a->data.uw + b->data.f128);
    case TAG_INTEGER:
      integer_init_uw(&tmp, a->data.uw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &b->data.integer, &dest->data.integer);
      integer_clean(&tmp);
      return tag_integer_reduce(dest);
    case TAG_RATIO:
      ratio_init_uw(&r, a->data.uw);
      dest->type = TAG_RATIO;
      ratio_add(&r, &b->data.ratio, &dest->data.ratio);
      ratio_clean(&r);
      return dest;
    case TAG_S8:
      integer_init_uw(&tmp, a->data.uw);
      integer_init_s8(&tmp2, b->data.s8);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_S16:
      integer_init_uw(&tmp, a->data.uw);
      integer_init_s16(&tmp2, b->data.s16);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_S32:
      integer_init_uw(&tmp, a->data.uw);
      integer_init_s32(&tmp2, b->data.s32);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_S64:
      integer_init_uw(&tmp, a->data.uw);
      integer_init_s64(&tmp2, b->data.s64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_SW:
      integer_init_uw(&tmp, a->data.uw);
      integer_init_sw(&tmp2, b->data.sw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U8:
      integer_init_uw(&tmp, a->data.uw);
      integer_init_u8(&tmp2, b->data.u8);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U16:
      integer_init_uw(&tmp, a->data.uw);
      integer_init_u16(&tmp2, b->data.u16);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U32:
      integer_init_uw(&tmp, a->data.uw);
      integer_init_u32(&tmp2, b->data.u32);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_U64:
      integer_init_uw(&tmp, a->data.uw);
      integer_init_u64(&tmp2, b->data.u64);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    case TAG_UW:
      integer_init_uw(&tmp, a->data.uw);
      integer_init_uw(&tmp2, b->data.uw);
      dest->type = TAG_INTEGER;
      integer_add(&tmp, &tmp2, &dest->data.integer);
      integer_clean(&tmp);
      integer_clean(&tmp2);
      return tag_integer_reduce(dest);
    default:
      goto ko;
    }
  case TAG_STR:
    switch (b->type) {
    case TAG_STR:
      return tag_init_str_concatenate(dest, &a->data.str, &b->data.str);
    default:
      goto ko;
    }
  case TAG_TIME:
    switch (b->type) {
    case TAG_TIME:
      return tag_init_time_add(dest, &a->data.time, &b->data.time);
    default:
      goto ko;
    }
  default:
    goto ko;
  }
 ko:
  err_write_1("tag_add: invalid tag type: ");
  err_write_1(tag_type_to_string(a->type));
  err_write_1(" + ");
  err_puts(tag_type_to_string(b->type));
  err_stacktrace();
  assert(! "tag_add: invalid tag type");
  return NULL;
}
