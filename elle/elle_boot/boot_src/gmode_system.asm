%ifndef GMODE_SYSTEM_INC
%define GMODE_SYSTEM_INC

_set_gmode_system:
    mov ax, 4F02h            ; vesa mode bios call to set the graphics mode
    mov bx, 980h             ; mode 980h corresponds to 1440x900x32bpp
    int 10h                  ; call bios interrupt 10h to set the mode
    ret                      ; return back to osload when finished


%endif ; GMODE_SYSTEM_INC