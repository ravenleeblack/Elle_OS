#include "core.h"
#include "screen.h"

int _core(int argc, const char *argv[])
{
        // Initialize video and clear screen first
    load_video();
    clear_screen();
    settextcolor(0, 2);
    puts("Booting Elle OS...\n");
   
    asm ("hlt");
}