SHELL := bash
CC := cc65816
AS := as65816
AR := nlib
LD := ln65816

.SUFFIXES:
.SUFFIXES: .c .s .o .a

MEMORY_MAP := config/memory.scm

CFLAGS := --include-system=include/libc \
		  -I include \
		  --code-model=large \
		  --data-model=huge \
		  --64bit-doubles \
		  --strong-inline \
		  --force-switch jump-table

ASFLAGS := --include-system=include/libc \
		   -I include \
		   --code-model=large \
		   --data-model=huge

ifeq ($(RELEASE), "true")
CFLAGS += -DNDEBUG \
		  -O2 \
		  --speed
else
CFLAGS += --debug \
		  -Wall \
		  -Wextra \
		  -Wpedantic \
		  -Werror \
		  -Wno-c11-extensions \
		  -Wno-gnu-binary-literal \
		  -Wno-gnu-conditional-omitted-operand \
		  -Wno-gnu-case-range \
		  -Wimplicit-fallthrough \
		  -Wno-gnu-folding-constant
ASFLAGS += --debug
endif

LDFLAGS := $(MEMORY_MAP) \
	   --hosted \
	   --no-data-init-table-section \
	   --rtattr cstartup=turaco \
	   --list-file build.lst \
	   --verbose \
	   --no-auto-libraries \
	   --output-format pgz

ifeq ($(ENABLE_RELEASE_BUILD), "true")
CFLAGS += -DRELEASE_BUILD
CFLAGS += -DNDEBUG
else
CFLAGS += -DDEBUG
endif

LIBS := build/libc.a

%.o: %.c
	@echo "Compiling $@..."
	@$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.s
	@echo "Assembling $@)..."
	@$(AS) $(ASFLAGS) -o $@ $<

KERNEL_SRC_C := $(wildcard src/*.c) \
	    	    $(wildcard src/*/*.c) \
	    	    $(wildcard src/*/*/*.c) \
	    	    $(wildcard src/*/*/*/*.c) \
	    	    $(wildcard src/*/*/*/*/*.c)
KERNEL_SRC_S := $(wildcard src/*.s) \
	    	    $(wildcard src/*/*.s) \
	    	    $(wildcard src/*/*/*.s) \
	    	    $(wildcard src/*/*/*/*.s) \
	    	    $(wildcard src/*/*/*/*/*.s)
KERNEL_OBJ := $(KERNEL_SRC_C:.c=.o) \
			  $(KERNEL_SRC_S:.s=.o)
