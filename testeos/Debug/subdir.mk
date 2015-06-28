################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mapeo\ y\ redirecciono.c 

OBJS += \
./mapeo\ y\ redirecciono.o 

C_DEPS += \
./mapeo\ y\ redirecciono.d 


# Each subdirectory must supply rules for building sources it contributes
mapeo\ y\ redirecciono.o: ../mapeo\ y\ redirecciono.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/utnso/TPOperativos/delEquipo" -I"/home/utnso/TPOperativos/commons-library" -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"mapeo y redirecciono.d" -MT"mapeo\ y\ redirecciono.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


