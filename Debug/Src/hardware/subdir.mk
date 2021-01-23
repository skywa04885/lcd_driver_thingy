################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../Src/hardware/rng.cc \
../Src/hardware/rs232.cc \
../Src/hardware/rtc.cc \
../Src/hardware/spi.cc 

CC_DEPS += \
./Src/hardware/rng.d \
./Src/hardware/rs232.d \
./Src/hardware/rtc.d \
./Src/hardware/spi.d 

OBJS += \
./Src/hardware/rng.o \
./Src/hardware/rs232.o \
./Src/hardware/rtc.o \
./Src/hardware/spi.o 


# Each subdirectory must supply rules for building sources it contributes
Src/hardware/rng.o: ../Src/hardware/rng.cc
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DSTM32H750VBTx -DSTM32 -DSTM32H7SINGLE -DSTM32H7 -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/hardware/rng.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/hardware/rs232.o: ../Src/hardware/rs232.cc
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DSTM32H750VBTx -DSTM32 -DSTM32H7SINGLE -DSTM32H7 -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/hardware/rs232.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/hardware/rtc.o: ../Src/hardware/rtc.cc
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DSTM32H750VBTx -DSTM32 -DSTM32H7SINGLE -DSTM32H7 -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/hardware/rtc.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/hardware/spi.o: ../Src/hardware/spi.cc
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DSTM32H750VBTx -DSTM32 -DSTM32H7SINGLE -DSTM32H7 -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/hardware/spi.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

