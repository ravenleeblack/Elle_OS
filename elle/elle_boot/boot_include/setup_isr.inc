
extern handle_core_service
extern handle_core_request
extern handle_timer_request
global flush_idt
extern _idt_ptr


section .text
flush_idt:
    lidt 	[_idt_ptr]
    ret



; Exception handlers
%macro service_error_code 1
global service_%1
service_%1:
    cli                     ; Disable interrupts
    push dword %1          ; Push error code
    jmp handle_service_common
%endmacro

%macro service_no_error_code 1
global service_%1
service_%1:
    cli                     ; Disable interrupts
    push dword 0           ; Push dummy error code
    push dword %1          ; Push interrupt number
    jmp handle_service_common
%endmacro

%macro request_handler 2
global request_%1
request_%1:
    cli                     ; Disable interrupts
    push dword 0           ; Push dummy error code
    push dword %2          ; Push interrupt number (32 + IRQ number)
    jmp handle_request_common
%endmacro

service_error_code 8
service_error_code 10
service_error_code 11
service_error_code 12
service_error_code 13
service_error_code 14

service_no_error_code 0
service_no_error_code 1
service_no_error_code 2
service_no_error_code 3
service_no_error_code 4
service_no_error_code 5
service_no_error_code 6
service_no_error_code 7
service_no_error_code 9
service_no_error_code 15
service_no_error_code 16
service_no_error_code 17
service_no_error_code 18
service_no_error_code 19
service_no_error_code 20
service_no_error_code 21
service_no_error_code 22
service_no_error_code 23
service_no_error_code 24
service_no_error_code 25
service_no_error_code 26
service_no_error_code 27
service_no_error_code 28
service_no_error_code 29
service_no_error_code 30
service_no_error_code 31
service_no_error_code 128
service_no_error_code 177

; Hardware interrupts
%assign i 0
%rep 16
    request_handler i, (i + 32)
    %assign i i+1
%endrep

handle_service_common:
    pushad
    push ds
    push es
    push fs
    push gs
    
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov eax, esp
    push eax
    call handle_core_service
    add esp, 4
    
    pop gs
    pop fs
    pop es
    pop ds
    popad
    add esp, 8
    iret

handle_request_common:
    pushad
    push ds
    push es
    push fs
    push gs
    
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov eax, esp
    push eax
    call handle_core_request
    add esp, 4
    
    pop gs
    pop fs
    pop es
    pop ds
    popad
    add esp, 8
    iret