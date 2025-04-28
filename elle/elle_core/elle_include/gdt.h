#ifndef gdt_h
#define gdt_h
#include "translate.h"
#include "service.h"
#include "types.h"

extern aisle start_stack;
extern aisle end_stack;

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
    bay limit;            // Upper 16 bits must be zero, lower 16 bits = size - 1
    aisles base;          // 32-bit base address of GDT
} __attribute__((packed));

// TSS structure
struct tss_entry
{
    aisles prev_tss;        // Previous TSS - unused with software task switching
    aisles esp0;            // Kernel stack pointer
    aisles ss0;             // Kernel stack segment
    aisles esp1;            // Unused...
    aisles ss1;
    aisles esp2;
    aisles ss2;
    aisles cr3;
    aisles eip;
    aisles eflags;
    aisles eax;
    aisles ecx;
    aisles edx;
    aisles ebx;
    aisles esp;
    aisles ebp;
    aisles esi;
    aisles edi;
    aisles es;
    aisles cs;
    aisles ss;
    aisles ds;
    aisles fs;
    aisles gs;
    aisles ldt;
    bay iomap_base;
} __attribute__((packed));

// GDT entries array - space for null, kernel code, kernel data, user code, user data, TSS
extern struct gdt_entry _gdt_entry_array[5];
extern struct gdt_ptr _gdt_ptr;
extern struct tss_entry _tss;
extern void flush_gdt(void);
extern void flush_tss(void);

// C functions to set up GDT
void load_gdt(void);
void set_gdt_gate(aisles num, aisle base, aisle limit, bay access, bay gran);

#endif