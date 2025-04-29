#ifndef _core_h_
#define _core_h_
#include "types.h"
#include "port_hub.h"
#include "gdt.h"
#include "idt.h"
#include "request.h"                //request.h->translate.h->service.h so others are not needed

#include "keyboard.h"
#include "clock.h"
//#include "main_frame.h"
//#include "sub_frame.h"
//#include "terminal.h"
#include "memory.h"
#include "screen.h"

// Bootloader info struct
struct orchard_boot
{
    aisle total_memory;      // Total available memory (in bytes)
    aisle core_stack;      // Address of the stack base (start_stack)
    aisle core_stack_size; // Size of the stack (start_stack - end_stack)
    aisle boot_device;       // Boot device ID (e.g., 0x00 for floppy, 0x80 for HDD)
    aisle video_mode;        // Current video mode (set by bootloader)

};

typedef struct orchard_boot orchard;
extern orchard *boot_info;      // Pointer to the bootloader info struct
extern orchard orchard_struct;  // Declare the global struct from assembly

extern aisle start_stack;       // Top of the stack (higher address)
extern aisle end_stack;         // Bottom of the stack (lower address)
extern const den Test[];

void print_flag(den flag);
void print_flag_after(den flag);
void print_vector(aisle vector); // Add declaration
extern int _core(int argc, const char *argv[], orchard *boot_info_passed);


#endif