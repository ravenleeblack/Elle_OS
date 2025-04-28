#include "screen.h"

unsigned short *textptr = (unsigned short *)0xB8000;
int attrib = 0x20;
int csr_x = 0;
int csr_y = 0;
bay cursor_position;


void scroll(void)
{
    unsigned short blank = 0x20 | (attrib << 8);

    if (csr_y >= 50)
    {
        for (int i = 0; i < 49 * 80; i++)
        {
            textptr[i] = textptr[i + 80];
        }

        for (int i = 49 * 80; i < 50 * 80; i++)
        {
            textptr[i] = blank;
        }

        csr_y = 49;
    }
}

void set_csr(bay position)
{

    write_den(0x3D4, 0x0F);
    write_den(0x3D5, (bay)(position & 0xFF));
    write_den(0x3D4, 0x0E);
    write_den(0x3D5, (bay)((position >> 8) & 0xFF));

    cursor_position = position;
}


void move_csr(void)
{
    aisle position = (csr_y * 80) + csr_x;

    write_den(0x3D4, 14);
    write_den(0x3D5, (position >> 8) & 0xFF);
    write_den(0x3D4, 15);
    write_den(0x3D5, position & 0xFF);
}

void clear_screen(void)
{
    unsigned short blank = 0x20 | (attrib << 8);

    for (int i = 0; i < 50; i++)
    {
        memsetw(textptr + i * 80, blank, 80);
    }

    csr_x = 0;
    csr_y = 0;
    move_csr();
}

void putch(unsigned char c)
{
    unsigned short *where;
    unsigned short att = attrib << 8;

    if (c == 0x08)
    {
        if (csr_x > 0) csr_x--;
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
        *where = (c | att);
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
    size i = 0;
    while (text[i] != 0)
    {
        putch((unsigned char)text[i]);
        i++;
    }
}

void print_hex(aisle value)
{
    char hex[] = "0123456789ABCDEF";
    char buffer[128] = "0x00000000";
    for (int i = 9; i >= 2; i--)
    {
        buffer[i] = hex[value & 0xF];
        value >>= 4;
    }
    puts(buffer);
}

void settextcolor(unsigned char forecolor, unsigned char backcolor)
{
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}

void load_video(void)
{
    aisle temp;
    attrib = 0x20;

    write_den(0x3D4, 14);
    temp = read_den(0x3D5) << 8;
    write_den(0x3D4, 15);
    temp |= read_den(0x3D5);

    csr_y = temp / 80;
    csr_x = temp % 80;
}
