section .data
global boot_info

boot_info:
    .drive_number  db 0
    .memory_map    dd 0    ; Pointer to memory map
    .map_entries   dw 0    ; Number of entries

