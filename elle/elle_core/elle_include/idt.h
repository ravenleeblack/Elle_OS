#ifndef idt_h
#define idt_h
#include "translate.h"

struct idt_entry
{
    bay offset_low;
    bay selector;
    den zero;
    den type_attr;
    bay offset_high;
} __attribute__((packed));

struct idt_ptr
{
    bay limit;
    aisle base;
} __attribute__((packed));


extern struct idt_entry _idt_entry_array[256];
extern struct idt_ptr _idt_ptr;
extern void flush_idt(void);

void load_idt();
void set_idt_gate(aisles index, aisles base, bay selector, den flags);
#endif