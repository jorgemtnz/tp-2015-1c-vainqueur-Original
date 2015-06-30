################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../filesystemTest/funcionesAuxiliares.c \
../filesystemTest/funcionesConsola.c \
../filesystemTest/funcionesConstructoras.c \
../filesystemTest/funcionesDestructoras.c 

OBJS += \
./filesystemTest/funcionesAuxiliares.o \
./filesystemTest/funcionesConsola.o \
./filesystemTest/funcionesConstructoras.o \
./filesystemTest/funcionesDestructoras.o 

C_DEPS += \
./filesystemTest/funcionesAuxiliares.d \
./filesystemTest/funcionesConsola.d \
./filesystemTest/funcionesConstructoras.d \
./filesystemTest/funcionesDestructoras.d 


# Each subdirectory must supply rules for building sources it contributes
filesystemTest/%.o: ../filesystemTest/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/utnso/TPOperativos/delEquipo" -I"/home/utnso/TPOperativos/commons-library" -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


