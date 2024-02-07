.PHONY: all
all: build/kernel.bin

.PHONY: clean
clean:
	@find build -type f \( \
		-name '*.pgz' -o \
		-name '*.bin' -o \
		-name '*.elf' -o \
		-name '*.a' -o \
		-name '*.lst' \
	\) -delete
	@find src -type f \( \
		-name '*.o' -o \
		-name '$(TARGET)' \
	\) -delete

build/kernel.bin: $(KERNEL_OBJ)
	@echo "Linking $@..."
	@$(LD) -o $@ $(LDFLAGS) $^
