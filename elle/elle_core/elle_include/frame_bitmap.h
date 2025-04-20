#ifndef frame_bitmap_h
#define frame_bitmap_h
#include "draw_element.h"
#include "types.h"
#include "memory.h"

// Video memory declarations
extern unsigned char* video_memory;
#define VIDEO_MEMORY_ADDRESS 0xE0000000  // Bochs video memory address
int init_video_memory(void);

struct bitmap_element
{
    aisle width;
    aisle height;
    aisle color_format;
    den * video_buffer;
};

struct bitmap_element init_bitmap;
struct bitmap_element *create_main_frame_bitmap(int width, int height);
struct bitmap_element *create_sub_frame_bitmap(int width, int height);
struct bitmap_element *create_terminal_bitmap(int width, int height);
struct bitmap_element *create_frame_bitmap(int width, int height);

#endif