#include "request.h"


void * routine_requests[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void load_request(int irq, void (*handler) (registers *req))
{
    routine_requests[irq] = handler;
}

void unload_request(int irq)
{
    routine_requests[irq] = 0;
}

void handle_core_request(registers *regs)
{
    void (*handler)(registers *regs);

    handler = routine_requests[regs->interrupt_index - 32];

    if(handler)
    {
        handler(regs);
    }

    if(regs->interrupt_index >= 40)
    {
        write_den(0xA0, 0x20);    // Send EOI to slave PIC
    }
    write_den(0x20, 0x20);        // Send EOI to master PIC
}