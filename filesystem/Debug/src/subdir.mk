################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/anteriorMain.c \
../src/envioYRecepcionMensajeFS.c \
../src/funcionesAuxiliares.c \
../src/funcionesConsola.c \
../src/funcionesConstructoras.c \
../src/funcionesDestructoras.c \
../src/mainFilesystem.c 

OBJS += \
./src/anteriorMain.o \
./src/envioYRecepcionMensajeFS.o \
./src/funcionesAuxiliares.o \
./src/funcionesConsola.o \
./src/funcionesConstructoras.o \
./src/funcionesDestructoras.o \
./src/mainFilesystem.o 

C_DEPS += \
./src/anteriorMain.d \
./src/envioYRecepcionMensajeFS.d \
./src/funcionesAuxiliares.d \
./src/funcionesConsola.d \
./src/funcionesConstructoras.d \
./src/funcionesDestructoras.d \
./src/mainFilesystem.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/utnso/TPOperativos/delEquipo" -I"/home/utnso/TPOperativos/commons-library" -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


