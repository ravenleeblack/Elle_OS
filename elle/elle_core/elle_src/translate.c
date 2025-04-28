#include "translate.h"

void handle_core_service(registers *regs);


#define PIC_MASTER_CTRL 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CTRL  0xA0
#define PIC_SLAVE_DATA  0xA1


void remap_pic(void) 
{
    // Save current masks
    unsigned char master_mask = read_den(PIC_MASTER_DATA);
    unsigned char slave_mask = read_den(PIC_SLAVE_DATA);

    // ICW1: Start initialization
    write_den(PIC_MASTER_CTRL, 0x11); // 0x11 = init + ICW4 needed
    write_den(PIC_SLAVE_CTRL, 0x11);

    // ICW2: Set vector offsets
    write_den(PIC_MASTER_DATA, 0x20); // Master IRQs at 32-39
    write_den(PIC_SLAVE_DATA, 0x28);  // Slave IRQs at 40-47

    // ICW3: Master/Slave wiring
    write_den(PIC_MASTER_DATA, 0x04); // Master has slave at IRQ2 (bit 2)
    write_den(PIC_SLAVE_DATA, 0x02);  // Slave ID 2

    // ICW4: 8086 mode
    write_den(PIC_MASTER_DATA, 0x01); // 8086/88 mode
    write_den(PIC_SLAVE_DATA, 0x01);

    // Restore masks (initially mask all IRQs)
    write_den(PIC_MASTER_DATA, master_mask);
    write_den(PIC_SLAVE_DATA, slave_mask);
}


static bay mask_request = 0xFFFC;

void enable_requests(den irq)
{
    puts("[PIC]       enable request:        checking mask request\n");
	mask_request &= (bay)~((1 << irq));

	if (irq < 8)
    {
        write_den(PIC_MASTER_DATA, (den)(mask_request & 0xFF));
    }
	else
    {
        write_den(PIC_SLAVE_DATA, (den)(mask_request >> 8));
    }
}

void acknowledge_pic(unsigned char irq)
{
    puts("[PIC]       acknowledge request:   determining pic m/s for request\n");
   
    if (irq >= 8) {
        // IRQs 8-15: Acknowledge slave first, then master
        write_den(PIC_SLAVE_CTRL, 0x20); // EOI to slave
    }
    write_den(PIC_MASTER_CTRL, 0x20); // EOI to master
}


void load_pre_requests(void) 
{
    remap_pic(); // Remap the PIC to avoid conflicts with exceptions
    for(int i = 0; i < 16; i++) {
        // All IRQ vectors point to the central dispatcher
        set_idt_gate(32 + i, (aisle)handle_core_request, 0x08, 0x8E);
    }
}

void load_pre_services(void) 
{
    for(int i = 0; i < 32; i++) 
    {
        set_idt_gate(i, (aisle)handle_core_service, 0x08, 0x8F);
    }
    set_idt_gate(128, (aisle)handle_core_service, 0x08, 0xEF);  
}
