# Makefile
# Properties
DESTINATION = firmware
DEVICE      = atmega328p
PROGRAMMER  = usbasp-clone
DEFINES		= $(addprefix -D, COMMON_CATHODE_MODE NO_LEADING_ZEROS_MODE)

# Utilities
AVRDUDE     = avrdude -c $(PROGRAMMER) -p $(DEVICE)
AVRGCC      = avr-gcc -mmcu=$(DEVICE) -Os -Wall $(DEFINES)
AVROBJCOPY  = avr-objcopy --input-target elf32-avr --output-target ihex --verbose
AVROBJDUMP  = avr-objdump --disassemble
AVRSIZE     = avr-size --format=AVR --mcu=$(DEVICE)

# Source files
SOURCES = \
    src/main.c \
    src/drivers/gpio.c \
    src/drivers/cx56.c 

# Object files
OBJECTS = $(patsubst ./src/%.c, ./target/%.o, $(SOURCES))

build: clean $(OBJECTS)
	@mkdir -p ./target  # Create the target directory if it doesn't exist
	@echo "Linking..."
	@$(AVRGCC) -o ./target/$(DESTINATION).elf $(OBJECTS)
	@$(AVROBJCOPY) ./target/$(DESTINATION).elf ./target/$(DESTINATION).hex
	@echo "INFO: build finished"

./target/%.o: ./src/%.c
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(AVRGCC) -c $< -o $@

clean:
	@rm --force --recursive --verbose ./target
	@echo "INFO: clean finished"

check:
	@$(AVRDUDE)
	
erease:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -e

upload:
	@$(AVRDUDE) -U flash:w:./target/$(DESTINATION).hex:i

disasm: ./target/$(DESTINATION).elf
	@avr-objdump -d ./target/$(DESTINATION).elf

size:	./target/$(DESTINATION).elf
	@avr-size --format=AVR --mcu=$(DEVICE) ./target/$(DESTINATION).elf 

fuses-default:
	@$(AVRDUDE) -U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m 

fuses-no-divider-int-rc:
	@$(AVRDUDE) -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m 

fuses-no-divider-ext-clk:
	@$(AVRDUDE) -U lfuse:w:0xff:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m
