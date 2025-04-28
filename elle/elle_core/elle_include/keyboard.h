#ifndef _keyboard_h_
#define _keyboard_h_
#include "request.h"
#include "port_hub.h"
#include "font.h"
#include "ascii.h"
#include "screen.h"

void load_request(int irq, void (*handler)(registers *req));
void request_system_keyboard(registers *regs);
void load_system_keyboard(void);



#endif