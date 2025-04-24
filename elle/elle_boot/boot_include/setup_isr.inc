extern handle_core_service
extern handle_core_request
extern handle_timer_request

global idt_selector




idt_start:
    times 256 dq 0   ; Create 256 empty interrupt entries

idt_end:

idt_selector:
    dw idt_end - idt_start - 1  ; Size of IDT
    dd idt_start                ; Base address of IDT




%macro service_error_code 1
  global service_%1
  service_%1:
    push dword %1         ; push the interrupt number
    jmp handle_service_common
%endmacro

%macro service_code 1
  global service_%1
  service_%1:
    push dword 0          ; push a dummy error code just because to keep struct Registers the same as the above macro
    push dword %1         ; push the interrupt number
    jmp handle_service_common
%endmacro


%macro request_code 2
  global request_%1
  request_%1:
    push dword 0          ; push a dummy error code just because to keep struct Registers the same again
    push dword %2
    jmp handle_request_common
%endmacro


service_code  0
service_code  1
service_code  2
service_code  3
service_code  4
service_code  5
service_code  6
service_code  7
service_error_code     8
service_code  9
service_error_code     10
service_error_code     11
service_error_code     12
service_error_code     13
service_error_code     14
service_code  15
service_code  16
service_code  17
service_code  18
service_code  19
service_code  20
service_code  21
service_code  22
service_code  23
service_code  24
service_code  25
service_code  26
service_code  27
service_code  28
service_code  29
service_code  30
service_code  31
service_code  128

request_code   0,    32
request_code   1,    33
request_code   2,    34
request_code   3,    35
request_code   4,    36
request_code   5,    37
request_code   6,    38
request_code   7,    39
request_code   8,    40
request_code   9,    41
request_code  10,    42
request_code  11,    43
request_code  12,    44
request_code  13,    45
request_code  14,    46
request_code  15,    47



handle_service_common:
    pushad                  ; Save all general purpose registers
    push ds
    push es
    push fs
    push gs

    mov bx, 0x10
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    call handle_core_service

    pop gs
    pop fs
    pop es
    pop ds
    popad
    add esp, 8             ; Clean up error code and interrupt number
    iret                   ; Return from interrupt

handle_request_common:
    pushad                  ; Save all general purpose registers
    push ds
    push es
    push fs
    push gs

    mov bx, 0x10
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    call handle_core_request

    pop gs
    pop fs
    pop es
    pop ds
    popad
    add esp, 8             ; Clean up error code and interrupt number
    iret                   ; Return from interrupt



