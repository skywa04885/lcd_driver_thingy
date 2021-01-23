################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../Src/drivers/ili9341.cc \
../Src/drivers/ir.cc \
../Src/drivers/nrf24l01.cc 

CC_DEPS += \
./Src/drivers/ili9341.d \
./Src/drivers/ir.d \
./Src/drivers/nrf24l01.d 

OBJS += \
./Src/drivers/ili9341.o \
./Src/drivers/ir.o \
./Src/drivers/nrf24l01.o 


# Each subdirectory must supply rules for building sources it contributes
Src/drivers/ili9341.o: ../Src/drivers/ili9341.cc
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -DSTM32H750VBTx -DSTM32 -DSTM32H7SINGLE -DSTM32H7 -c -I../Inc -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/drivers/ili9341.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/drivers/ir.o: ../Src/drivers/ir.cc
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -DSTM32H750VBTx -DSTM32 -DSTM32H7SINGLE -DSTM32H7 -c -I../Inc -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/drivers/ir.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/drivers/nrf24l01.o: ../Src/drivers/nrf24l01.cc
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -DSTM32H750VBTx -DSTM32 -DSTM32H7SINGLE -DSTM32H7 -c -I../Inc -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/drivers/nrf24l01.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

