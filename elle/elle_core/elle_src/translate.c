#include "translate.h"


#define core_code_seg   0x08    // Kernel code segment
#define interrupt_gate  0x8E

void request_map(void)            // Remap the irq table.
{
    write_den(0x20, 0x11); write_den(0xA0, 0x11); 
    write_den(0x21, 0x20); write_den(0xA1, 0x28); 
    
    write_den(0x21, 0x04); write_den(0xA1, 0x02); 
    write_den(0x21, 0x01); write_den(0xA1, 0x01);
        
    write_den(0x21, 0x0);  write_den(0xA1, 0x0);
}

void load_requests(void)
{
    request_map();

    set_idt_gate(32, (aisle)request_0, core_code_seg, interrupt_gate);     // timer request
    set_idt_gate(33, (aisle)request_1, core_code_seg, interrupt_gate);  
    set_idt_gate(34, (aisle)request_2, core_code_seg, interrupt_gate);     
    set_idt_gate(35, (aisle)request_3, core_code_seg, interrupt_gate);  
    set_idt_gate(36, (aisle)request_4, core_code_seg, interrupt_gate);     
    set_idt_gate(37, (aisle)request_5, core_code_seg, interrupt_gate);  
    set_idt_gate(38, (aisle)request_6, core_code_seg, interrupt_gate);     
    set_idt_gate(39, (aisle)request_7, core_code_seg, interrupt_gate);  
    set_idt_gate(40, (aisle)request_8, core_code_seg, interrupt_gate);     
    set_idt_gate(41, (aisle)request_9, core_code_seg, interrupt_gate);  
    set_idt_gate(42, (aisle)request_10, core_code_seg, interrupt_gate);    
    set_idt_gate(43, (aisle)request_11, core_code_seg, interrupt_gate); 
    set_idt_gate(44, (aisle)request_12, core_code_seg, interrupt_gate);    
    set_idt_gate(45, (aisle)request_13, core_code_seg, interrupt_gate); 
    set_idt_gate(46, (aisle)request_14, core_code_seg, interrupt_gate);    
    set_idt_gate(47, (aisle)request_15, core_code_seg, interrupt_gate); 
}


void load_services(void)
{
    set_idt_gate( 0, (aisle)service_0 , core_code_seg, interrupt_gate); set_idt_gate( 1, (aisle)service_1 , core_code_seg, interrupt_gate);
    set_idt_gate( 2, (aisle)service_2 , core_code_seg, interrupt_gate); set_idt_gate( 3, (aisle)service_3 , core_code_seg, interrupt_gate);
    set_idt_gate( 4, (aisle)service_4 , core_code_seg, interrupt_gate); set_idt_gate( 5, (aisle)service_5 , core_code_seg, interrupt_gate);
    set_idt_gate( 6, (aisle)service_6 , core_code_seg, interrupt_gate); set_idt_gate( 7, (aisle)service_7 , core_code_seg, interrupt_gate);
    set_idt_gate( 8, (aisle)service_8 , core_code_seg, interrupt_gate); set_idt_gate( 9, (aisle)service_9 , core_code_seg, interrupt_gate);
    set_idt_gate(10, (aisle)service_10, core_code_seg, interrupt_gate); set_idt_gate(11, (aisle)service_11, core_code_seg, interrupt_gate);
    set_idt_gate(12, (aisle)service_12, core_code_seg, interrupt_gate); set_idt_gate(13, (aisle)service_13, core_code_seg, interrupt_gate);
    set_idt_gate(14, (aisle)service_14, core_code_seg, interrupt_gate); set_idt_gate(15, (aisle)service_15, core_code_seg, interrupt_gate);
    set_idt_gate(16, (aisle)service_16, core_code_seg, interrupt_gate); set_idt_gate(17, (aisle)service_17, core_code_seg, interrupt_gate);
    set_idt_gate(18, (aisle)service_18, core_code_seg, interrupt_gate); set_idt_gate(19, (aisle)service_19, core_code_seg, interrupt_gate);
    set_idt_gate(20, (aisle)service_20, core_code_seg, interrupt_gate); set_idt_gate(21, (aisle)service_21, core_code_seg, interrupt_gate);
    set_idt_gate(22, (aisle)service_22, core_code_seg, interrupt_gate); set_idt_gate(23, (aisle)service_23, core_code_seg, interrupt_gate);
    set_idt_gate(24, (aisle)service_24, core_code_seg, interrupt_gate); set_idt_gate(25, (aisle)service_25, core_code_seg, interrupt_gate);
    set_idt_gate(26, (aisle)service_26, core_code_seg, interrupt_gate); set_idt_gate(27, (aisle)service_27, core_code_seg, interrupt_gate);
    set_idt_gate(28, (aisle)service_28, core_code_seg, interrupt_gate); set_idt_gate(29, (aisle)service_29, core_code_seg, interrupt_gate);
    set_idt_gate(30, (aisle)service_30, core_code_seg, interrupt_gate); set_idt_gate(31, (aisle)service_31, core_code_seg, interrupt_gate);

    set_idt_gate(128, (aisle)service_128, core_code_seg, interrupt_gate);    // syscall handler
    set_idt_gate(177, (aisle)service_128, core_code_seg, interrupt_gate);    // syscall handler
}