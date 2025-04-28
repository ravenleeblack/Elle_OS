#include "keyboard.h"


unsigned char keyboard_map[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\0', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void request_system_keyboard(registers *regs) 
{
    den scancode = read_den(0x60); // Read keyboard data port

    if (!(scancode & 0x80)) { // Key pressed (not released)
        putch(keyboard_map[scancode]);
    }

    acknowledge_pic(1); // Acknowledge IRQ 1 (keyboard)
}

void load_system_keyboard(void) 
{
    puts("[REQUEST]   load request:          keyboard IRQ 1\n");

    load_request(1, request_system_keyboard); // Register handler for IRQ 1
    enable_requests(1); // Enable IRQ 1
}