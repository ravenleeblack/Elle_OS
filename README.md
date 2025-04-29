# Elle_OS

 Elle has a 2 stage bootloader that loads the kernel named core. I use a link.ld script instead of the file system in the booting process. The link.ld handle loading the bootloader stages, the core, and handle the stack. Code current as of Monday, April 28, 2025.

 It currently has:
 - GDT
 - IDT
 - IRQ
 - ISR
 - Clock works
 - Keyboards works with letters, numbers, odd chars, and enter no arrow keys or shift yet.
 - Bootloader passes information through the Orchard Struct.

Will be working on getting these to work:
- heap memory
- pysical memory
- paging memory
- A system to print or write it out
- A terminal
- A file system

