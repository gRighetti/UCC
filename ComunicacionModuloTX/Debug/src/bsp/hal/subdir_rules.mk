################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/bsp/hal/hal_cc2500.obj: ../src/bsp/hal/hal_cc2500.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/bin/cl430" -vmspx --abi=eabi --data_model=restricted -Ooff --use_hw_mpy=16 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/include" --advice:power_severity=suppress --advice:power="1,2,3,4,5,6,7,8,9,10,11,12,13,14,15" -g --define=__MSP430FG4619__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=nofloat --preproc_with_compile --preproc_dependency="src/bsp/hal/hal_cc2500.pp" --obj_directory="src/bsp/hal" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/hal/hal_pin.obj: ../src/bsp/hal/hal_pin.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/bin/cl430" -vmspx --abi=eabi --data_model=restricted -Ooff --use_hw_mpy=16 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/include" --advice:power_severity=suppress --advice:power="1,2,3,4,5,6,7,8,9,10,11,12,13,14,15" -g --define=__MSP430FG4619__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=nofloat --preproc_with_compile --preproc_dependency="src/bsp/hal/hal_pin.pp" --obj_directory="src/bsp/hal" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/hal/hal_usci_spi.obj: ../src/bsp/hal/hal_usci_spi.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/bin/cl430" -vmspx --abi=eabi --data_model=restricted -Ooff --use_hw_mpy=16 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/include" --advice:power_severity=suppress --advice:power="1,2,3,4,5,6,7,8,9,10,11,12,13,14,15" -g --define=__MSP430FG4619__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=nofloat --preproc_with_compile --preproc_dependency="src/bsp/hal/hal_usci_spi.pp" --obj_directory="src/bsp/hal" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/hal/uart.obj: ../src/bsp/hal/uart.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/bin/cl430" -vmspx --abi=eabi --data_model=restricted -Ooff --use_hw_mpy=16 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/include" --advice:power_severity=suppress --advice:power="1,2,3,4,5,6,7,8,9,10,11,12,13,14,15" -g --define=__MSP430FG4619__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=nofloat --preproc_with_compile --preproc_dependency="src/bsp/hal/uart.pp" --obj_directory="src/bsp/hal" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


