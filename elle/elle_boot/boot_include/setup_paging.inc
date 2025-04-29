[BITS 32]

; Define constants for memory locations
PAGE_DIR equ 0x1000       ; Page Directory at 0x1000
PAGE_TABLE equ 0x2000     ; Page Table at 0x2000

setup_paging:
    ; Set up the Page Directory
    mov edi, PAGE_DIR
    mov eax, PAGE_TABLE | 0x03  ; Point to Page Table (present, writable)
    mov [edi], eax              ; First PDE (Page Directory Entry)
    
    ; Clear remaining PDEs (optional, for safety)
    mov ecx, 1023               ; 1024 entries total, we set 1, clear 1023
    xor eax, eax                ; Clear EAX (0x00)
    add edi, 4                  ; Move to next PDE
    rep stosd                   ; Fill remaining PDEs with 0

    ; Set up the Page Table (map first 4 MiB with 4 KiB pages)
    mov edi, PAGE_TABLE
    mov ebx, 0x00000003         ; Starting physical address (present, writable)
    mov ecx, 1024               ; 1024 entries = 4 MiB (1024 * 4 KiB)

.set_page_table:
    mov [edi], ebx              ; Write page table entry
    add ebx, 0x1000             ; Next 4 KiB page
    add edi, 4                  ; Next PTE (Page Table Entry)
    loop .set_page_table        ; Repeat for all 1024 entries

    ; Load Page Directory into CR3
    mov eax, PAGE_DIR
    mov cr3, eax

    ; Enable paging in CR0
    mov eax, cr0
    or eax, 1 << 31             ; Set PG bit (paging enable)
    mov cr0, eax

    ret                         ; Return (assumes caller handles GDT/IDT)