################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ServConSelect.c \
../src/logger.c \
../src/mapeo\ y\ redirecciono.c \
../src/servidor.c \
../src/testBuscaBloqueYMarcaOcupado.c \
../src/testCliente.c \
../src/testCrearFilesystem.c \
../src/testeoModificaElemento.c 

OBJS += \
./src/ServConSelect.o \
./src/logger.o \
./src/mapeo\ y\ redirecciono.o \
./src/servidor.o \
./src/testBuscaBloqueYMarcaOcupado.o \
./src/testCliente.o \
./src/testCrearFilesystem.o \
./src/testeoModificaElemento.o 

C_DEPS += \
./src/ServConSelect.d \
./src/logger.d \
./src/mapeo\ y\ redirecciono.d \
./src/servidor.d \
./src/testBuscaBloqueYMarcaOcupado.d \
./src/testCliente.d \
./src/testCrearFilesystem.d \
./src/testeoModificaElemento.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/utnso/TPOperativos/delEquipo" -I"/home/utnso/TPOperativos/commons-library" -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/mapeo\ y\ redirecciono.o: ../src/mapeo\ y\ redirecciono.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/utnso/TPOperativos/delEquipo" -I"/home/utnso/TPOperativos/commons-library" -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"src/mapeo y redirecciono.d" -MT"src/mapeo\ y\ redirecciono.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


