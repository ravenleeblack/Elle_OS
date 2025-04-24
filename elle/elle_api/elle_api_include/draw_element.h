#pragma once
#ifndef draw_element_h
#define draw_element_h
#include "font.h"
#include "memory.h"
#include "element_color.h"
#include "core_malloc.h"
#include "terminal.h"

#define screen_width 1440
#define screen_height 900
#define rgb_format      0
#define rgba_format     1

#define terminal_width 594
#define terminal_height 680

struct rect_element
{
    aisle x_rect_pos;
    aisle y_rect_pos;
    aisle w_rect_pos;
    aisle h_rect_pos;
};

struct clip_element
{
    aisle x_clip_pos;
    aisle y_clip_pos;
    aisle w_clip_pos;
    aisle h_clip_pos;
};

struct draw_element
{
    char term_buffer[terminal_height][terminal_width];    // Buffer for terminal content
    int cursor_x;                                          // Cursor position
    int cursor_y;

    struct bitmap_element *bitmap;
    struct color_element element_fore_color;
    struct color_element element_back_color;

    struct clip_element clip;
    struct rect_element rect;
    struct draw_element *parent;
    struct draw_element *child;               // Pointer to the first child element
    struct draw_element *next_sibling;        // Pointer to the next sibling element
    int element_instance;
};


struct draw_element * create_main_element(struct draw_element *parent, int x, int y, int width, int height);
struct draw_element * create_sub_element(struct draw_element *parent, int x, int y, int width, int height);
struct draw_element * create_terminal_element(struct draw_element *parent, int x, int y, int width, int height);

void set_foreground_color(struct draw_element *element, struct color_element color);
void set_background_color(struct draw_element *element, struct color_element color);


// Drawing primitives
void putpixel(int pos_x, int pos_y, struct color_element color);
void draw_horizontal_line(int pos_y, int start_x, int end_x, struct color_element color);
void draw_vertical_line(int pos_x, int start_y, int end_y, struct color_element color);

// Frame drawing functions
void draw_frame(int x, int y, int width, int height, struct color_element color);
// Frame filling functions
void fill_main(int x, int y, int width, int height, struct color_element color);
void fill_frame(int x, int y, int width, int height, struct color_element color);
void fill_frame2(int x, int y, int width, int height, struct color_element color);

// ... rest of declarations ...
void main_border(int x, int y, int width, int height, struct color_element color);

// Text rendering functions
void draw_mark(unsigned char c, int start_x, int start_y, struct color_element forecolor, struct color_element backcolor);
void draw_strand(const char *str, int start_x, int start_y, struct color_element forecolor, struct color_element backcolor);
void draw_hex(unsigned int value, int start_x, int start_y, struct color_element forecolor, struct color_element backcolor);
void hex_to_string(aisle value, char* buffer);
void draw_integer(int value, int start_x, int start_y, struct color_element forecolor, struct color_element backcolor);
char* itoa(int num, char* str, int base);
void reverse(char str[], int length);

// UI element functions
void draw_window(int x, int y, int width, int height, struct color_element color);
void draw_menu(int x, int y, int width, int height, struct color_element color);
void draw_taskbar(int x, int y, int width, int height, struct color_element color);


#endif