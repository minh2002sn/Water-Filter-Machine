################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Menu/Main_menu.c \
../App/Menu/Menu.c \
../App/Menu/Setting_menu.c 

OBJS += \
./App/Menu/Main_menu.o \
./App/Menu/Menu.o \
./App/Menu/Setting_menu.o 

C_DEPS += \
./App/Menu/Main_menu.d \
./App/Menu/Menu.d \
./App/Menu/Setting_menu.d 


# Each subdirectory must supply rules for building sources it contributes
App/Menu/%.o App/Menu/%.su: ../App/Menu/%.c App/Menu/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x8 -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/Libraries" -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/App" -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/App/Control" -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/App/Data" -I"D:/A_Minh/B_Big Projects/Water Filter Machine/Code/STM_Code/Water_Filter_Machine_1.0/App/Menu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-Menu

clean-App-2f-Menu:
	-$(RM) ./App/Menu/Main_menu.d ./App/Menu/Main_menu.o ./App/Menu/Main_menu.su ./App/Menu/Menu.d ./App/Menu/Menu.o ./App/Menu/Menu.su ./App/Menu/Setting_menu.d ./App/Menu/Setting_menu.o ./App/Menu/Setting_menu.su

.PHONY: clean-App-2f-Menu

