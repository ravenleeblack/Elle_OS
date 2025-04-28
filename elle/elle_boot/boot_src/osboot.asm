[BITS 16]
extern osload

osboot:
     cli
     xor ax, ax                      ; Initialize seg regsisters to 0
     mov ds, ax
     mov es, ax
     mov fs, ax
     mov gs, ax
     mov ss, ax
     mov sp, 0x7c00                  ; Place stack just below bootloader
     sti

     call read_osload
     jmp 0: osload                    ; Far jump to osload with CS=0

read_osload:
    mov ah, 0                        ; reset the drive function
   ; mov dl, 1                      ; drive number 0 (floppy)
    int 0x13                        ; call the BIOS interrupt to reset drive

    xor ax, ax
    mov es, ax                      ; Make sure ES is 0 for read
    mov bx, 0x7E00                  ; read address 0x7E00

    mov ah, 0x02                    ; read sector function
    mov al, 36                       ; read 36 sectors
    mov ch, 0                       ; track 0
    mov cl, 2                       ; sector 2
    ;mov dh, 1                       ; head 0
    int 0x13                        ; read drive
    ret