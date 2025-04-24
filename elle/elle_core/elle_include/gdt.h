#ifndef gdt_h
#define gdt_h
#include "translate.h"
#include "service.h"

// GDT entry structure
struct gdt_entry
{
    bay  limit_low;           // Lower 16 bits of limit
    bay  base_low;           // Lower 16 bits of base
    den  base_middle;        // Middle 8 bits of base
    den  access;            // Access flags
    den  granularity;       // Granularity and upper 4 bits of limit
    den  base_high;         // Upper 8 bits of base
} __attribute__((packed));

// GDT pointer structure (6 bytes)
struct gdt_ptr
{
    aisle limit;            // Upper 16 bits must be zero, lower 16 bits = size - 1
    aisle base;            // 32-bit base address of GDT
} __attribute__((packed));

// TSS structure
struct tss_entry
{
    aisle prev_tss;        // Previous TSS - unused with software task switching
    aisle esp0;            // Kernel stack pointer
    bay ss0;              // Kernel stack segment
    aisle esp1;           // Unused...
    bay ss1;
    aisle esp2;
    bay ss2;
    aisle cr3;
    aisle eip;
    aisle eflags;
    aisle eax;
    aisle ecx;
    aisle edx;
    aisle ebx;
    aisle esp;
    aisle ebp;
    aisle esi;
    aisle edi;
    bay es;
    bay cs;
    bay ss;
    bay ds;
    bay fs;
    bay gs;
    bay ldt;
    bay trap;
    aisle iomap_base;
} __attribute__((packed));

// GDT entries array - space for null, kernel code, kernel data, user code, user data, TSS
extern struct gdt_entry _gdt_entry_array[6];
extern struct gdt_ptr _gdt_ptr;
extern struct tss_entry _tss;

// Assembly function to load GDT
extern void flush_gdt(aisle);
extern int end_stack; // Placeholder for the end of the stack


// C functions to set up GDT
void load_gdt(void);
void set_gdt_gate(aisles num, aisles base, aisles limit, den access, den gran);

#endif