%ifndef TMODE_SYSTEM_INC
%define TMODE_SYSTEM_INC

%include "clear_screen.inc"
%include "move_cursor.inc"
%include "write.inc"


_set_tmode_system:
    pusha                ; Save registers

    mov ah, 00h          ; Set video mode
    mov al, 03h          ; 80x25 text mode (initially)
    int 10h              ; Call BIOS

    mov ax, 1112h        ; Load 8x8 font
    mov bh, 0            ; Font block
    mov bl, 0            ; Default ROM font
    int 10h              ; Call BIOS

    mov ax, 1202h        ; Set 400 scan lines for 80x50
    mov bl, 30h          ; Video control
    int 10h              ; Call BIOS

    popa                 ; Restore registers
    ret                  ; Return to caller

%endif ; TMODE_SYSTEM_INC