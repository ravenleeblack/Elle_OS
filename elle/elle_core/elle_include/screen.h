#ifndef _screen_h_
#define _screen_h_
#include "memory.h"
#include "port_hub.h"  // Make sure this is included
#include "types.h"


// Function declarations
void enable_cursor_blink(void);
void scroll(void);

void set_csr(bay position);
void move_csr(void);
void clear_screen(void);
void putch(unsigned char c);
void puts(const char *text);
void print_hex(aisle value);
void settextcolor(unsigned char forecolor, unsigned char backcolor);
void load_video(void);
void print_hex(aisle value);

#endif