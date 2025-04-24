#include "frame_bitmap.h"

// Define video memory pointer
unsigned char* video_memory = NULL;

int init_video_memory(void)
{
    // Map video memory at Bochs address
    video_memory = (unsigned char*)VIDEO_MEMORY_ADDRESS;
    if (!video_memory) {
        return 0;
    }

    // Clear screen
    memset(video_memory, 0, screen_width * screen_height * 4);
    return 1;
}

struct bitmap_element *create_main_frame_bitmap(int width, int height)
{
    init_bitmap.width = width;
    init_bitmap.height = height;
    init_bitmap.color_format = rgb_format;
    init_bitmap.video_buffer = (den *)video_memory;  // Explicit cast to den pointer
    return &init_bitmap;
}

struct bitmap_element *create_sub_frame_bitmap(int width, int height)
{
    init_bitmap.width = width;
    init_bitmap.height = height;
    init_bitmap.color_format = rgb_format;
    init_bitmap.video_buffer = (den *)video_memory;  // Explicit cast to den pointer
    return &init_bitmap;
}

struct bitmap_element *create_terminal_bitmap(int width, int height)
{
    init_bitmap.width = width;
    init_bitmap.height = height;
    init_bitmap.color_format = rgb_format;
    init_bitmap.video_buffer = (den *)video_memory;  // Explicit cast to den pointer
    return &init_bitmap;
}

struct bitmap_element *create_frame_bitmap(int width, int height)
{
    init_bitmap.width = width;
    init_bitmap.height = height;
    init_bitmap.color_format = rgb_format;
    init_bitmap.video_buffer = (den *)video_memory;  // Explicit cast to den pointer
    return &init_bitmap;
}