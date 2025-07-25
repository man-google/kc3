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
#include <math.h>
#include <libkc3/kc3.h>
#include "../window_sdl2.h"
#include "../gl_camera.h"
#include "../mat4.h"
#include "../gl_object.h"
#include "../gl_sphere.h"
#include "../gl_sprite.h"
#include "earth.h"

#define EARTH_CAMERA_ROTATION_Z_SPEED 0.1
#define EARTH_SEGMENTS_U 200
#define EARTH_SEGMENTS_V 100

s_gl_sprite g_sprite_earth = {0};

bool earth_load (s_sequence *seq)
{
  s_gl_camera *camera;
  s_map *map;
  s_mat4 matrix;
  s_gl_sphere *sphere;
  const f32    sphere_radius = 5.0;
  s_window_sdl2 *window;
  assert(seq);
  window = seq->window;
  assert(window);
  camera = gl_camera_new(window->w, window->h);
  if (! camera)
    return false;
  sphere = gl_sphere_new(EARTH_SEGMENTS_U, EARTH_SEGMENTS_V);
  if (! sphere)
    return false;
  mat4_init_scale(&matrix, sphere_radius, sphere_radius,
                  sphere_radius);
  gl_object_transform(&sphere->object, &matrix);
  gl_object_update(&sphere->object);
  if (! tag_map(&seq->tag, 3))
    return false;
  map = &seq->tag.data.map;
  tag_init_psym(             map->key   + 0, sym_1("camera"));
  tag_init_ptr_free(         map->value + 0, camera);
  tag_init_psym(             map->key   + 1,
                sym_1("camera_rot_x_speed"));
  tag_init_f64(              map->value + 1, 0.01);
  tag_init_psym(             map->key   + 2, sym_1("sphere"));
  tag_init_pstruct_with_data(map->value + 2, sym_1("GL.Sphere"),
                             sphere, false);
  return true;
}

bool earth_render (s_sequence *seq)
{
  s_gl_camera *camera;
  f64         *camera_rot_x_speed;
  s_map *map;
  s_gl_sphere *sphere;
  s_window_sdl2 *window;
  assert(seq);
  window = seq->window;
  assert(window);
  if (! seq || seq->tag.type != TAG_MAP ||
      seq->tag.data.map.count != 3) {
    err_puts("earth_render: invalid seq->tag");
    return false;
  }
  map = &seq->tag.data.map;
  if (map->value[0].type != TAG_PTR_FREE ||
      map->value[1].type != TAG_F64 ||
      map->value[2].type != TAG_PSTRUCT) {
    err_puts("earth_render: invalid map");
    return false;
  }
  camera             =  map->value[0].data.ptr_free.p;
  camera_rot_x_speed = &map->value[1].data.f64;
  sphere             =  map->value[2].data.pstruct->data;
  gl_camera_set_aspect_ratio(camera, window->w, window->h);
  camera->rotation.x += seq->dt * (*camera_rot_x_speed) *
    M_PI * 2.0f;
  if (camera->rotation.x > M_PI || camera->rotation.x < 0)
    *camera_rot_x_speed *= -1.0;
  camera->rotation.z += seq->dt * EARTH_CAMERA_ROTATION_Z_SPEED *
    M_PI * 2.0f;
  camera->light_count = 1;
  camera->light_pos[0] = (s_vec4) { 1.0f, 0.0f, 0.0f, 0.0f };
  camera->light_color[0] = (s_rgb) { 1.0f, 0.98f, 0.95f };
  assert(glGetError() == GL_NO_ERROR);
  gl_camera_render(camera);
  assert(glGetError() == GL_NO_ERROR);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  assert(glGetError() == GL_NO_ERROR);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  assert(glGetError() == GL_NO_ERROR);
  assert(glGetError() == GL_NO_ERROR);
  assert(glGetError() == GL_NO_ERROR);
  assert(glGetError() == GL_NO_ERROR);
  glEnable(GL_DEPTH_TEST);
  assert(glGetError() == GL_NO_ERROR);
  gl_camera_bind_texture(camera,
                         gl_sprite_texture(&g_sprite_earth, 0));
  assert(glGetError() == GL_NO_ERROR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  assert(glGetError() == GL_NO_ERROR);
  gl_sphere_render(sphere);
  glDisable(GL_DEPTH_TEST);
  return true;
}

bool earth_unload (s_sequence *seq)
{
  (void) seq;
  return true;
}
