extern handle_core_service
extern handle_core_request
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
    cli
    push dword %1
    mov eax, 0xCAFEBABE
    jmp handle_service_common
%endmacro

%macro service_no_error_code 1
global service_%1
service_%1:
    cli
    push dword 0
    push dword %1
    mov eax, 0xDEADBEEF
    jmp handle_service_common
%endmacro

%macro request_handler 2
global request_%1
request_%1:
    cli
    push dword 0
    push dword %2
    mov eax, 0xBEEFBEEF
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
    cli
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
    mov ss, ax
    
    push esp
    call handle_core_service
    add esp, 4
    
    pop gs
    pop fs
    pop es
    pop ds
    popad
    add esp, 8
    
    ; Debug EFLAGS before iret
    pushf
    pop eax
    push eax
    shr eax, 9
    and eax, 1
    push eax
    call print_flag_iret
    add esp, 4
    pop eax
    
    sti
    iret

handle_request_common:
    cli
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
    mov ss, ax
    
    ; Debug interrupt vector
    mov eax, [esp + 32]
    push eax
    call print_vector
    add esp, 4
    
    ; Debug EFLAGS before handler
    pushf
    pop eax
    push eax
    shr eax, 9
    and eax, 1
    push eax
    call print_flag
    add esp, 4
    pop eax
    
    push esp
    call handle_core_request
    add esp, 4
    
    ; Debug EFLAGS after handler
    pushf
    pop eax
    push eax
    shr eax, 9
    and eax, 1
    push eax
    call print_flag_after
    add esp, 4
    pop eax
    
    pop gs
    pop fs
    pop es
    pop ds
    popad
    add esp, 8
    
    ; Debug EFLAGS before iret
    pushf
    pop eax
    push eax
    shr eax, 9
    and eax, 1
    push eax
    call print_flag_iret
    add esp, 4
    pop eax
    
    sti
    iret

section .text
global print_flag
global print_flag_after
global print_flag_iret
global print_vector
extern num_to_str
extern puts

print_flag:
    push ebp
    mov ebp, esp
    sub esp, 32
    mov eax, [ebp + 8]
    lea ebx, [esp]
    push 10
    push ebx
    push eax
    call num_to_str
    add esp, 12
    push ebx
    mov ebx, flag_msg
    push ebx
    call puts
    add esp, 4
    call puts
    add esp, 4
    mov eax, newline
    push eax
    call puts
    add esp, 4
    mov esp, ebp
    pop ebp
    ret

print_flag_after:
    push ebp
    mov ebp, esp
    sub esp, 32
    mov eax, [ebp + 8]
    lea ebx, [esp]
    push 10
    push ebx
    push eax
    call num_to_str
    add esp, 12
    push ebx
    mov ebx, flag_after_msg
    push ebx
    call puts
    add esp, 4
    call puts
    add esp, 4
    mov eax, newline
    push eax
    call puts
    add esp, 4
    mov esp, ebp
    pop ebp
    ret

print_flag_iret:
    push ebp
    mov ebp, esp
    sub esp, 32
    mov eax, [ebp + 8]
    lea ebx, [esp]
    push 10
    push ebx
    push eax
    call num_to_str
    add esp, 12
    push ebx
    mov ebx, flag_iret_msg
    push ebx
    call puts
    add esp, 4
    call puts
    add esp, 4
    mov eax, newline
    push eax
    call puts
    add esp, 4
    mov esp, ebp
    pop ebp
    ret

print_vector:
    push ebp
    mov ebp, esp
    sub esp, 32
    mov eax, [ebp + 8]
    lea ebx, [esp]
    push 16
    push ebx
    push eax
    call num_to_str
    add esp, 12
    push ebx
    mov ebx, vector_msg
    push ebx
    call puts
    add esp, 4
    call puts
    add esp, 4
    mov eax, newline
    push eax
    call puts
    add esp, 4
    mov esp, ebp
    pop ebp
    ret

section .data
flag_msg: db "[DEBUG]     Handler EFLAGS IF (before): ", 0
flag_after_msg: db "[DEBUG]     Handler EFLAGS IF (after): ", 0
flag_iret_msg: db "[DEBUG]     Pre-IRET EFLAGS IF: ", 0
vector_msg: db "[DEBUG]     Interrupt Vector: 0x", 0
newline: db 10, 0