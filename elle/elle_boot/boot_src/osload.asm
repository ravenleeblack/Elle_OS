[BITS 16]
section .osload
global osload
extern start_stack
extern end_stack
extern _core


osload: jmp switch_pmode

switch_pmode:
    mov ah, 0eh
    mov al, 'H'
    int 10h

    call enable_gate                 ; enable A20 gate
    call _set_tmode_system           ; set graphics mode

    cli                       ; disable interrupts
    lgdt[gdt_selector]                    ; load GDT

    mov eax, cr0                     ; get CR0
    or eax, 1                        ; set protected mode bit
    mov cr0, eax                     ; enable protected mode

    jmp dword core_mode_code_seg:.pmode_entry      ; Far jump to protected mode entry point

[BITS 32]
.pmode_entry:
    ; Initialize segment registers
    mov ax, core_mode_data_seg                  ; Data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, start_stack
    mov ebp, esp

    call _core

halt:
    cli
    hlt

%include "enable_gate.inc"
%include "tmode_system.asm"
%include "gmode_system.asm"
%include "setup_gdt.inc"
%include "setup_isr.inc"