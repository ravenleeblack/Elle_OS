#include "gdt.h"
#include "memory.h"


struct gdt_entry _gdt_entry_array[5];
struct gdt_ptr _gdt_ptr;
struct tss_entry _tss;


void load_gdt(void) {
    // Initialize TSS
    memset(&_tss, 0, sizeof(struct tss_entry));
    _tss.ss0 = 0x10;  // Kernel data segment
    _tss.esp0 = (aisle)&end_stack;
    
    // Set up GDT entries
    set_gdt_gate(0, 0, 0, 0, 0);                // Null segment
    set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    set_gdt_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    set_gdt_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment
    
    // Set up TSS entry
    aisle base = (aisle)&_tss;
    aisle limit = sizeof(struct tss_entry);
    set_gdt_gate(5, base, limit, 0x89, 0x00);   // TSS entry
    
    _gdt_ptr.limit = (sizeof(struct gdt_entry) * 6) - 1;
    _gdt_ptr.base = (aisle)&_gdt_entry_array;
    
    flush_gdt();
    flush_tss();  // Load TSS after GDT is set up
}

void set_gdt_gate(aisles num, aisle base, aisle limit, bay access, bay gran) {
    _gdt_entry_array[num].base_low = (base & 0xFFFF);
    _gdt_entry_array[num].base_middle = (base >> 16) & 0xFF;
    _gdt_entry_array[num].base_high = (base >> 24) & 0xFF;
    
    _gdt_entry_array[num].limit_low = (limit & 0xFFFF);
    _gdt_entry_array[num].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    _gdt_entry_array[num].access = access;
}