#ifndef _request_h_
#define _request_h_
#include "types.h"
#include "service.h"

// Request management functions

void load_request(int irq, void (*handler) (registers *req));
void unload_request(int irq);
void handle_core_request(registers *regs);
#endif