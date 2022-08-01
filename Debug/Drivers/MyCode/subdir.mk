################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/MyCode/kalman.c \
../Drivers/MyCode/workman.c 

OBJS += \
./Drivers/MyCode/kalman.o \
./Drivers/MyCode/workman.o 

C_DEPS += \
./Drivers/MyCode/kalman.d \
./Drivers/MyCode/workman.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/MyCode/%.o Drivers/MyCode/%.su: ../Drivers/MyCode/%.c Drivers/MyCode/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DARM_MATH_CM7 -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"D:/ST/workspace/H7_Voice/DSP/Include" -I"D:/ST/workspace/H7_Voice/Drivers/MyCode" -I"D:/ST/workspace/H7_Voice/Drivers/mytft/mytft" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-MyCode

clean-Drivers-2f-MyCode:
	-$(RM) ./Drivers/MyCode/kalman.d ./Drivers/MyCode/kalman.o ./Drivers/MyCode/kalman.su ./Drivers/MyCode/workman.d ./Drivers/MyCode/workman.o ./Drivers/MyCode/workman.su

.PHONY: clean-Drivers-2f-MyCode

