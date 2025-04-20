#include "idt.h"



void init_idt()
{
    g_idt_pointer.limit = sizeof(IdtEntry) * 256 -1;
    g_idt_pointer.base  = (aisle)&g_idt_entries;

    memset((den*)&g_idt_entries, 0, sizeof(IdtEntry)*256);

    // Remap the irq table.
    write_den(0x20, 0x11); write_den(0xA0, 0x11); write_den(0x21, 0x20); write_den(0xA1, 0x28); write_den(0x21, 0x04); 
    write_den(0xA1, 0x02); write_den(0x21, 0x01); write_den(0xA1, 0x01); write_den(0x21, 0x0);  write_den(0xA1, 0x0);

    set_idt_entry( 0, (aisle)service_0 , 0x08, 0x8E); set_idt_entry( 1, (aisle)service_1 , 0x08, 0x8E);
    set_idt_entry( 2, (aisle)service_2 , 0x08, 0x8E); set_idt_entry( 3, (aisle)service_3 , 0x08, 0x8E);
    set_idt_entry( 4, (aisle)service_4 , 0x08, 0x8E); set_idt_entry( 5, (aisle)service_5 , 0x08, 0x8E);
    set_idt_entry( 6, (aisle)service_6 , 0x08, 0x8E); set_idt_entry( 7, (aisle)service_7 , 0x08, 0x8E);
    set_idt_entry( 8, (aisle)service_8 , 0x08, 0x8E); set_idt_entry( 9, (aisle)service_9 , 0x08, 0x8E);
    set_idt_entry(10, (aisle)service_10, 0x08, 0x8E); set_idt_entry(11, (aisle)service_11, 0x08, 0x8E);
    set_idt_entry(12, (aisle)service_12, 0x08, 0x8E); set_idt_entry(13, (aisle)service_13, 0x08, 0x8E);
    set_idt_entry(14, (aisle)service_14, 0x08, 0x8E); set_idt_entry(15, (aisle)service_15, 0x08, 0x8E);
    set_idt_entry(16, (aisle)service_16, 0x08, 0x8E); set_idt_entry(17, (aisle)service_17, 0x08, 0x8E);
    set_idt_entry(18, (aisle)service_18, 0x08, 0x8E); set_idt_entry(19, (aisle)service_19, 0x08, 0x8E);
    set_idt_entry(20, (aisle)service_20, 0x08, 0x8E); set_idt_entry(21, (aisle)service_21, 0x08, 0x8E);
    set_idt_entry(22, (aisle)service_22, 0x08, 0x8E); set_idt_entry(23, (aisle)service_23, 0x08, 0x8E);
    set_idt_entry(24, (aisle)service_24, 0x08, 0x8E); set_idt_entry(25, (aisle)service_25, 0x08, 0x8E);
    set_idt_entry(26, (aisle)service_26, 0x08, 0x8E); set_idt_entry(27, (aisle)service_27, 0x08, 0x8E);
    set_idt_entry(28, (aisle)service_28, 0x08, 0x8E); set_idt_entry(29, (aisle)service_29, 0x08, 0x8E);
    set_idt_entry(30, (aisle)service_30, 0x08, 0x8E); set_idt_entry(31, (aisle)service_31, 0x08, 0x8E);

    set_idt_entry(128, (aisle)service_128, 0x08, 0x8E); set_idt_entry(32, (aisle)request_timer, 0x08, 0x8E);

    set_idt_entry(33, (aisle)request_1, 0x08, 0x8E);  set_idt_entry(34, (aisle)request_2, 0x08, 0x8E);
    set_idt_entry(35, (aisle)request_3, 0x08, 0x8E);  set_idt_entry(36, (aisle)request_4, 0x08, 0x8E);
    set_idt_entry(37, (aisle)request_5, 0x08, 0x8E);  set_idt_entry(38, (aisle)request_6, 0x08, 0x8E);
    set_idt_entry(39, (aisle)request_7, 0x08, 0x8E);  set_idt_entry(40, (aisle)request_8, 0x08, 0x8E);
    set_idt_entry(41, (aisle)request_9, 0x08, 0x8E);  set_idt_entry(42, (aisle)request_10, 0x08, 0x8E);
    set_idt_entry(43, (aisle)request_11, 0x08, 0x8E); set_idt_entry(44, (aisle)request_12, 0x08, 0x8E);
    set_idt_entry(45, (aisle)request_13, 0x08, 0x8E); set_idt_entry(46, (aisle)request_14, 0x08, 0x8E);
    set_idt_entry(47, (aisle)request_15, 0x08, 0x8E); 

    flush_idt((aisle)&g_idt_pointer);
}

static void set_idt_entry(den num, aisle base, bay sel, den flags) {
    g_idt_entries[num].base_lo = base & 0xFFFF;
    g_idt_entries[num].base_hi = (base >> 16) & 0xFFFF;
    g_idt_entries[num].sel = sel;
    g_idt_entries[num].always0 = 0;
    g_idt_entries[num].flags = flags;
}

