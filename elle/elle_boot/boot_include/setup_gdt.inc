
global gdt_selector
global flush_gdt     					; Allows the C code to link to this
global flush_tss
extern _gdt_ptr  
extern _tss

section .text
flush_gdt:
    lgdt 	[_gdt_ptr]        				; Load the GDT with our '_gp' which is a special pointer
    mov 	ax, 0x10      				; 0x10 is the offset in the GDT to our data segment
    mov 	ds, ax
    mov 	es, ax
    mov 	fs, ax
    mov 	gs, ax
    mov 	ss, ax
    jmp 	0x08:flush   				; 0x08 is the offset to our code segment: Far jump!
flush:
    ret               					; Returns back to the C code

flush_tss:
   mov ax, 0x28
   ltr ax
   ret

section .data
gdt_start:
gdt_null:
    dq 0

core_mode_code:
    dw 0xFFFF    ; Limit 0-15
    dw 0         ; Base 0-15
    db 0         ; Base 16-23
    db 0x9A      ; Access byte - Present, Ring 0, Code, Readable
    db 0xCF      ; Flags + Limit 16-19
    db 0         ; Base 24-31

core_mode_data:
    dw 0xFFFF
    dw 0
    db 0
    db 0x92      ; Access byte - Present, Ring 0, Data, Writable
    db 0xCF
    db 0

user_mode_code:
    dw 0xFFFF
    dw 0
    db 0
    db 0xFA      ; Access byte - Present, Ring 3, Code, Readable
    db 0xCF
    db 0

user_mode_data:
    dw 0xFFFF
    dw 0
    db 0
    db 0xF2      ; Access byte - Present, Ring 3, Data, Writable
    db 0xCF
    db 0

tss_descriptor:
    dw 103       ; Limit (size of tss - 1)
    dw 0         ; Base 0-15
    db 0         ; Base 16-23
    db 0x89      ; Access byte - Present(1) DPL(00) Type(1001)
    db 0x40      ; Flags(0100) + Limit 16-19(0000)
    db 0         ; Base 24-31

gdt_end:

gdt_selector:
    dw gdt_end - gdt_start - 1
    dd gdt_start

core_mode_code_seg equ 0x08
core_mode_data_seg equ 0x10
user_mode_code_seg equ 0x18
user_mode_data_seg equ 0x20
tss_mode_seg equ 0x28