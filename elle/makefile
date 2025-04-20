# Directories
BOOT_SRC = elle_boot/boot_src
BOOT_INC = elle_boot/boot_include

CORE_SRC = elle_core/elle_src
CORE_INC = elle_core/elle_include

OBJ_DIR = obj

# Compiler flags
ASM = nasm
ASM_FLAGS = -f elf32 -i $(BOOT_INC)/ -i $(BOOT_SRC)/

CC = gcc
CC_FLAGS = -m32 -fno-pie -Wall -ffreestanding --no-builtin -nostdinc -nostdlib -I$(CORE_INC)

# Boot assembly files
BOOT_SOURCES = $(BOOT_SRC)/osboot.asm \
               $(BOOT_SRC)/osload.asm \
               $(BOOT_SRC)/gmode_system.asm \
               $(BOOT_SRC)/tmode_system.asm

# Core C source files
CORE_SOURCES = $(CORE_SRC)/core.c \
               $(CORE_SRC)/clock.c \
               $(CORE_SRC)/request.c \
               $(CORE_SRC)/service.c \
			   $(CORE_SRC)/gdt.c \
               $(CORE_SRC)/idt.c \
               $(CORE_SRC)/port_hub.c \
               $(CORE_SRC)/memory.c \
               $(CORE_SRC)/screen.c

# Generate object file names (all in obj/)
BOOT_OBJS = $(patsubst $(BOOT_SRC)/%.asm,$(OBJ_DIR)/%.o,$(BOOT_SOURCES))
CORE_OBJS = $(patsubst $(CORE_SRC)/%.c,$(OBJ_DIR)/%.o,$(CORE_SOURCES))

ALL_OBJS = $(CORE_OBJS) $(BOOT_OBJS)

# Target files
all: directories boot_objects core_objects elle.flp
	@echo "Build complete: elle.flp created"

# Boot components
boot_objects: $(BOOT_OBJS)

$(OBJ_DIR)/%.o: $(BOOT_SRC)/%.asm
	@$(ASM) $(ASM_FLAGS) $< -o $@
	@test -f $@ || (echo "Failed to create $@" && exit 1)

# Core components
core_objects: $(CORE_OBJS)

$(OBJ_DIR)/%.o: $(CORE_SRC)/%.c
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@test -f $@ || (echo "Failed to create $@" && exit 1)

# Linking
core.bin: $(ALL_OBJS)
	@echo "Linking core components..."
	@cd $(OBJ_DIR) && \
	ld -T ../link.ld -melf_i386 -o ../core.elf \
		$(notdir $(CORE_OBJS)) \
		$(notdir $(BOOT_OBJS))
	@objcopy -O binary core.elf core.bin
	@echo "\nSection sizes:"
	@size -A -d core.elf | awk '\
		BEGIN {total = 0} \
		/\.osboot/ {printf "Boot sector:     %8d bytes\n", $$2} \
		/\.osload/ {printf "Loader:          %8d bytes\n", $$2} \
		/\._core/  {printf "Core code/data:  %8d bytes\n", $$2} \
		/\.bss/    {printf "BSS:             %8d bytes\n", $$2} \
		/\.stack/  {printf "Stack:           %8d bytes\n", $$2} \
		{if ($$2 ~ /^[0-9]+$$/) total += $$2} \
		END {printf "\nTotal size:      %8d bytes\n", total}'

# Final disk image
elle.flp: core.bin
	@echo "Creating disk image..."
	@dd if=/dev/zero of=elle.flp bs=1K count=1440 2>/dev/null
	@dd if=core.bin of=elle.flp conv=notrunc 2>/dev/null

# Create necessary directories
directories:
	@mkdir -p $(OBJ_DIR)

# Debug target
debug:
	@echo "Boot sources: $(BOOT_SOURCES)"
	@echo "Core sources: $(CORE_SOURCES)"
	@echo "Boot objects: $(BOOT_OBJS)"
	@echo "Core objects: $(CORE_OBJS)"
	@echo "All objects: $(ALL_OBJS)"
	@ls -l $(OBJ_DIR)

# Clean
clean:
	@echo "Cleaning build files..."
	@rm -f core.bin core.elf elle.flp
	@rm -f $(OBJ_DIR)/*.o

.PHONY: all clean directories debug boot_objects core_objects
