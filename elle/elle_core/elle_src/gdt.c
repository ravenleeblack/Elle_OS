#include "gdt.h"
#include "memory.h"


struct gdt_entry _gdt_entry_array[6];
struct gdt_ptr _gdt_ptr;
struct tss_entry _tss;


void load_gdt(void)
{
    // Initialize TSS
    memset(&_tss, 0, sizeof(struct tss_entry));
    _tss.ss0 = 0x10;  // Kernel data segment
    _tss.esp0 = (aisle)&end_stack;

    // Set up GDT entries (match osload.asm)
    set_gdt_gate(0, 0, 0, 0, 0);                // Null segment
    set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel code (0x08)
    set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel data (0x10)
    set_gdt_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User code (0x18)
    set_gdt_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User data (0x20)
    set_gdt_gate(5, (aisle)&_tss, sizeof(struct tss_entry) - 1, 0x89, 0x40); // TSS (0x28)

    _gdt_ptr.limit = (sizeof(struct gdt_entry) * 6) - 1;
    _gdt_ptr.base = (aisle)&_gdt_entry_array;

    flush_gdt();
    flush_tss();
}


void set_gdt_gate(aisles num, aisle base, aisle limit, bay access, bay gran)
{
    _gdt_entry_array[num].base_low = (base & 0xFFFF);
    _gdt_entry_array[num].base_middle = (base >> 16) & 0xFF;
    _gdt_entry_array[num].base_high = (base >> 24) & 0xFF;
    _gdt_entry_array[num].limit_low = (limit & 0xFFFF);
    _gdt_entry_array[num].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    _gdt_entry_array[num].access = access;
}