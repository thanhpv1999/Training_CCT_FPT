################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/RD_Type_Device/RD_Type_Device.c 

OBJS += \
./vendor/RD_Type_Device/RD_Type_Device.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/RD_Type_Device/%.o: ../vendor/RD_Type_Device/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"C:\telink2_den_sw\fpt\Training_CCT_FPT\firmware" -I"C:\telink2_den_sw\fpt\Training_CCT_FPT\firmware\vendor\common\mi_api\libs" -I"C:\telink2_den_sw\fpt\Training_CCT_FPT\firmware\vendor\common\mi_api\mijia_ble_api" -D__PROJECT_MESH__=1 -D__telink__ -DCHIP_TYPE=CHIP_TYPE_8258 -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


