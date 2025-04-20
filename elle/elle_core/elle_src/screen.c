#include "screen.h"

// screen.c functions are for text mode support and testing. Elle is currently using graphics mode so refer to draw_element.c for its functions
// and vesa video buffer. I left this here so we could continue testing from text mode if needed.

unsigned short *textptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;

void scroll(void)
{
    unsigned short blank = 0x20 | (attrib << 8);

    if(csr_y >= 50)
    {
        // Move lines up manually
        for(int i = 0; i < 49 * 80; i++) {
            textptr[i] = textptr[i + 80];
        }

        // Clear last line
        for(int i = 49 * 80; i < 50 * 80; i++) {
            textptr[i] = blank;
        }

        csr_y = 49;
    }
}


void move_csr(void)
{
    unsigned temp;
    temp = csr_y * 80 + csr_x;

    write_den(0x3D4, 14);
    write_den(0x3D5, temp >> 8);
    write_den(0x3D4, 15);
    write_den(0x3D5, temp);
}

void clear_screen(void)
{
    unsigned short blank = 0x20 | (attrib << 8);
    unsigned short *ptr = textptr;
    
    // Direct write to video memory
    for(int i = 0; i < 80 * 50; i++) {
        *ptr++ = blank;
    }
    
    csr_x = 0;
    csr_y = 0;
    move_csr();
}

void putch(unsigned char c)
{
     unsigned short *where;
     unsigned att = attrib << 8;
	
     if (c == 0x08)
     {
	if (csr_x != 0) csr_x--;
     }
     else if (c == 0x09)
     {
	csr_x = (csr_x + 8) & ~(8 - 1);
     }
     else if (c == '\r')
     {
	csr_x = 0;
     }
     else if (c == '\n')
     {
	csr_x = 0;
	csr_y++;
     }
     else if (c >= ' ')
     {
	where = textptr + (csr_y * 80 + csr_x);
	*where = c | att;	/* Character AND attributes: color */
	csr_x++;
     }
     if (csr_x >= 80)
     {
        csr_x = 0;
	csr_y++;
     }
     scroll();
     move_csr();
}


void puts(const char *text)
{
    int i;

    for (i = 0; i < strlen(text); i++)
    {
	    putch((unsigned char)text[i]);
    }
}

void init_video(void)
{
    // Set up text mode video buffer
    textptr = (unsigned short *)0xB8000;
    attrib = 0x0F;  // White on black

    // Clear screen to ensure clean state
    clear_screen();

    // Initialize cursor position
    csr_x = 0;
    csr_y = 0;
    move_csr();
}