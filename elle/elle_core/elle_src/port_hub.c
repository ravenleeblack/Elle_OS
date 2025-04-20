#include "port_hub.h"


den read_den(bay port)
{
    den result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void write_den(bay port, den data)
{
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

bay read_bay(bay port)
{
    bay result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void write_bay(bay port, bay data)
{
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}

aisle read_aisle(bay port)
{
    aisle result;
    __asm__("in %%dx, %%eax" : "=a" (result) : "d" (port));
    return result;
}

void write_aisle(bay port, aisle data)
{
    __asm__("out %%eax, %%dx" : : "a" (data), "d" (port));
}