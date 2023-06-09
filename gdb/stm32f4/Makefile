# make is alias for make all
.DEFAULT_GOAL := all

# Name of recipes
.PHONY: all llaunch mlaunch clean fclean re

################################################################################
#								PROJECT	CONFIG 								   #
################################################################################

# Selecting Core (STM32F0 cortex-M0)
CORTEX_M = 4
CORE = CM$(CORTEX_M)

# Project name
NAME = GDB-$(CORE).elf

# Compiler, Linker & Debugger
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
DB = arm-none-eabi-gdb

# Launch debug from Linux (Ubuntu/Debian)
GDB = gdb-multiarch

# Flash utility
FLASH_TOOL = openocd

# Include directories given to GCC
DIR_INC_LOCAL = inc

# Start up file repository
DIR_ASM = startup_file

# Linker script file repository
DIR_LKS = linker_script

# OpenOCD debug script file repository
DIR_OCD_SCRIPT = openocd

# Object files repository
DIR_OBJ = obj

# VPATH name to find *.c files
vpath %.c src/

################################################################################
#							PROJECT FILES									   #
################################################################################

# Start up file name (I have commented a line so I made a local copy)
FILE_ASM = startup_stm32f413xx.s

# Linker script file name (I have commented a line so I made a local copy)
FILE_LKS = STM32F413ZH_FLASH.ld

# Files used for building project
FILE_SRC = main.c \
		   stm32f4xx_it.c \
		   system_stm32f4xx.c

FILE_OBJ = $(FILE_SRC:.c=.o)
FILE_OBJ += $(FILE_ASM:.s=.o)

OBJ = $(addprefix $(DIR_OBJ)/, $(FILE_OBJ))
ASM = $(addprefix $(DIR_ASM)/, $(FILE_ASM))

################################################################################
#							GCC COMPILATION FLAGS							   #
################################################################################

# Architecture flags (ARM)
ARCH_FLAGS =-mthumb -mcpu=cortex-m$(CORTEX_M) -mlittle-endian -mthumb

# Debug flags
DBG_FLAGS = -g3

# Floating point flags (ARM) no hardware floating point support, only soft
FP_FLAGS =  -mfloat-abi=hard -mfpu=fpv4-sp-d16

# Include path flags
INC_LOCAL_FLAG = $(addprefix -I , $(DIR_INC_LOCAL))

# All flags together
INC_FLAGS = $(INC_LOCAL_FLAG)

# DEFINE/MACRO flags
DM_FLAGS = -DSTM32F413_423xx

# Compiling Optimization flags (add -0s for best optimization flag)
CO_FLAGS = -ffunction-sections -fdata-sections

# Warning flags
WRN_FLAGS = -Werror -Wall -Wextra

# All flags for GCC compiling step
GCC_FLAGS = $(ARCH_FLAGS) $(DBG_FLAGS) $(FP_FLAGS) $(INC_FLAGS) \
		  	$(DM_FLAGS) $(CO_FLAGS) $(WRN_FLAGS)

################################################################################
#								LINKING										   #
################################################################################

# Linking Optimization flags
LO_FLAGS = --gc-sections

# Map File flags
MAP_FLAGS = -Map=$(NAME).map

# Linking Script file (I have commented 3 line a the end so I made a local copy)
LS_FLAGS = -T $(DIR_LKS)/$(FILE_LKS)

# All flags for LD linking step
LD_FLAGS = $(LS_FLAGS) $(LO_FLAGS) $(MAP_FLAGS)

################################################################################
#								MAKE RULES									   #
################################################################################

all: $(NAME)

$(NAME): $(OBJ)
	$(LD) $^ -o $@ $(LD_FLAGS)
	@echo "\033[33;32m=== Linking $(NAME)...\t\t\tDONE\033[0m"
	@echo "---------------------------------------------------------------------"

# Build *.c file
$(DIR_OBJ)/%.o: %.c
	@mkdir -p obj
	$(CC) $(GCC_FLAGS) -o $@ -c $<
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
	@echo "---------------------------------------------------------------------"

# Build *.s file
$(DIR_OBJ)/%.o: $(DIR_ASM)/%.s
	@mkdir -p obj
	$(CC) $(GCC_FLAGS) -o $@ -c $<
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
	@echo "---------------------------------------------------------------------"

# Linux (Debian) flash and launch debug session
debug:
	@$(DB) -q $(NAME) -x $(DIR_OCD_SCRIPT)/openocd.gdb

flash: all
	@$(FLASH_TOOL) -f interface/stlink-v2.cfg -f target/stm32f0x.cfg -c "program $(NAME) verify reset exit"

# Delete all intermediate files
clean:
	@rm -rf *.map
	@rm -rf obj
	@echo "\033[33;32m=== Cleaning project $(DIR_OBJ) repository and $(NAME).map...\t\tDONE\033[0m"

# Delete all intermediate files and executable file
fclean: clean
	@rm -rf $(NAME)
	@echo "\033[33;32m=== Cleaning executable $(NAME)...\t\t\tDONE\033[0m"

# Clean and rebuild project
re: fclean all
