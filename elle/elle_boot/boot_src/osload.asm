BITS 16
section .osload
global osload
extern start_stack 
extern end_stack
extern _core

%include "gmode_system.asm"
%include "tmode_system.asm"
%include "setup_gdt.inc"
%include "setup_isr.inc"
%include "enable_gate.inc"

osload: jmp switch_pmode

switch_pmode:
    call enable_gate           ; enable A20 gate
    call _set_tmode_system    ; set graphics mode
                 
    cli                       ; Disable interrupts
    
    ; Load our GDT and IDT
    lgdt [gdt_selector]       ; Load the GDT from setup_gdt.inc
    lidt [idt_selector]       ; Load the IDT from setup_idt.inc
    
    ; Switch to protected mode
    mov eax, cr0              ; get CR0
    or eax, 1                 ; set protected mode bit
    mov cr0, eax              ; enable protected mode
    
    ; Perform far jump to flush CPU pipeline
    jmp dword core_mode_code_seg:pmode_entry  ; Far jump using GDT code segment

BITS 32
pmode_entry:
    ; Set up segment registers
    mov ax, core_mode_data_seg  ; Update segment registers with GDT data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Set up initial stack
    mov esp, end_stack      ; Set up stack
    mov ebp, esp
    
    mov ax, tss_mode_seg     ; Load TSS
    ltr ax
    
    ; Now safe to enable interrupts since both GDT and IDT are set up
    sti                      ; Enable interrupts

    push 0                   ; Push arguments for _core
    push 0

    call _core              ; Jump to C code
    
halt:
    cli
    hlt
