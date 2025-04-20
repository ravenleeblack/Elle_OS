global gdt_selector
global flush_gdt

gdt_start:
gdt_null:
    dd 0                    ; Null descriptor (low 32 bits)
    dd 0                    ; Null descriptor (high 32 bits)

core_mode_code:
    dw 0xFFFF               ; Limit (bits 0-15)
    dw 0                    ; Base (bits 0-15)
    db 0                    ; Base (bits 16-23)
    db 10011010b            ; Access: Present, Ring 0, Code, Executable, Readable
    db 11001111b            ; Granularity: 4K pages, 32-bit mode, Limit (bits 16-19)
    db 0                    ; Base (bits 24-31)

core_mode_data:
    dw 0xFFFF               ; Limit (bits 0-15)
    dw 0                    ; Base (bits 0-15)
    db 0                    ; Base (bits 16-23)
    db 10010010b            ; Access: Present, Ring 0, Data, Writable
    db 11001111b            ; Granularity: 4K pages, 32-bit mode, Limit (bits 16-19)
    db 0                    ; Base (bits 24-31)

boot_mode_code:
    dw 0xFFFF               ; Limit (bits 0-15)
    dw 0                    ; Base (bits 0-15)
    db 0                    ; Base (bits 16-23)
    db 10011010b            ; Access: Present, Ring 0, Code, Executable, Readable
    db 00001111b            ; Granularity: 1-byte pages, 16-bit mode, Limit (bits 16-19)
    db 0                    ; Base (bits 24-31)

boot_mode_data:
    dw 0xFFFF               ; Limit (bits 0-15)
    dw 0                    ; Base (bits 0-15)
    db 0                    ; Base (bits 16-23)
    db 10010010b            ; Access: Present, Ring 0, Data, Writable
    db 00001111b            ; Granularity: 1-byte pages, 16-bit mode, Limit (bits 16-19)
    db 0                    ; Base (bits 24-31)

gdt_end:

gdt_selector:
    dw gdt_end - gdt_start - 1  ; GDT limit
    dd gdt_start                ; GDT base address

; Segment selector offsets
core_mode_code_seg equ core_mode_code - gdt_start
core_mode_data_seg equ core_mode_data - gdt_start
boot_mode_code_seg equ boot_mode_code - gdt_start
boot_mode_data_seg equ boot_mode_data - gdt_start


flush_gdt:
    mov eax, [esp+4]  ; Get pointer to GdtPointer
    lgdt [eax]        ; Load GDT
    mov ax, 0x10      ; Kernel data segment (offset 0x28)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush_gdt_done ; Far jump to kernel code segment (offset 0x20)
flush_gdt_done:
    ret


