#ifndef _keyboard_h_
#define _keyboard_h_
#include "request.h"
#include "port_hub.h"
#include "font.h"
#include "ascii.h"
#include "screen.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_COMMAND_PORT 0x64


void load_request(int irq, void (*handler)(registers *req));

char translate_key(den scancode);
void request_system_keyboard(registers *req);
void load_system_keyboard(void);



#endif