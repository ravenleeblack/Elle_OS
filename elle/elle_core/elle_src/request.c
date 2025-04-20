#include "request.h"

service_function handle_interrupt[256];
aisle request_count = 0;


void load_request(int irq, service_function handler)
{
    handle_interrupt[irq] = handler;
}

void unload_request(int irq)
{
     handle_interrupt[irq] = 0;
}

void handle_core_request(registers regs)
{
     request_count++;
    
    // end of interrupt message
    if (regs.interrupt_index >= 40)
    {
        //slave PIC
        write_den(0xA0, 0x20);
    }

    write_den(0x20, 0x20);

    //Screen_PrintF("irq: %d\n", regs.int_no);

    if (handle_interrupt[regs.interrupt_index] != 0)
    {
     service_function handler = handle_interrupt[regs.interrupt_index];
        handler(&regs);
    }
    else
    {
        //printkf("unhandled IRQ: %d\n", regs.interruptNumber);
    }
    
}