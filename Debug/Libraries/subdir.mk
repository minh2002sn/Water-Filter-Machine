################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/DS3231.c \
../Libraries/Keypad.c \
../Libraries/LCD_I2C.c \
../Libraries/Water_Level_Sensor.c \
../Libraries/flash.c 

OBJS += \
./Libraries/DS3231.o \
./Libraries/Keypad.o \
./Libraries/LCD_I2C.o \
./Libraries/Water_Level_Sensor.o \
./Libraries/flash.o 

C_DEPS += \
./Libraries/DS3231.d \
./Libraries/Keypad.d \
./Libraries/LCD_I2C.d \
./Libraries/Water_Level_Sensor.d \
./Libraries/flash.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/%.o Libraries/%.su: ../Libraries/%.c Libraries/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x8 -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/Libraries" -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/App" -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/App/Control" -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/App/Data" -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/App/Menu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libraries

clean-Libraries:
	-$(RM) ./Libraries/DS3231.d ./Libraries/DS3231.o ./Libraries/DS3231.su ./Libraries/Keypad.d ./Libraries/Keypad.o ./Libraries/Keypad.su ./Libraries/LCD_I2C.d ./Libraries/LCD_I2C.o ./Libraries/LCD_I2C.su ./Libraries/Water_Level_Sensor.d ./Libraries/Water_Level_Sensor.o ./Libraries/Water_Level_Sensor.su ./Libraries/flash.d ./Libraries/flash.o ./Libraries/flash.su

.PHONY: clean-Libraries

