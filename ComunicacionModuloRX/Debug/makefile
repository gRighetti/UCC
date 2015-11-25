################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3

ORDERED_OBJS += \
"./src/main.obj" \
"./src/bsp/hal/hal_cc2500.obj" \
"./src/bsp/hal/hal_pin.obj" \
"./src/bsp/hal/hal_usci_spi.obj" \
"./src/bsp/hal/uart.obj" \
"./src/bsp/bsp.obj" \
"../lnk_msp430fg4619.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include src/subdir_vars.mk
-include src/bsp/hal/subdir_vars.mk
-include src/bsp/subdir_vars.mk
-include subdir_rules.mk
-include src/subdir_rules.mk
-include src/bsp/hal/subdir_rules.mk
-include src/bsp/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
ComunicacionModuloRX.out \

EXE_OUTPUTS__QUOTED += \
"ComunicacionModuloRX.out" \

BIN_OUTPUTS += \
ComunicacionModuloRX.hex \

BIN_OUTPUTS__QUOTED += \
"ComunicacionModuloRX.hex" \


# All Target
all: ComunicacionModuloRX.out

# Tool invocations
ComunicacionModuloRX.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/bin/cl430" -vmspx --abi=eabi --data_model=restricted -Ooff --use_hw_mpy=16 --advice:power_severity=suppress --advice:power="1,2,3,4,5,6,7,8,9,10,11,12,13,14,15" -g --define=__MSP430FG4619__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=nofloat -z -m"ComunicacionModuloRX.map" --heap_size=120 --stack_size=120 --cinit_hold_wdt=on -i"C:/ti/ccsv6/ccs_base/msp430/include" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="ComunicacionModuloRX_linkInfo.xml" --use_hw_mpy=16 --rom_model -o "ComunicacionModuloRX.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

ComunicacionModuloRX.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP430 Hex Utility'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/bin/hex430" --memwidth=8 --romwidth=8 -o "ComunicacionModuloRX.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "src\main.pp" "src\bsp\hal\hal_cc2500.pp" "src\bsp\hal\hal_pin.pp" "src\bsp\hal\hal_usci_spi.pp" "src\bsp\hal\uart.pp" "src\bsp\bsp.pp" 
	-$(RM) "src\main.obj" "src\bsp\hal\hal_cc2500.obj" "src\bsp\hal\hal_pin.obj" "src\bsp\hal\hal_usci_spi.obj" "src\bsp\hal\uart.obj" "src\bsp\bsp.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

