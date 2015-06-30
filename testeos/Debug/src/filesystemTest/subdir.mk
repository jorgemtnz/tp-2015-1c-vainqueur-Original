################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/filesystemTest/funcionesAuxiliares.c \
../src/filesystemTest/funcionesConsola.c \
../src/filesystemTest/funcionesConstructoras.c \
../src/filesystemTest/funcionesDestructoras.c 

OBJS += \
./src/filesystemTest/funcionesAuxiliares.o \
./src/filesystemTest/funcionesConsola.o \
./src/filesystemTest/funcionesConstructoras.o \
./src/filesystemTest/funcionesDestructoras.o 

C_DEPS += \
./src/filesystemTest/funcionesAuxiliares.d \
./src/filesystemTest/funcionesConsola.d \
./src/filesystemTest/funcionesConstructoras.d \
./src/filesystemTest/funcionesDestructoras.d 


# Each subdirectory must supply rules for building sources it contributes
src/filesystemTest/%.o: ../src/filesystemTest/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/utnso/TPOperativos/delEquipo" -I"/home/utnso/TPOperativos/commons-library" -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


