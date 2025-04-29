ENTRY(_core)
OUTPUT_FORMAT("elf32-i386")

SECTIONS
{
    . = 0x7C00;                  /* Boot sector */
    .osboot : AT(0x7C00) SUBALIGN(4)
    {
        osboot.o(.text)
        osboot.o(.*)
    }

    . = 0x7DFE;
    .bootsig : {
        SHORT(0xaa55);     /* handles end of section*/
    }

    . = 0x7E20;                 /* Loader */
    .osload : AT(0x7E20) SUBALIGN(4)
    {
        osload.o(.text)
        osload.o(.*)
		binary.o(.*)
    }

    . = 0x9090;               /* Core at 64KB */
    ._core : SUBALIGN(4)
    {
        *(.text*)              /* Code section */
        *(.rodata*)           /* Read-only data */
    }

    ._core_data : SUBALIGN(4)
    {
        *(.data*)             /* Initialized data */
        *(.core_data)         /* Special core data section */
    }

    .bss : SUBALIGN(4) {
        __bss_start = .;
        *(COMMON);
        *(.bss*);
        . = ALIGN(4);          /* Round BSS up to 4 byte boundary */
        __bss_end = .;
    }

    .stack : ALIGN(16)        /* Stack section - 16-byte aligned */
    {
        end_stack = .;
        . = ALIGN(16);        /* Ensure alignment */
        . += 0x20000;         /* 128KB stack */
        . = ALIGN(16);        /* Ensure alignment */
        start_stack = .;      /* Stack grows down */
    }

    core_sectors = (SIZEOF(._core) + 511) / 512;

    /DISCARD/ : {
        *(.eh_frame)
        *(.comment)
    }
}