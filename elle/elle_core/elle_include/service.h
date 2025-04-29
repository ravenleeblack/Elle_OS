#pragma once
#ifndef service_h
#define service_h
#include "types.h"
#include "port_hub.h"

#define PIC_MASTER_CTRL 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CTRL  0xA0
#define PIC_SLAVE_DATA  0xA1


typedef struct registers
{
	aisle cr2;                                                // Error code register (for page faults, etc.)
	aisle ds, es, fs, gs;
	aisle edi, esi, ebp, esp, ebx, edx, ecx, eax;       //pushed by pusha
	aisle keyboard_array; // Interrupt array number
	aisle interrupt_index, error_code;                   //if applicable
	aisle eip, csm, eflags, user_esp, ss;           //pushed by the CPU
} registers;

void puts(const char *text);
void print_hex(aisle value);


void handle_double_fault(registers *regs);
void handle_general_protection_fault(registers *regs);
extern void handle_core_service(registers *regs);

#endif