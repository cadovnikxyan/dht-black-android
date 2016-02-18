################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/dht.cpp \
../src/main.cpp \
../src/rwfile.cpp \
../src/socket.cpp 

OBJS += \
./src/dht.o \
./src/main.o \
./src/rwfile.o \
./src/socket.o 

CPP_DEPS += \
./src/dht.d \
./src/main.d \
./src/rwfile.d \
./src/socket.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	mips-openwrt-linux-g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


