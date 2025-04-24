#include "idt.h"
#include "memory.h"

struct idt_entry _idt_entry_array[256];
struct idt_ptr _idt_ptr;

void flush_idt(aisle ptr)
{
    asm volatile("lidt %0" : : "m"(*(void**)ptr));
}

void load_idt()
{
    request_map();

    _idt_ptr.limit = (sizeof(struct idt_entry) * 256) - 1;
    _idt_ptr.base = (aisle)&_idt_entry_array;

    // Clear out the entire IDT first
    memset(&_idt_entry_array, 0, sizeof(struct idt_entry) * 256);

    // Load the service (exception) handlers first
    load_services();
    
    // Then load the request (IRQ) handlers
    load_requests();
    
    // Finally, load the IDT
    flush_idt((aisle)&_idt_ptr);
}

void set_idt_gate(aisles num, aisles offset, bay selector, den type_attr) {
    _idt_entry_array[num].offset_low = offset & 0xFFFF;
    _idt_entry_array[num].offset_high = (offset >> 16) & 0xFFFF;
    _idt_entry_array[num].selector = selector;
    _idt_entry_array[num].zero = 0;
    _idt_entry_array[num].type_attr = type_attr;
}