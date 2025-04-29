#include "request.h"

void *routine_requests[16] = {0};

void load_request(int irq, void (*handler)(registers *req)) 
{
    char buffer[32];
    routine_requests[irq] = handler;
    puts("[DEBUG]     Registering IRQ ");
    num_to_str(irq, buffer, 10);
    puts(buffer); puts(" handler 0x");
    num_to_str((aisle)handler, buffer, 16);
    puts(buffer); puts("\n");
    set_idt_gate(32 + irq, (aisle)handler, 0x08, 0x8E);
    puts("[DEBUG]     Set IDT gate ");
    num_to_str(32 + irq, buffer, 10);
    puts(buffer); puts(" to handler 0x");
    num_to_str((aisle)handler, buffer, 16);
    puts(buffer); puts("\n");
}

void unload_request(int irq) 
{
    routine_requests[irq] = 0;
}

void handle_core_request(registers *regs) 
{
    char buffer[32];
    if (regs->interrupt_index >= 32 && regs->interrupt_index < 48) {
        puts("[REQUEST]   handle request:        dispatching request\n");
        int request = regs->interrupt_index - 32;
        void (*handler)(registers *regs);

        puts("[REQUEST]   irq request:           "); 
        num_to_str(regs->interrupt_index, buffer, 16);
        puts(buffer); puts("\n");

        if (regs->interrupt_index == 33) {
            puts("[DEBUG]     IRQ 1 reached handle_core_request\n");
        }

        if (request >= 0 && request < 16) {
            handler = routine_requests[request];
            if (handler) {
                handler(regs);
            }
            if (request >= 8) {
                write_den(PIC_SLAVE_CTRL, 0x20);
            }
            write_den(PIC_MASTER_CTRL, 0x20);
        }
    } else if (regs->interrupt_index == 7 || regs->interrupt_index == 15) {
        puts("[REQUEST]   Spurious interrupt:    ");
        num_to_str(regs->interrupt_index, buffer, 16);
        puts(buffer); puts("\n");
    } else {
        puts("[REQUEST]   unexpected interrupt:  ");
        num_to_str(regs->interrupt_index, buffer, 16);
        puts(buffer); puts("\n");

        puts("[REQUEST]   Register Layout:\n");
        puts("            EAX: "); num_to_str(regs->eax, buffer, 16); puts(buffer); puts("\n");
        puts("            EBX: "); num_to_str(regs->ebx, buffer, 16); puts(buffer); puts("\n");
        puts("            ECX: "); num_to_str(regs->ecx, buffer, 16); puts(buffer); puts("\n");
        puts("            EDX: "); num_to_str(regs->edx, buffer, 16); puts(buffer); puts("\n");
        puts("            ESP: "); num_to_str(regs->esp, buffer, 16); puts(buffer); puts("\n");
        puts("            EBP: "); num_to_str(regs->ebp, buffer, 16); puts(buffer); puts("\n");
        puts("            ESI: "); num_to_str(regs->esi, buffer, 16); puts(buffer); puts("\n");
        puts("            EDI: "); num_to_str(regs->edi, buffer, 16); puts(buffer); puts("\n");
        puts("            EIP: "); num_to_str(regs->eip, buffer, 16); puts(buffer); puts("\n");

        puts("[REQUEST]   Ignoring unexpected interrupt for debug\n");
        acknowledge_pic(0);
    }
    asm("sti"); // Ensure interrupts are re-enabled
}