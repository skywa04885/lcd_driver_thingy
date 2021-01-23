################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../Src/bitmaps.cc \
../Src/delay.cc \
../Src/fifo.cc \
../Src/main.cc \
../Src/sysclk.cc 

C_SRCS += \
../Src/syscalls.c \
../Src/sysmem.c 

C_DEPS += \
./Src/syscalls.d \
./Src/sysmem.d 

CC_DEPS += \
./Src/bitmaps.d \
./Src/delay.d \
./Src/fifo.d \
./Src/main.d \
./Src/sysclk.d 

OBJS += \
./Src/bitmaps.o \
./Src/delay.o \
./Src/fifo.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysclk.o \
./Src/sysmem.o 


# Each subdirectory must supply rules for building sources it contributes
Src/bitmaps.o: ../Src/bitmaps.cc
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DSTM32H750VBTx -DSTM32 -DSTM32H7SINGLE -DSTM32H7 -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/bitmaps.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/delay.o: ../Src/delay.cc
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DSTM32H750VBTx -DSTM32 -DSTM32H7SINGLE -DSTM32H7 -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/delay.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/fifo.o: ../Src/fifo.cc
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DSTM32H750VBTx -DSTM32 -DSTM32H7SINGLE -DSTM32H7 -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/fifo.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/main.o: ../Src/main.cc
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DSTM32H750VBTx -DSTM32 -DSTM32H7SINGLE -DSTM32H7 -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32H750VBTx -DSTM32 -DSTM32H7SINGLE -DSTM32H7 -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/sysclk.o: ../Src/sysclk.cc
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DSTM32H750VBTx -DSTM32 -DSTM32H7SINGLE -DSTM32H7 -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/sysclk.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32H750VBTx -DSTM32 -DSTM32H7SINGLE -DSTM32H7 -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

