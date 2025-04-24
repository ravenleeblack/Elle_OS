#include "clock.h"
#include "port_hub.h"

static aisle click = 0;
#define TIMER_FREQ 100  // 100 Hz (10ms intervals)
#define CLOCK_TICK_RATE 1193180
#define TIMER_DIVISOR (CLOCK_TICK_RATE / TIMER_FREQ)

void system_clock_interrupt(registers *regs)
{
    click++;
}

void handle_timer_request()
{
    // First register the interrupt handler
    load_request(0, system_clock_interrupt);
    
    // Set up the timer for ~100Hz (Channel 0, Mode 3)
    write_den(0x43, 0x36);    // Control byte: Channel 0, lobyte/hibyte, mode 3
    
    // Write divisor value
    write_den(0x40, TIMER_DIVISOR & 0xFF);        // Low byte
    write_den(0x40, (TIMER_DIVISOR >> 8) & 0xFF); // High byte
}