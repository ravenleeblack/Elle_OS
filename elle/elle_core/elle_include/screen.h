#ifndef _screen_h_
#define _screen_h_
#include "memory.h"
#include "port_hub.h"  // Make sure this is included
#include "types.h"



// Function declarations
void scroll(void);
void move_csr(void);
void clear_screen(void);
void putch(unsigned char c);
void puts(const char *text);
void init_video(void);


void settextcolor(unsigned char forecolor, unsigned char backcolor);


#endif