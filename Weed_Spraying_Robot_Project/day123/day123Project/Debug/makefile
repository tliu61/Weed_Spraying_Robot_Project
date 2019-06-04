################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := -l"./day123cfg.cmd"

ORDERED_OBJS += \
"./COECSL_edma3.obj" \
"./COECSL_mcbsp.obj" \
"./ColorLCD.obj" \
"./ColorVision.obj" \
"./LCDprintf.obj" \
"./Ladar.obj" \
"./MatrixMath.obj" \
"./day123cfg.obj" \
"./day123cfg_c.obj" \
"./pQueue.obj" \
"./pru.obj" \
"./user_day123.obj" \
"./user_xy.obj" \
"C:/tliu61_xz7/_shared/c67xmathlib_2_01_00_00/lib/c674xfastMath.lib" \
"C:/tliu61_xz7/_shared/bsl/lib/evmomapl138_bsl.lib" \
"C:/tliu61_xz7/mylabs/day123/lnk.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
day123.out \

EXE_OUTPUTS__QUOTED += \
"day123.out" \


# All Target
all: day123.out

# Tool invocations
day123.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/bin/cl6x" -mv6740 --abi=coffabi -O3 -g --define=RUNNING_ON_OMAPL138 --define=_DEBUG --diag_warning=225 --display_error_number -z -m"day123.map" --stack_size=0xc00 -i"C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/lib" -i"C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/include" -i"C:/CCStudio_v7/bios_5_42_02_10/packages/ti/rtdx/lib/c6000" -i"C:/CCStudio_v7/bios_5_42_02_10/packages/ti/bios/lib" --reread_libs --warn_sections --xml_link_info="day123_linkInfo.xml" --rom_model -o "day123.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(GEN_CMDS__QUOTED)$(GEN_MISC_FILES__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)$(GEN_HDRS__QUOTED)
	-$(RM) "day123cfg.d" 
	-$(RM) "COECSL_edma3.obj" "COECSL_mcbsp.obj" "ColorLCD.obj" "ColorVision.obj" "LCDprintf.obj" "Ladar.obj" "MatrixMath.obj" "day123cfg.obj" "day123cfg_c.obj" "pQueue.obj" "pru.obj" "user_day123.obj" "user_xy.obj" 
	-$(RM) "COECSL_edma3.d" "COECSL_mcbsp.d" "ColorLCD.d" "ColorVision.d" "LCDprintf.d" "Ladar.d" "MatrixMath.d" "day123cfg_c.d" "pQueue.d" "pru.d" "user_day123.d" "user_xy.d" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-"C:/tliu61_xz7/mylabs/day123/day123Project/../postBuildStep_Debug.bat" PROJECT_ROOT C:/tliu61_xz7/mylabs/day123/day123Project !
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

