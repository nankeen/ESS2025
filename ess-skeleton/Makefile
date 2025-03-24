######################################
# Project settings
######################################
TARGET = stm32f411_project
BUILD_DIR = build
EXECUTABLE = $(BUILD_DIR)/$(TARGET).elf
BIN = $(BUILD_DIR)/$(TARGET).bin
HEX = $(BUILD_DIR)/$(TARGET).hex

######################################
# Source files
######################################
# Core source files
C_SOURCES = \
$(wildcard Core/Src/*.c) \
$(wildcard Core/Startup/*.c)

# Drivers
C_SOURCES += \
$(wildcard Drivers/STM32F4xx_HAL_Driver/Src/*.c) \
$(wildcard Drivers/CMSIS/Device/ST/STM32F4xx/Source/*.c)

# ASM sources
ASM_SOURCES = \
Core/Startup/startup_stm32f411vetx.s

######################################
# Compiler settings
######################################
# Define the cross-compiler
PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size

# Define microcontroller information
MCU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

# Compiler flags
# C flags
CFLAGS = $(MCU)
CFLAGS += -Wall -Wextra
CFLAGS += -g3 -O0 -std=gnu11
CFLAGS += -ffunction-sections -fdata-sections -fstack-usage
CFLAGS += -DUSE_HAL_DRIVER -DSTM32F411xE

# AS flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) -Wall -fdata-sections -ffunction-sections

# Linker flags
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) -lc -lm -lnosys 
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

######################################
# Include directories
######################################
# Include directories
C_INCLUDES = \
-ICore/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy \
-IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
-IDrivers/CMSIS/Include

# Linker script
LDSCRIPT = STM32F411VETX_FLASH.ld

######################################
# Build the application
######################################
# List of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# Add ASM objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

# Default rule: build all
all: $(BUILD_DIR) $(EXECUTABLE) $(BIN) $(HEX)

# Create build directory
$(BUILD_DIR):
	mkdir -p $@

# Link the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

# Convert to .bin
$(BIN): $(EXECUTABLE)
	$(CP) -O binary $< $@

# Convert to .hex
$(HEX): $(EXECUTABLE)
	$(CP) -O ihex $< $@

# Compile C files
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $(C_INCLUDES) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

# Assemble ASM files
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(ASFLAGS) $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

# Flash the board using OpenOCD
flash:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $(EXECUTABLE) verify reset exit"

# Debug the board using GDB
debug:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg

.PHONY: all clean flash debug