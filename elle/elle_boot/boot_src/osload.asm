[BITS 16]
section .osload
global osload
extern start_stack
extern end_stack


%include "gmode_system.asm"
%include "tmode_system.asm"
%include "enable_gate.inc"

osload: jmp switch_pmode

switch_pmode:

    call enable_gate           ; Enable A20 gate
    call _set_tmode_system    ; Set text mode
    
    cli                         ; Disable interrupts
    lgdt [gdt_selector]         ; Load GDT
    
    ; Enable protected mode
    mov eax, cr0 
    or al, 1       ; set PE (Protection Enable) bit in CR0 (Control Register 0)
    mov cr0, eax

    ; Far jump to flush pipeline and load CS
    jmp dword 08h: pmode

[BITS 32]
pmode:
    ; Set up segment registers
    mov ax, 0x10              ; Data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    
    ; Set up stack
    mov esp, end_stack
    mov ebp, esp
    
    call setup_paging         ; Set up paging

    ; Call C kernel
    push dword 0              ; argv
    push dword 0              ; argc

    extern _core
    call _core
    
%include "setup_gdt.inc"
%include "setup_isr.inc"
%include "setup_paging.inc"

    ; Should never return, but if it does:
halt:
    cli
    hlt
