################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../funcionesAuxiliares.c \
../funcionesConsola.c \
../funcionesConstructoras.c \
../funcionesDestructoras.c \
../main.c 

OBJS += \
./funcionesAuxiliares.o \
./funcionesConsola.o \
./funcionesConstructoras.o \
./funcionesDestructoras.o \
./main.o 

C_DEPS += \
./funcionesAuxiliares.d \
./funcionesConsola.d \
./funcionesConstructoras.d \
./funcionesDestructoras.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/utnso/TPOperativos/delEquipo" -I"/home/utnso/TPOperativos/commons-library" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


