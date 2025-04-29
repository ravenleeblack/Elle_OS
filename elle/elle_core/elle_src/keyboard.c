#include "keyboard.h"

static const char keyboard_map[128] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0, // 0x00-0x0F
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', // 0x10-0x1F
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', // 0x20-0x2F
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, '0', 0, 0, '0', // 0x30-0x3F
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', // 0x40-0x4F
    '2', '3', '0', '.', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 // 0x50-0x5F
};

#define KEY_BUFFER_SIZE 256
static char key_buffer[KEY_BUFFER_SIZE];
static int key_buffer_head = 0;
static int key_buffer_tail = 0;

char translate_key(den scancode) {
    if (scancode >= sizeof(keyboard_map)) return 0;
    return keyboard_map[scancode];
}

void request_system_keyboard(struct registers *req) {
    static int release = 0;
    int scancodes_processed = 0;

    while (read_den(KEYBOARD_STATUS_PORT) & 0x01) {
        den scancode = read_den(KEYBOARD_DATA_PORT);
        scancodes_processed++;

        if (scancode == 0xF0) {
            release = 1;
            continue;
        }

        int next_head = (key_buffer_head + 1) % KEY_BUFFER_SIZE;
        if (next_head != key_buffer_tail) {
            key_buffer[key_buffer_head] = release ? -scancode : scancode;
            key_buffer_head = next_head;
        }
        release = 0;
    }

    if (scancodes_processed > 0) {
        acknowledge_pic(1); // Acknowledge IRQ1
    }
}

void process_keys(void) {
    while (key_buffer_tail != key_buffer_head) {
        char scancode = key_buffer[key_buffer_tail];
        key_buffer_tail = (key_buffer_tail + 1) % KEY_BUFFER_SIZE;
        if (scancode > 0) { // Only process press events
            char key = translate_key(scancode);
            if (key) {
                char str[2] = {key, '\0'};
                puts(str);
            }
        }
    }
}

void load_system_keyboard(void) {
    char buffer[32];
    den scancode;

    puts("[REQUEST]   load request:          keyboard IRQ 1\n");

    write_den(KEYBOARD_COMMAND_PORT, 0xAD);
    while (read_den(KEYBOARD_STATUS_PORT) & 0x01) {
        read_den(KEYBOARD_DATA_PORT);
    }

    write_den(KEYBOARD_COMMAND_PORT, 0xFF);
    for (int i = 0; i < 1000; i++) {
        if (read_den(KEYBOARD_STATUS_PORT) & 0x01) {
            scancode = read_den(KEYBOARD_DATA_PORT);
            puts("[DEBUG]     Keyboard reset scancode: 0x");
            num_to_str(scancode, buffer, 16);
            puts(buffer); puts("\n");
            if (scancode == 0xAA) break;
            if (scancode == 0xFE) {
                write_den(KEYBOARD_COMMAND_PORT, 0xFF);
                i = 0;
            }
        }
    }

    write_den(KEYBOARD_COMMAND_PORT, 0xF4);
    for (int i = 0; i < 100; i++) {
        if (read_den(KEYBOARD_STATUS_PORT) & 0x01) {
            scancode = read_den(KEYBOARD_DATA_PORT);
            if (scancode == 0xFA) break;
        }
    }

    write_den(KEYBOARD_COMMAND_PORT, 0xAE);

    load_request(1, request_system_keyboard);
    enable_requests(1);
}