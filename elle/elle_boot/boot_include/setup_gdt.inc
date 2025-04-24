global gdt_selector

gdt_start:
gdt_null:
    dw 0
    dw 0
    db 0
    db 0
    db 0
    db 0
core_mode_code:
    dw 0xFFFF
    dw 0
    db 0
    db 0x9A
    db 0xCF
    db 0
core_mode_data:
    dw 0xFFFF
    dw 0
    db 0
    db 0x92
    db 0xCF
    db 0
user_mode_code:
    dw 0xFFFF
    dw 0
    db 0
    db 0xFA
    db 0xCF
    db 0
user_mode_data:
    dw 0xFFFF
    dw 0
    db 0
    db 0xF2
    db 0xCF
    db 0
tss_descriptor:
    dw 0x67       ; limit (size of TSS minus 1)
    dw 0          ; base low
    db 0          ; base middle
    db 0x89       ; access byte - present, ring0, non-system (1000 1001)
    db 0x40       ; flags + limit high (0100 0000)
    db 0          ; base high
gdt_end:

gdt_selector:
    dw gdt_end - gdt_start - 1  ; 39
    dd gdt_start

core_mode_code_seg equ core_mode_code - gdt_start
core_mode_data_seg equ core_mode_data - gdt_start
user_mode_code_seg equ user_mode_code - gdt_start
user_mode_data_seg equ user_mode_data - gdt_start
tss_mode_seg equ tss_descriptor - gdt_start