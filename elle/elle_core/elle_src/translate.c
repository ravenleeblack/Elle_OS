#include "translate.h"

void handle_core_service(registers *regs);
extern void *routine_requests[16];


void remap_pic(void)
{
    char buffer[32];

    // Save masks
    den master_mask = read_den(0x21);
    den slave_mask = read_den(0xA1);

    // ICW1: Initialize PICs
    write_den(0x20, 0x11); // Master PIC
    write_den(0xA0, 0x11); // Slave PIC

    // ICW2: Vector offsets
    write_den(0x21, 0x20); // Master starts at 0x20
    write_den(0xA1, 0x28); // Slave starts at 0x28

    // ICW3: Master-slave wiring
    write_den(0x21, 0x04); // Master has slave at IRQ2
    write_den(0xA1, 0x02); // Slave ID

    // ICW4: 8086 mode
    write_den(0x21, 0x01);
    write_den(0xA1, 0x01);

    // Restore masks
    write_den(0x21, master_mask);
    write_den(0xA1, slave_mask);

    // Debug
    puts("[DEBUG]     PIC Master Vector: 0x");
    num_to_str(0x20, buffer, 16);
    puts(buffer); puts("\n");
}

void enable_requests(den irq)
{
    char buffer[32];
    den port = (irq < 8) ? 0x21 : 0xA1;
    den mask = read_den(port);
    mask &= ~(1 << (irq & 7));
    write_den(port, mask);
    puts("[PIC]       enable request:        checking mask request\n");
    puts("[DEBUG]     New PIC Master Mask: 0x");
    num_to_str(read_den(0x21), buffer, 16);
    puts(buffer); puts("\n");

    // Acknowledge PIC to clear pending IRQs
    if (irq >= 8)
        write_den(0xA0, 0x20);
    write_den(0x20, 0x20);
}

void acknowledge_pic(den irq)
{
    if (irq >= 8)
        write_den(0xA0, 0x20);
    write_den(0x20, 0x20);
}

void load_pre_requests(void) 
{
    remap_pic();
}

void load_pre_services(void) 
{
    char buffer[32];
    for (int i = 0; i < 32; i++)
    {
        aisle base = (aisle)service_0 + i * ((aisle)service_1 - (aisle)service_0);
        set_idt_gate((bay)i, base, 0x08, 0x8F);
        if (i == 0) {
            puts("[DEBUG]     IDT 0 handler: 0x");
            num_to_str(base, buffer, 16);
            puts(buffer); puts("\n");
        }
    }
    extern void service_128();
    set_idt_gate((bay)128, (aisle)service_128, 0x08, 0xEF);
}