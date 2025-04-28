#include "core.h"


struct boot_info boot_info;

extern const den Test[];

int _core(int argc, const char *argv[])
{
    load_video();
    clear_screen();
    settextcolor(0, 2);

    puts("________________________________________________________________________________\n");
    puts("            Elle OS Core System\n");
    puts("________________________________________________________________________________\n");
    
    puts("[SETUP GDT] global descriptor table\n");
    
    load_gdt();

    puts("[SETUP IDT] interrupt descriptor table\n");
    load_idt();

    puts("[SETUP IRQ] interrupt requests\n");
    load_pre_requests();

    puts("[SETUP ISR] service interrupts\n");
    load_pre_services();

    puts("\n");
    puts("[LOAD]      system clock driver\n");
    load_system_clock();
    
    puts("\n");
    puts("[LOAD]      system keyboard driver\n");
    load_system_keyboard();
  

	asm("sti"); /* enable interrupts */

    puts("________________________________________________________________________________\n");
    puts("            Elle OS Hub System\n");
    puts("________________________________________________________________________________\n");
    //no printing output here, we make real requests here, and those functions output to the screen per request.
    //we want to collect all the output from here till after the hlt is done uninhibited so we have proper output.
    // pretty sure this is where we would make a while loop to start handling system requests. 

    //request_system_clock(50);        // guess we shouldnt be using the actual function here, but rather the request handler thats already setup?
    //request_system_keyboard(1);      // guess we shouldnt be using the actual function here, but rather the request handler thats already setup?

    asm("int $13"); // Service exception test: Trigger GPF after sti.

    while(1)
    {
       
        asm("hlt");
        puts("________________________________________________________________________________\n");
    }

    return 0;
}
