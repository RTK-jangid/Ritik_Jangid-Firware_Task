################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/Src/stm32f407_FLASH_drivers.c \
../drivers/Src/stm32f407_GPIOx_drivers.c \
../drivers/Src/stm32f407_USART_drivers.c \
../drivers/Src/stm32f40_RCC_drivers.c 

OBJS += \
./drivers/Src/stm32f407_FLASH_drivers.o \
./drivers/Src/stm32f407_GPIOx_drivers.o \
./drivers/Src/stm32f407_USART_drivers.o \
./drivers/Src/stm32f40_RCC_drivers.o 

C_DEPS += \
./drivers/Src/stm32f407_FLASH_drivers.d \
./drivers/Src/stm32f407_GPIOx_drivers.d \
./drivers/Src/stm32f407_USART_drivers.d \
./drivers/Src/stm32f40_RCC_drivers.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/Src/%.o drivers/Src/%.su drivers/Src/%.cyclo: ../drivers/Src/%.c drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -c -I"/home/ritik/STM32CubeIDE/workspace_1.15.0/Ritik_Jangid_Firmware_Task/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drivers-2f-Src

clean-drivers-2f-Src:
	-$(RM) ./drivers/Src/stm32f407_FLASH_drivers.cyclo ./drivers/Src/stm32f407_FLASH_drivers.d ./drivers/Src/stm32f407_FLASH_drivers.o ./drivers/Src/stm32f407_FLASH_drivers.su ./drivers/Src/stm32f407_GPIOx_drivers.cyclo ./drivers/Src/stm32f407_GPIOx_drivers.d ./drivers/Src/stm32f407_GPIOx_drivers.o ./drivers/Src/stm32f407_GPIOx_drivers.su ./drivers/Src/stm32f407_USART_drivers.cyclo ./drivers/Src/stm32f407_USART_drivers.d ./drivers/Src/stm32f407_USART_drivers.o ./drivers/Src/stm32f407_USART_drivers.su ./drivers/Src/stm32f40_RCC_drivers.cyclo ./drivers/Src/stm32f40_RCC_drivers.d ./drivers/Src/stm32f40_RCC_drivers.o ./drivers/Src/stm32f40_RCC_drivers.su

.PHONY: clean-drivers-2f-Src

