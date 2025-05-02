
#include <bitmap-font/boxxy.h>

typedef struct draw_ctx {
  u32 *restrict fb;
  u32  width;
  u32  height;
  u32  pitch;
  i32  x;
  i32  y;
  u32  bg;
  u32  fg;
  bool single_line;
  bool auto_wrap;
  bool break_word;
  bool ingore_cr;
  bool ingore_lf;
} *draw_ctx_t;

void draw_char(draw_ctx_t ctx, char ch) {
  if (!ctx->single_line && ctx->auto_wrap && ctx->x + bitmap_font_boxxy_width >= ctx->width) {
    ctx->x  = 0;
    ctx->y += bitmap_font_boxxy_height;
  }
  for (i32 dy = 0; dy < bitmap_font_boxxy_height; dy++) {
    i32 by = ctx->y + dy;
    if (by < 0 || by >= ctx->height) continue;
    u32 byte = bitmap_font_boxxy[ch * bitmap_font_boxxy_height + dy];
    for (i32 dx = 0; dx < bitmap_font_boxxy_width; dx++) {
      i32 bx = ctx->x + dx;
      if (bx < 0 || bx >= ctx->width) continue;
      ctx->fb[by * ctx->pitch + bx] = (byte >> (8 - dx)) & 1 ? ctx->fg : ctx->bg;
    }
  }
  ctx->x += bitmap_font_boxxy_width;
}

#define isalnum(c)                                                                                 \
  ((c) >= '0' && (c) <= '9' || (c) >= 'A' && (c) <= 'Z' || (c) >= 'a' && (c) <= 'z')

void draw_text(draw_ctx_t ctx, cstr text) {
  if (ctx->single_line) {
    for (; *text; text++) {
      draw_char(ctx, *text);
    }
    return;
  }
  bool in_word = false;
  for (; *text; text++) {
    const char ch = *text;
    if (!ctx->break_word && !in_word && isalnum(ch)) {
      int nchars = 0;
      for (const char *p = text; *p && isalnum(*p); p++) {
        nchars++;
      }
      if (ctx->x + bitmap_font_boxxy_width * nchars >= ctx->width) {
        ctx->x  = 0;
        ctx->y += bitmap_font_boxxy_height;
      }
      in_word = true;
    }
    if (ch == '\n') {
      if (ctx->ingore_lf) {
        ctx->x += bitmap_font_boxxy_width;
      } else {
        ctx->x  = 0;
        ctx->y += bitmap_font_boxxy_height;
      }
      continue;
    }
    if (ch == '\r') {
      if (ctx->ingore_cr) {
        ctx->x += bitmap_font_boxxy_width;
      } else {
        ctx->x = 0;
      }
      continue;
    }
    if (in_word && !isalnum(ch)) in_word = false;
    draw_char(ctx, ch);
  }
}

#define WIDTH  64
#define HEIGHT 24
u32 buffer[WIDTH * HEIGHT];

int main() {
  struct draw_ctx ctx = {
      .fb          = buffer,
      .width       = WIDTH,
      .height      = HEIGHT,
      .pitch       = WIDTH,
      .x           = 0,
      .y           = 0,
      .bg          = 0x00000000,
      .fg          = 0xFFFFFFFF,
      .single_line = false,
      .auto_wrap   = true,
      .break_word  = false,
      .ingore_cr   = false,
      .ingore_lf   = false,
  };

  draw_text(&ctx, "ABC DEFGHIJKL");

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      __syscall(1, 1, buffer[i * WIDTH + j] ? "*" : " ", 1);
    }
    __syscall(1, 1, "\n", 1);
  }

  __syscall(60, 0);
  __builtin_unreachable();
}
