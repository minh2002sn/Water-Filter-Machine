################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libs/DS3231.c \
../Libs/Keypad.c \
../Libs/LCD_I2C.c \
../Libs/flash.c 

OBJS += \
./Libs/DS3231.o \
./Libs/Keypad.o \
./Libs/LCD_I2C.o \
./Libs/flash.o 

C_DEPS += \
./Libs/DS3231.d \
./Libs/Keypad.d \
./Libs/LCD_I2C.d \
./Libs/flash.d 


# Each subdirectory must supply rules for building sources it contributes
Libs/%.o Libs/%.su: ../Libs/%.c Libs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x8 -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/App" -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/App/Control" -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/App/Menu" -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/Libs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libs

clean-Libs:
	-$(RM) ./Libs/DS3231.d ./Libs/DS3231.o ./Libs/DS3231.su ./Libs/Keypad.d ./Libs/Keypad.o ./Libs/Keypad.su ./Libs/LCD_I2C.d ./Libs/LCD_I2C.o ./Libs/LCD_I2C.su ./Libs/flash.d ./Libs/flash.o ./Libs/flash.su

.PHONY: clean-Libs

