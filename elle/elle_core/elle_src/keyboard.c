#include "keyboard.h"


unsigned char keyboard_map[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\0',
    '\t',
    'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
     0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/', 0,
    '*',
    0,
    ' ',
    0,
	0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0,
	0,
	0,
	0,
	0,
	0,
	'-',
	0,
	0,
	0,
	'+',
	0,
	0,
	0,
	0,
	0,
	0, 0, 0,
	0,
	0,
	0 };

void request_keyboard(registers regs)  // Changed from (int i, int intr_code)
{
    unsigned char scancode;
    char keychar[2];

	
    scancode = read_den(0x60);

    while (scancode & 1 && (scancode & 0x20) == 0)
    {
        den keycode = read_den(0x60);
        den scan_code = keycode & 0x7f;
        den key_state = !(keycode & 0x80);

        if (key_state)
        {
              // Convert single char to null-terminated string
            keychar[0] = keyboard_map[(unsigned char)scan_code];
            keychar[1] = '\0';
            puts(keychar);  // Now passing a proper string
        }

        scancode = read_den(0x64);
    }
    write_den(0x20, 0x20);
}

void load_keyboard()
{
    load_request(1, request_keyboard);
}