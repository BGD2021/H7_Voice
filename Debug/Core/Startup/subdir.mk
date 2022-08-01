################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32h743iitx.s 

OBJS += \
./Core/Startup/startup_stm32h743iitx.o 

S_DEPS += \
./Core/Startup/startup_stm32h743iitx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -D__FPU_PRESENT=1 -D__FPU_USED=1 -D__TARGET_FPU_VFP -DARM_MATH_CM4 -DARM_MATH_CM7 -DARM_MATH_CM7 -c -I"G:/CubeProject/H7_Voice/MyCode/Inc" -I"G:/CubeProject/H7_Voice/DSP/Include" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32h743iitx.d ./Core/Startup/startup_stm32h743iitx.o

.PHONY: clean-Core-2f-Startup

