#include "request.h"

void * routine_requests[16] = {
    request_0, request_1, request_2, request_3,
    request_4, request_5, request_6, request_7,
    request_8, request_9, request_10, request_11,
    request_12, request_13, request_14, request_15
};

void load_request(int irq, void (*handler)(registers *req)) 
{
    routine_requests[irq] = handler;
}

void unload_request(int irq) 
{
    routine_requests[irq] = 0;
}

void handle_core_request(registers *regs) 
{
    // Check if it's a valid IRQ range (32-47 for IRQ 0-15)
    if (regs->interrupt_index >= 32 && regs->interrupt_index < 48) {
        puts("[REQUEST]   handle request:        dispatching request\n");
        int request = regs->interrupt_index - 32;
        void (*handler)(registers *regs);

        puts("[REQUEST]   irq request:           "); 
        print_hex(regs->interrupt_index); puts("\n");

        if (request >= 0 && request < 16) { // Redundant but kept for clarity
            handler = routine_requests[request];
            if (handler) {
                handler(regs);
            }
            // Acknowledge PIC only for valid IRQs
            if (request >= 8) {
                write_den(0xA0, 0x20); // Slave EOI
            }
            write_den(0x20, 0x20); // Master EOI
        }
    }
    else
    {
        puts("[REQUEST]   unexpected interrupt:  ");
        print_hex(regs->interrupt_index);
        puts(" eip: ");
        print_hex(regs->eip);
        puts("\n");
    }
}
