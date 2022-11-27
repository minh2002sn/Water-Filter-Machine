################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Control/Control.c \
../App/Control/Motor.c \
../App/Control/Relay.c 

OBJS += \
./App/Control/Control.o \
./App/Control/Motor.o \
./App/Control/Relay.o 

C_DEPS += \
./App/Control/Control.d \
./App/Control/Motor.d \
./App/Control/Relay.d 


# Each subdirectory must supply rules for building sources it contributes
App/Control/%.o App/Control/%.su: ../App/Control/%.c App/Control/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x8 -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/Libraries" -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/App" -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/App/Control" -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/App/Data" -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/App/Menu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-Control

clean-App-2f-Control:
	-$(RM) ./App/Control/Control.d ./App/Control/Control.o ./App/Control/Control.su ./App/Control/Motor.d ./App/Control/Motor.o ./App/Control/Motor.su ./App/Control/Relay.d ./App/Control/Relay.o ./App/Control/Relay.su

.PHONY: clean-App-2f-Control

