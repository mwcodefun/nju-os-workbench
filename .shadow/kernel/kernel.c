#include <am.h>
#include <amdev.h>
#include <klib.h>
#include <klib-macros.h>

#define SIDE 16

static int w, h; // Screen size

#define KEYNAME(key) \
  [AM_KEY_##key] = #key,
static const char *key_names[] = {AM_KEYS(KEYNAME)};

static inline void puts(const char *s)
{
  for (; *s; s++)
    putch(*s);
}

void print_key()
{
  AM_INPUT_KEYBRD_T event = {.keycode = AM_KEY_NONE};
  ioe_read(AM_INPUT_KEYBRD, &event);
  if (event.keycode != AM_KEY_NONE && event.keydown)
  {
    puts("Key pressed: ");
    puts(key_names[event.keycode]);
    puts("\n");
  }
}

static void draw_tile(int x, int y, int w, int h, uint32_t color)
{
  uint32_t pixels[w * h]; // WARNING: large stack-allocated memory
  AM_GPU_FBDRAW_T event = {
      .x = x,
      .y = y,
      .w = w,
      .h = h,
      .sync = 1,
      .pixels = pixels,
  };
  for (int i = 0; i < w * h; i++)
  {
    pixels[i] = color;
  }
  ioe_write(AM_GPU_FBDRAW, &event);
}
unsigned int jpg[] = {0x12,0x33};
unsigned int jpg_len = 6904;
unsigned int jpeg_h = 160;
unsigned int jpeg_w = 160;

void draw_pic()
{
  AM_GPU_CONFIG_T info = {0};
  ioe_read(AM_GPU_CONFIG, &info);
  w = info.width;
  h = info.height;
  // w=640 h = 480
  uint32_t pixels[w];
  AM_GPU_FBDRAW_T event = {
      .x = 0,
      .y = 0,
      .w = w,
      .h = 1,
      .sync = 1,
      .pixels = pixels,
  };
  for (int x = 0; x < h; x++)
  {
    for (int y = 0; y < w; y++)
    {
      // int original = x * h + y;
      // int p = x * jpeg_h + 
      unsigned int t = jpg[x * w + y];
      pixels[y] = t;
    }
    event.x = 0;
    event.y = x;
    event.pixels = pixels;
    ioe_write(AM_GPU_FBDRAW, &event);
  }
  // 每次绘制一行
}

void splash()
{
  AM_GPU_CONFIG_T info = {0};
  ioe_read(AM_GPU_CONFIG, &info);
  w = info.width;
  h = info.height;

  for (int x = 0; x * SIDE <= w; x++)
  {
    for (int y = 0; y * SIDE <= h; y++)
    {
      if ((x & 1) ^ (y & 1))
      {
        draw_tile(x * SIDE, y * SIDE, SIDE, SIDE, 0xffffff); // white
      }
    }
  }
}

// Operating system is a C program!
int main(const char *args)
{
  ioe_init();

  puts("mainargs = \"");
  puts(args); // make run mainargs=xxx
  puts("\"\n");

  puts("hello\n");
  // splash();
  draw_pic();

  puts("Press any key to see its key code...\n");
  while (1)
  {
    print_key();
  }
  return 0;
}
