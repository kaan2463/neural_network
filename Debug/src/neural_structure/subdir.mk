################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/neural_structure/NN.cpp \
../src/neural_structure/NeuralStructure.cpp 

OBJS += \
./src/neural_structure/NN.o \
./src/neural_structure/NeuralStructure.o 

CPP_DEPS += \
./src/neural_structure/NN.d \
./src/neural_structure/NeuralStructure.d 


# Each subdirectory must supply rules for building sources it contributes
src/neural_structure/%.o: ../src/neural_structure/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


