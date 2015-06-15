################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: filesystem

dependents:
	-cd /home/utnso/TPOperativos/commons-library/Debug && $(MAKE) all
	-cd /home/utnso/TPOperativos/delEquipo/Debug && $(MAKE) all

# Tool invocations
filesystem: $(OBJS) $(USER_OBJS) /home/utnso/TPOperativos/commons-library/Debug/libcommons-library.so /home/utnso/TPOperativos/delEquipo/Debug/libdelEquipo.so
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc -L"/home/utnso/TPOperativos/delEquipo/Debug" -L"/home/utnso/TPOperativos/commons-library/Debug" -o "filesystem" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) filesystem
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/home/utnso/TPOperativos/commons-library/Debug/libcommons-library.so:
/home/utnso/TPOperativos/delEquipo/Debug/libdelEquipo.so:

-include ../makefile.targets
