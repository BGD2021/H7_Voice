################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/mytft/mytft/cmd_process.c \
../Drivers/mytft/mytft/cmd_queue.c \
../Drivers/mytft/mytft/hmi_driver.c \
../Drivers/mytft/mytft/hmi_user_uart.c 

OBJS += \
./Drivers/mytft/mytft/cmd_process.o \
./Drivers/mytft/mytft/cmd_queue.o \
./Drivers/mytft/mytft/hmi_driver.o \
./Drivers/mytft/mytft/hmi_user_uart.o 

C_DEPS += \
./Drivers/mytft/mytft/cmd_process.d \
./Drivers/mytft/mytft/cmd_queue.d \
./Drivers/mytft/mytft/hmi_driver.d \
./Drivers/mytft/mytft/hmi_user_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/mytft/mytft/%.o Drivers/mytft/mytft/%.su: ../Drivers/mytft/mytft/%.c Drivers/mytft/mytft/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DARM_MATH_CM7 -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"D:/ST/workspace/H7_Voice/DSP/Include" -I"D:/ST/workspace/H7_Voice/Drivers/MyCode" -I"D:/ST/workspace/H7_Voice/Drivers/mytft/mytft" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-mytft-2f-mytft

clean-Drivers-2f-mytft-2f-mytft:
	-$(RM) ./Drivers/mytft/mytft/cmd_process.d ./Drivers/mytft/mytft/cmd_process.o ./Drivers/mytft/mytft/cmd_process.su ./Drivers/mytft/mytft/cmd_queue.d ./Drivers/mytft/mytft/cmd_queue.o ./Drivers/mytft/mytft/cmd_queue.su ./Drivers/mytft/mytft/hmi_driver.d ./Drivers/mytft/mytft/hmi_driver.o ./Drivers/mytft/mytft/hmi_driver.su ./Drivers/mytft/mytft/hmi_user_uart.d ./Drivers/mytft/mytft/hmi_user_uart.o ./Drivers/mytft/mytft/hmi_user_uart.su

.PHONY: clean-Drivers-2f-mytft-2f-mytft

