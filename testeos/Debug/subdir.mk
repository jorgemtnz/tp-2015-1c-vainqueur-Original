################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../logger.c \
../mapeo\ y\ redirecciono.c \
../servidor.c \
../testBuscaBloqueYMarcaOcupado.c \
../testCliente.c \
../testCrearFilesystem.c \
../testeoModificaElemento.c 

OBJS += \
./logger.o \
./mapeo\ y\ redirecciono.o \
./servidor.o \
./testBuscaBloqueYMarcaOcupado.o \
./testCliente.o \
./testCrearFilesystem.o \
./testeoModificaElemento.o 

C_DEPS += \
./logger.d \
./mapeo\ y\ redirecciono.d \
./servidor.d \
./testBuscaBloqueYMarcaOcupado.d \
./testCliente.d \
./testCrearFilesystem.d \
./testeoModificaElemento.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/utnso/TPOperativos/delEquipo" -I"/home/utnso/TPOperativos/commons-library" -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

mapeo\ y\ redirecciono.o: ../mapeo\ y\ redirecciono.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/utnso/TPOperativos/delEquipo" -I"/home/utnso/TPOperativos/commons-library" -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"mapeo y redirecciono.d" -MT"mapeo\ y\ redirecciono.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


