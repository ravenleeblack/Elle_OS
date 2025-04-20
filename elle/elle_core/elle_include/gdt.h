#ifndef gdt_h
#define gdt_h
#include "types.h"
#include "service.h"
#include "memory.h"
#include "port_hub.h"


struct GdtEntry
{
    bay limit_low;
    bay base_low;
    den  base_middle;
    den  access;
    den  granularity;
    den  base_high;
} __attribute__((packed));

typedef struct GdtEntry GdtEntry;


struct GdtPointer
{
    bay limit;
    aisle base;
} __attribute__((packed));

typedef struct GdtPointer GdtPointer;


extern void flush_gdt(aisle);


void init_gdt();
static void set_gdt_entry(aisle num, aisle base, aisle limit, den access, den gran);

GdtEntry g_gdt_entries[5];
GdtPointer g_gdt_pointer;


#endif