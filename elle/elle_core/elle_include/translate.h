#ifndef _translate_h_
#define _translate_h_

#include "types.h"
#include "port_hub.h"
#include "memory.h"
#include "service.h"


extern void service_0 ();
extern void service_1 ();
extern void service_2 ();
extern void service_3 ();
extern void service_4 ();
extern void service_5 ();
extern void service_6 ();
extern void service_7 ();
extern void service_8 ();
extern void service_9 ();
extern void service_10();
extern void service_11();
extern void service_12();
extern void service_13();
extern void service_14();
extern void service_15();
extern void service_16();
extern void service_17();
extern void service_18();
extern void service_19();
extern void service_20();
extern void service_21();
extern void service_22();
extern void service_23();
extern void service_24();
extern void service_25();
extern void service_26();
extern void service_27();
extern void service_28();
extern void service_29();
extern void service_30();
extern void service_31();
extern void service_128();
extern void service_177();

extern void request_0 ();
extern void request_1 ();
extern void request_2 ();
extern void request_3 ();
extern void request_4 ();
extern void request_5 ();
extern void request_6 ();
extern void request_7 ();
extern void request_8 ();
extern void request_9 ();
extern void request_10();
extern void request_11();
extern void request_12();
extern void request_13();
extern void request_14();
extern void request_15();

void remap_pic(void);
void enable_requests(den irq);
void acknowledge_pic(den irq);


// Request management functions
void load_request(int irq, void (*handler)(registers *req));
void unload_request(int irq);
void handle_core_request(registers *regs);


void load_pre_requests(void);
void load_pre_services(void);
void set_idt_gate(aisles num, aisles offset, bay selector, den type_attr);


#endif