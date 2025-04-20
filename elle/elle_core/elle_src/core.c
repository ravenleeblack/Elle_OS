#include "core.h"
#include "screen.h"



int _core(int argc, const char *argv[])
{

    init_idt();
    init_gdt();


    for (;;)
    {
        asm("hlt");  // Halt CPU until next interrupt to save power
    }
    return 0;
}


/*

int _core(int argc, const char *argv[])
{
    volatile char* video_memory = (volatile char*)0xb8000;

    video_memory[0] = 'E';
    video_memory[2] = 'L';
    video_memory[4] = 'L';
    video_memory[6] = 'E';

    video_memory[8] = 'O';
    video_memory[10] = 'S';


    // Initialize video buffer before any memory operations
    //init_video();

    // Now load GDT and IDT
    //load_gdt();
    //load_idt();

    __asm__("sti");

    while(1) {
        __asm__("hlt");
    }
    return 0;
}
*/
