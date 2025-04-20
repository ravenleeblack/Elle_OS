#include "service.h"

aisle service_count = 0;


static void handle_double_fault(registers *regs);
static void handle_general_protection_fault(registers *regs);


static void handle_double_fault(registers *regs)
 {
    //printf("Double Fault! Error code: %x\n", regs->error_code);
    //for (;;) asm("hlt"); // Halt the system
}

static void handle_general_protection_fault(registers *regs) {
    //printf("General Protection Fault! Error code: %x, EIP: %x\n", 
           //regs->error_code, regs->eip);
   // for (;;) asm("hlt"); // Halt the system
}


void handle_core_service(registers regs)
{
    //Screen_PrintF("handle_isr interrupt no:%d\n", regs.int_no);

    service_count++;

    den int_no = regs.interrupt_index & 0xFF;

    if (handle_interrupt[int_no] != 0)
    {
        service_function handler = handle_interrupt[int_no];
        handler(&regs);
    }
    else
    {
        //printf("unhandled interrupt: %d\n", int_no);
        //printf("Tick: %d\n", get_system_tick_count());
        //printf("unhandled interrupt\n");
    }
}