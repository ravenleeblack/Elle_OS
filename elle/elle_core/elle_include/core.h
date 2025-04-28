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

struct memory_entry {
    aisle base;
    aisle length;
    aisle type;
    aisle extended;
};

struct boot_info {
    unsigned char drive_number;
    struct memory_entry* memory_map;
    unsigned short map_entries;
};

extern struct boot_info boot_info;


extern int _core(int argc, const char *argv[]);


#endif