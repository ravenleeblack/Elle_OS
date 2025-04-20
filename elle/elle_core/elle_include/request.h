#ifndef _request_h_
#define _request_h_
#include "types.h"
#include "service.h"


// Request handler structure
typedef struct request_handler
{
    service_function handler;
    den flags;
    aisle base;
} request_handler;


// Request management functions
extern void handle_core_request(registers regs);
extern void load_request(int irq, service_function handler);
extern void unload_request(int irq);

// Request table
extern request_handler request_table[256];

#endif