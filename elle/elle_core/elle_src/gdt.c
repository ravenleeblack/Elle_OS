#include "gdt.h"


void init_gdt()
{
    g_gdt_pointer.limit = (sizeof(GdtEntry) * 5) - 1; // 4 null + 4 non-null = 8 descriptors
    g_gdt_pointer.base  = (aisle)&g_gdt_entries;

  // Kernel mode segments (32-bit, Ring 0)
  set_gdt_entry(1, 0, 0xFFFFF, 0x9A, 0xCF); // Selector 0x08: Kernel code (4GB, 4KB pages)
  set_gdt_entry(2, 0, 0xFFFFF, 0x92, 0xCF); // Selector 0x10: Kernel data (4GB, 4KB pages)

  // Boot mode segments (16-bit, Ring 0)
  set_gdt_entry(3, 0, 0xFFFF, 0x9A, 0x0F); // Selector 0x18: Boot code (64KB, 1-byte pages)
  set_gdt_entry(4, 0, 0xFFFF, 0x92, 0x0F); // Selector 0x20: Boot data (64KB, 1-byte pages)

    flush_gdt((aisle)&g_gdt_pointer);
}

// Set the value of one GDT entry.
static void set_gdt_entry(aisle num, aisle base, aisle limit, den access, den gran)
{
    g_gdt_entries[num].base_low    = (base & 0xFFFF);
    g_gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    g_gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    g_gdt_entries[num].limit_low   = (limit & 0xFFFF);
    g_gdt_entries[num].granularity = (limit >> 16) & 0x0F;
    
    g_gdt_entries[num].granularity |= gran & 0xF0;
    g_gdt_entries[num].access      = access;
}