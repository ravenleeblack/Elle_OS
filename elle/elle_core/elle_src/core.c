#include "core.h"

aisle stack_size;  //This will equal 0x20000 (128KB)
orchard *boot_info;  // Define the global pointer here

// Print boot info for debugging
char buffer[32];

// Simple number-to-string function for base 10 or 16
void num_to_str(aisle value, char *buffer, int base)
{
    char *p = buffer;
    char *p_end;
    char tmp[32];  // Enough for 32-bit number in base 2, let alone 10 or 16
    int i = 0;
    
    // Handle 0 explicitly
    if (value == 0)
    {
        *p++ = '0';
        *p = '\0';
        return;
    }

    // Convert to digits (in reverse order)
    while (value)
    {
        int digit = value % base;
        tmp[i++] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
        value /= base;
    }

    // Reverse digits into buffer
    p_end = p + i;
    while (i--)
        *p++ = tmp[i];
    *p = '\0';
}


int _core(int argc, const char *argv[], orchard *boot_info_passed)
{
    // Assign the passed boot_info to the global pointer
    boot_info = boot_info_passed;  // Use the passed pointer

    stack_size = start_stack - end_stack;  // Calculate stack size (should be 0x20000)

    den scancode;

    load_video();
    clear_screen();
    settextcolor(0, 2);
    int x, y;
    get_cursor_pos(&x, &y);

    puts("________________________________________________________________________________\n");
    puts("            Elle OS Core System\n");
    puts("________________________________________________________________________________\n");
    
    puts("[SETUP GDT] global descriptor table\n");
    
    load_gdt();

    puts("[SETUP IDT] interrupt descriptor table\n");
    load_idt();

    puts("[SETUP IRQ] interrupt requests\n");
    load_pre_requests();

    puts("[SETUP ISR] service requests\n");
    load_pre_services();


    puts("\n");
    puts("[ORCHARD]   orchard boot structure:\n");

    puts("\n");
    puts("            boot device:   0x");
    num_to_str(boot_info->boot_device, buffer, 16);
    puts(buffer);   puts("  (0x00 = floppy, 0x80 = HDD)\n");

    puts("            video mode:    0x");
    num_to_str(boot_info->video_mode, buffer, 16);
    puts(buffer);   puts("  (0x32 = 80x50 text)\n");

    puts("\n");
    puts("            stack address: 0x");
    num_to_str(boot_info->core_stack, buffer, 16);
    puts(buffer);   puts("  bytes\n");

    puts("            stack size:    ");
    num_to_str(boot_info->core_stack_size, buffer, 10);
    puts(buffer);   puts("  bytes\n");

    puts("            total memory:  ");
    num_to_str(boot_info->total_memory, buffer, 10);
    puts(buffer);   puts("  bytes\n");
    puts("\n");


    puts("[LOAD]      programmable interrupt controller\n");
    remap_pic();

    puts("\n");
    puts("[LOAD]      system clock driver\n");
    load_system_clock();
    
    puts("\n");
    puts("[LOAD]      system keyboard driver\n");
    load_system_keyboard();



    puts("\n");

    puts("[DEBUG]     GDT base: 0x");
    num_to_str(_gdt_ptr.base, buffer, 16);
    puts(buffer); puts("\n");
    puts("[DEBUG]     GDT limit: 0x");
    num_to_str(_gdt_ptr.limit, buffer, 16);
    puts(buffer); puts("\n");
    puts("[DEBUG]     IDT base: 0x");
    num_to_str(_idt_ptr.base, buffer, 16);
    puts(buffer); puts("\n");
    puts("[DEBUG]     IDT limit: 0x");
    num_to_str(_idt_ptr.limit, buffer, 16);
    puts(buffer); puts("\n");

    asm("sti"); // Initial interrupt enable

    puts("________________________________________________________________________________\n");
    puts("            Elle OS Hub System\n");
    puts("________________________________________________________________________________\n");

    while (1) {
        process_keys();

        asm("sti");
        asm("hlt");
    }

    return 0;
}