################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/image.c \
../code/my_encoder.c \
../code/my_motor.c \
../code/my_servo.c \
../code/my_usart.c 

COMPILED_SRCS += \
./code/image.src \
./code/my_encoder.src \
./code/my_motor.src \
./code/my_servo.src \
./code/my_usart.src 

C_DEPS += \
./code/image.d \
./code/my_encoder.d \
./code/my_motor.d \
./code/my_servo.d \
./code/my_usart.d 

OBJS += \
./code/image.o \
./code/my_encoder.o \
./code/my_motor.o \
./code/my_servo.o \
./code/my_usart.o 


# Each subdirectory must supply rules for building sources it contributes
code/%.src: ../code/%.c code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/86152/AURIX-v1.9.12-workspace/Seekfree_TC264_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/code\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

code/%.o: ./code/%.src code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-code

clean-code:
	-$(RM) ./code/image.d ./code/image.o ./code/image.src ./code/my_encoder.d ./code/my_encoder.o ./code/my_encoder.src ./code/my_motor.d ./code/my_motor.o ./code/my_motor.src ./code/my_servo.d ./code/my_servo.o ./code/my_servo.src ./code/my_usart.d ./code/my_usart.o ./code/my_usart.src

.PHONY: clean-code

