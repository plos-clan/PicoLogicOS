#pragma once
#include "private.hpp"

#define API                                                                                        \
  template <>                                                                                      \
  INLINE void

namespace {

//*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
API fb_flush_pix<PixFmt::BGR>(FrameBuffer &fb, const pl2d::TextureB &tex, u32 x, u32 y) {
  byte *_rest fb_p  = &fb.pix8[0][y * fb.pitch + x * fb.padding];
  auto *_rest tex_p = &tex.pixels[y * tex.pitch + x];
  fb_p[0]           = tex_p->b;
  fb_p[1]           = tex_p->g;
  fb_p[2]           = tex_p->r;
}
API fb_flush_pix<PixFmt::BGR>(FrameBuffer &fb, const pl2d::TextureF &tex, u32 x, u32 y) {
  byte *_rest fb_p  = &fb.pix8[0][y * fb.pitch + x * fb.padding];
  auto *_rest tex_p = &tex.pixels[y * tex.pitch + x];
  fb_p[0]           = cpp::clamp(tex_p->b, 0.f, 1.f) * 255.f;
  fb_p[1]           = cpp::clamp(tex_p->g, 0.f, 1.f) * 255.f;
  fb_p[2]           = cpp::clamp(tex_p->r, 0.f, 1.f) * 255.f;
}
API fb_copy_to_pix<PixFmt::BGR>(const FrameBuffer &fb, pl2d::TextureB &tex, u32 x, u32 y) {
  byte *_rest fb_p  = &fb.pix8[0][y * fb.pitch + x * fb.padding];
  auto *_rest tex_p = &tex.pixels[y * tex.pitch + x];
  tex_p->b          = fb_p[0];
  tex_p->g          = fb_p[1];
  tex_p->r          = fb_p[2];
  tex_p->a          = 255;
}
API fb_copy_to_pix<PixFmt::BGR>(const FrameBuffer &fb, pl2d::TextureF &tex, u32 x, u32 y) {
  byte *_rest fb_p  = &fb.pix8[0][y * fb.pitch + x * fb.padding];
  auto *_rest tex_p = &tex.pixels[y * tex.pitch + x];
  tex_p->b          = fb_p[0] / 255.f;
  tex_p->g          = fb_p[1] / 255.f;
  tex_p->r          = fb_p[2] / 255.f;
  tex_p->a          = 1;
}
//.<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
API fb_flush_pix<PixFmt::BGRA>(FrameBuffer &fb, const pl2d::TextureB &tex, u32 x, u32 y) {
  byte *_rest fb_p  = &fb.pix8[0][y * fb.pitch + x * fb.padding];
  auto *_rest tex_p = &tex.pixels[y * tex.pitch + x];
  fb_p[0]           = tex_p->b;
  fb_p[1]           = tex_p->g;
  fb_p[2]           = tex_p->r;
  fb_p[3]           = tex_p->a;
}
API fb_flush_pix<PixFmt::BGRA>(FrameBuffer &fb, const pl2d::TextureF &tex, u32 x, u32 y) {
  byte *_rest fb_p  = &fb.pix8[0][y * fb.pitch + x * fb.padding];
  auto *_rest tex_p = &tex.pixels[y * tex.pitch + x];
  fb_p[0]           = cpp::clamp(tex_p->b, 0.f, 1.f) * 255.f;
  fb_p[1]           = cpp::clamp(tex_p->g, 0.f, 1.f) * 255.f;
  fb_p[2]           = cpp::clamp(tex_p->r, 0.f, 1.f) * 255.f;
  fb_p[3]           = cpp::clamp(tex_p->a, 0.f, 1.f) * 255.f;
}
API fb_copy_to_pix<PixFmt::BGRA>(const FrameBuffer &fb, pl2d::TextureB &tex, u32 x, u32 y) {
  byte *_rest fb_p  = &fb.pix8[0][y * fb.pitch + x * fb.padding];
  auto *_rest tex_p = &tex.pixels[y * tex.pitch + x];
  tex_p->b          = fb_p[0];
  tex_p->g          = fb_p[1];
  tex_p->r          = fb_p[2];
  tex_p->a          = fb_p[3];
}
API fb_copy_to_pix<PixFmt::BGRA>(const FrameBuffer &fb, pl2d::TextureF &tex, u32 x, u32 y) {
  byte *_rest fb_p  = &fb.pix8[0][y * fb.pitch + x * fb.padding];
  auto *_rest tex_p = &tex.pixels[y * tex.pitch + x];
  tex_p->b          = fb_p[0] / 255.f;
  tex_p->g          = fb_p[1] / 255.f;
  tex_p->r          = fb_p[2] / 255.f;
  tex_p->a          = fb_p[3] / 255.f;
}
//.<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
API fb_flush_pix<PixFmt::ABGR>(FrameBuffer &fb, const pl2d::TextureB &tex, u32 x, u32 y) {
  byte *_rest fb_p  = &fb.pix8[0][y * fb.pitch + x * fb.padding];
  auto *_rest tex_p = &tex.pixels[y * tex.pitch + x];
  fb_p[0]           = tex_p->a;
  fb_p[1]           = tex_p->b;
  fb_p[2]           = tex_p->g;
  fb_p[3]           = tex_p->r;
}
API fb_flush_pix<PixFmt::ABGR>(FrameBuffer &fb, const pl2d::TextureF &tex, u32 x, u32 y) {
  byte *_rest fb_p  = &fb.pix8[0][y * fb.pitch + x * fb.padding];
  auto *_rest tex_p = &tex.pixels[y * tex.pitch + x];
  fb_p[0]           = cpp::clamp(tex_p->a, 0.f, 1.f) * 255.f;
  fb_p[1]           = cpp::clamp(tex_p->b, 0.f, 1.f) * 255.f;
  fb_p[2]           = cpp::clamp(tex_p->g, 0.f, 1.f) * 255.f;
  fb_p[3]           = cpp::clamp(tex_p->r, 0.f, 1.f) * 255.f;
}
API fb_copy_to_pix<PixFmt::ABGR>(const FrameBuffer &fb, pl2d::TextureB &tex, u32 x, u32 y) {
  byte *_rest fb_p  = &fb.pix8[0][y * fb.pitch + x * fb.padding];
  auto *_rest tex_p = &tex.pixels[y * tex.pitch + x];
  tex_p->a          = fb_p[0];
  tex_p->b          = fb_p[1];
  tex_p->g          = fb_p[2];
  tex_p->r          = fb_p[3];
}
API fb_copy_to_pix<PixFmt::ABGR>(const FrameBuffer &fb, pl2d::TextureF &tex, u32 x, u32 y) {
  byte *_rest fb_p  = &fb.pix8[0][y * fb.pitch + x * fb.padding];
  auto *_rest tex_p = &tex.pixels[y * tex.pitch + x];
  tex_p->a          = fb_p[0] / 255.f;
  tex_p->b          = fb_p[1] / 255.f;
  tex_p->g          = fb_p[2] / 255.f;
  tex_p->r          = fb_p[3] / 255.f;
}
//.<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

} // namespace

#undef API
