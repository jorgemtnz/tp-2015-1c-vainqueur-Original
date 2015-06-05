################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/clienteServidorMultihilo.c 

OBJS += \
./src/clienteServidorMultihilo.o 

C_DEPS += \
./src/clienteServidorMultihilo.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/utnso/TpOperativos/tp-2015-1c-vainqueur/delEquipo" -I"/home/utnso/TpOperativos/tp-2015-1c-vainqueur/commons-library" -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


