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
    char buffer[32];
    puts("[SERVICE]   double fault\n");

    puts("[SERVICE]   Register Layout:\n");
    puts("            EAX: "); num_to_str(regs->eax, buffer, 16); puts(buffer); puts("\n");
    puts("            EBX: "); num_to_str(regs->ebx, buffer, 16); puts(buffer); puts("\n");
    puts("            ECX: "); num_to_str(regs->ecx, buffer, 16); puts(buffer); puts("\n");
    puts("            EDX: "); num_to_str(regs->edx, buffer, 16); puts(buffer); puts("\n");
    puts("            ESP: "); num_to_str(regs->esp, buffer, 16); puts(buffer); puts("\n");
    puts("            EBP: "); num_to_str(regs->ebp, buffer, 16); puts(buffer); puts("\n");
    puts("            ESI: "); num_to_str(regs->esi, buffer, 16); puts(buffer); puts("\n");
    puts("            EDI: "); num_to_str(regs->edi, buffer, 16); puts(buffer); puts("\n");
    puts("            EIP: "); num_to_str(regs->eip, buffer, 16); puts(buffer); puts("\n");

    puts("[SERVICE]   System Halted\n");
    for(;;);
}

void handle_general_protection_fault(registers *regs) 
{
    char buffer[32];
    puts("[SERVICE]   general protection fault\n");

    puts("[SERVICE]   Register Layout:\n");
    puts("            EAX: "); num_to_str(regs->eax, buffer, 16); puts(buffer); puts("\n");
    puts("            EBX: "); num_to_str(regs->ebx, buffer, 16); puts(buffer); puts("\n");
    puts("            ECX: "); num_to_str(regs->ecx, buffer, 16); puts(buffer); puts("\n");
    puts("            EDX: "); num_to_str(regs->edx, buffer, 16); puts(buffer); puts("\n");
    puts("            ESP: "); num_to_str(regs->esp, buffer, 16); puts(buffer); puts("\n");
    puts("            EBP: "); num_to_str(regs->ebp, buffer, 16); puts(buffer); puts("\n");
    puts("            ESI: "); num_to_str(regs->esi, buffer, 16); puts(buffer); puts("\n");
    puts("            EDI: "); num_to_str(regs->edi, buffer, 16); puts(buffer); puts("\n");
    puts("            EIP: "); num_to_str(regs->eip, buffer, 16); puts(buffer); puts("\n");

    puts("[SERVICE]   System Halted\n");
    for(;;);
}

void handle_core_service(registers *regs)
{
    char buffer[32];
    puts("[SERVICE]   processing exception: exception occurred\n");
    puts("[SERVICE]   interrupt index:      ");
    num_to_str(regs->interrupt_index, buffer, 16);
    puts(buffer); puts("\n");

    if (regs->interrupt_index < 32)
    {
        puts("[EXCEPTION] ");
        puts(exception_messages[regs->interrupt_index]);
        puts("\n\n");

        if (regs->interrupt_index == 8 || (regs->interrupt_index >= 10 && regs->interrupt_index <= 14)) {
            puts(" service exception error code: ");
            num_to_str(regs->error_code, buffer, 16);
            puts(buffer); puts("\n");
        }

        puts("[SERVICE]   Register Layout:\n");
        puts("            EAX: "); num_to_str(regs->eax, buffer, 16); puts(buffer); puts("\n");
        puts("            EBX: "); num_to_str(regs->ebx, buffer, 16); puts(buffer); puts("\n");
        puts("            ECX: "); num_to_str(regs->ecx, buffer, 16); puts(buffer); puts("\n");
        puts("            EDX: "); num_to_str(regs->edx, buffer, 16); puts(buffer); puts("\n");
        puts("            ESP: "); num_to_str(regs->esp, buffer, 16); puts(buffer); puts("\n");
        puts("            EBP: "); num_to_str(regs->ebp, buffer, 16); puts(buffer); puts("\n");
        puts("            ESI: "); num_to_str(regs->esi, buffer, 16); puts(buffer); puts("\n");
        puts("            EDI: "); num_to_str(regs->edi, buffer, 16); puts(buffer); puts("\n");
        puts("            EIP: "); num_to_str(regs->eip, buffer, 16); puts(buffer); puts("\n");

        puts("[SERVICE]   Continuing for debug\n");
        return;
    }
    else
    {
        puts("[SERVICE]   non-exception index:  exiting from service\n");
    }
}