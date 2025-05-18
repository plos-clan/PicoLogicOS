#pragma once
#include "private.hpp"

#define API                                                                                        \
  template <PixFmt fmt>                                                                            \
  vectorize FLATTEN void

namespace {

API fb_flush(FrameBuffer &fb, const pl2d::TextureB &tex, const pl2d::Rect &rect) {
  for (u32 y = rect.y1; y <= rect.y2; y++) {
    for (u32 x = rect.x1; x <= rect.x2; x++) {
      fb_flush_pix<fmt>(fb, tex, x, y);
    }
  }
}
API fb_flush(FrameBuffer &fb, const pl2d::TextureF &tex, const pl2d::Rect &rect) {
  for (u32 y = rect.y1; y <= rect.y2; y++) {
    for (u32 x = rect.x1; x <= rect.x2; x++) {
      fb_flush_pix<fmt>(fb, tex, x, y);
    }
  }
}
API fb_copy_to(const FrameBuffer &fb, pl2d::TextureB &tex, const pl2d::Rect &rect) {
  for (u32 y = rect.y1; y <= rect.y2; y++) {
    for (u32 x = rect.x1; x <= rect.x2; x++) {
      fb_copy_to_pix<fmt>(fb, tex, x, y);
    }
  }
}
API fb_copy_to(const FrameBuffer &fb, pl2d::TextureF &tex, const pl2d::Rect &rect) {
  for (u32 y = rect.y1; y <= rect.y2; y++) {
    for (u32 x = rect.x1; x <= rect.x2; x++) {
      fb_copy_to_pix<fmt>(fb, tex, x, y);
    }
  }
}

} // namespace

#undef API
