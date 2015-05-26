################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -vcpu:3.3 -g -O3 --include_path="C:/ti/ccsv6/tools/compiler/c5500_4.4.1/include" --include_path="../../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --opt_for_speed=5 --gen_opt_info=2 --opt_for_space=3 --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


