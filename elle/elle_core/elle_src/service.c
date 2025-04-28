#include "service.h"


const char *exception_messages[] = {
    "service: arith error: division by zero",
    "service: debug service",
    "service: non maskable interrupt",
    "service: debug break point",
    "service: arith: detected overflow",
    "service: memory error: out of bounds",
    "service: asm error: invalid opcode",
    "service: cpu error: no coprocessor",
    "service: cpu error: double fault",
    "service: cpu error: coprocessor segment overrun",
    "service: bad tss",
    "service: memory error: segment not present",
    "service: stack fault",
    "service: cpu error: general protection fault",
    "service: memory error: page fault",
    "service: cpu error: unknown interrupt",
    "service: cpu error: coprocessor fault",
    "service: memory error: alignment check",
    "service: cpu error: machine check",
    "service: reserved 0",
    "service: reserved 1",
    "service: reserved 2",
    "service: reserved 3",
    "service: reserved 4",
    "service: reserved 5",
    "service: reserved 6",
    "service: reserved 7",
    "service: reserved 8",
    "service: reserved 9",
    "service: reserved 10",
    "service: reserved 11",
    "service: reserved 12"
};

void handle_double_fault(registers *regs)
{
    puts("Double Fault!\nError Code: ");
    print_hex(regs->error_code);
    puts("\nEIP: ");
    print_hex(regs->eip);
    puts("\nSystem Halted\n");
    for(;;);
}

void handle_general_protection_fault(registers *regs) 
{
    puts("General Protection Fault!\nError Code: ");
    print_hex(regs->error_code);
    puts("\nEIP: ");
    print_hex(regs->eip);
    puts("\nSystem Halted\n");
    for(;;);
}

void handle_core_service(registers *regs)
{
    puts("[SERVICE]   processing exception: exception occurred\n");
    puts("[SERVICE]   interrupt index:      ");
    print_hex(regs->interrupt_index);
    puts("\n");
    if (regs->interrupt_index < 32)
    {
        puts("[EXCEPTION] ");
        puts(exception_messages[regs->interrupt_index]);
        puts("\n");

        if (regs->interrupt_index == 8 || (regs->interrupt_index >= 10 && regs->interrupt_index <= 14)) {
            puts(" service exception error code: ");
            print_hex(regs->error_code);
            puts("\n");
        }

        puts(" Registers:\n");
        puts(" EAX="); print_hex(regs->eax);
        puts(" EBX="); print_hex(regs->ebx);
        puts(" ECX="); print_hex(regs->ecx);
        puts(" EDX="); print_hex(regs->edx);
        puts("\nESP="); print_hex(regs->esp);
        puts(" EBP="); print_hex(regs->ebp);
        puts(" ESI="); print_hex(regs->esi);
        puts(" EDI="); print_hex(regs->edi);
        puts("\nEIP="); print_hex(regs->eip);
        puts("\nSystem Halted\n");

        for (;;);
    }
    else
    {
        puts("[SERVICE]   non-exception index:  exiting from service\n");
    }
}