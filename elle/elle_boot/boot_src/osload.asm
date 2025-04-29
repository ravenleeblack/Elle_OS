[BITS 16]
section .osload
global osload
extern start_stack
extern end_stack
global orchard_struct        ; Make orchard_struct globally accessible

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
    jmp dword 0x08: pmode

[BITS 32]
pmode:
    ; Set up segment registers
    mov ax, 0x10              ; Data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    

    ;call setup_paging         ; Set up paging

    ; Set up stack
    mov esp, start_stack      ; Use linker-defined stack top
    mov ebp, esp

    ; Mask all IRQs
    mov al, 0xFF
    out 0x21, al              ; Master PIC
    out 0xA1, al              ; Slave PIC
    
    mov eax, 0x1000000
    mov [orchard_struct], eax        ; total_memory

    mov eax, start_stack
    mov [orchard_struct + 4], eax    ; core_stack

    mov eax, start_stack
    sub eax, end_stack
    mov [orchard_struct + 8], eax    ; core_stack_size

    mov eax, edx                     ; Boot device from DL (passed by osboot)
    and eax, 0xFF                    ; Mask to byte
    mov [orchard_struct + 12], eax   ; boot_device

    mov eax, 0x32                    ; 80x50 text mode (not 0x03, reflects tmode_system)
    mov [orchard_struct + 16], eax   ; video_mode

    ; Pass orchard struct pointer via a register (e.g., EBX)
    mov ebx, orchard_struct   ; EBX holds the pointer to orchard_struct
    push ebx                  ; Push orchard_struct pointer
    ; Push parameters for _core (argc, argv, boot_info)
    push dword 0              ; argv (dummy)
    push dword 0              ; argc (dummy)

    extern _core
    call _core
    
%include "setup_gdt.inc"
%include "setup_isr.inc"
%include "setup_paging.inc"

halt:
    cli
    hlt

; Define the orchard struct in the data section
section .data
orchard_struct:
    dd 0x00000000             ; total_memory (placeholder)
    dd 0x00000000             ; core_stack (placeholder)
    dd 0x00000000             ; core_stack_size (placeholder)
    dd 0x00000000             ; boot_device (placeholder)
    dd 0x00000000             ; video_mode (placeholder)