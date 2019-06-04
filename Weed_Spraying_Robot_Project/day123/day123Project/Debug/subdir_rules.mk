################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
COECSL_edma3.obj: C:/tliu61_xz7/mylabs/day123/src/COECSL_edma3.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/bin/cl6x" -mv6740 --abi=coffabi -O3 -g --include_path="C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/include" --include_path="C:/tliu61_xz7/_shared/bsl/inc" --include_path="C:/tliu61_xz7/mylabs/day123" --include_path="C:/tliu61_xz7/_shared/c67xmathlib_2_01_00_00/inc" --include_path="C:/tliu61_xz7/_shared/mcbsp_com" --include_path="C:/tliu61_xz7/_shared/sharedmem_com" --include_path="C:/tliu61_xz7/mylabs/day123/include" --include_path="C:/tliu61_xz7/mylabs/day123/day123Project/Debug" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/rtdx/include/c6000" --define=RUNNING_ON_OMAPL138 --define=_DEBUG --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="COECSL_edma3.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

COECSL_mcbsp.obj: C:/tliu61_xz7/mylabs/day123/src/COECSL_mcbsp.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/bin/cl6x" -mv6740 --abi=coffabi -O3 -g --include_path="C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/include" --include_path="C:/tliu61_xz7/_shared/bsl/inc" --include_path="C:/tliu61_xz7/mylabs/day123" --include_path="C:/tliu61_xz7/_shared/c67xmathlib_2_01_00_00/inc" --include_path="C:/tliu61_xz7/_shared/mcbsp_com" --include_path="C:/tliu61_xz7/_shared/sharedmem_com" --include_path="C:/tliu61_xz7/mylabs/day123/include" --include_path="C:/tliu61_xz7/mylabs/day123/day123Project/Debug" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/rtdx/include/c6000" --define=RUNNING_ON_OMAPL138 --define=_DEBUG --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="COECSL_mcbsp.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ColorLCD.obj: C:/tliu61_xz7/mylabs/day123/src/ColorLCD.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/bin/cl6x" -mv6740 --abi=coffabi -O3 -g --include_path="C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/include" --include_path="C:/tliu61_xz7/_shared/bsl/inc" --include_path="C:/tliu61_xz7/mylabs/day123" --include_path="C:/tliu61_xz7/_shared/c67xmathlib_2_01_00_00/inc" --include_path="C:/tliu61_xz7/_shared/mcbsp_com" --include_path="C:/tliu61_xz7/_shared/sharedmem_com" --include_path="C:/tliu61_xz7/mylabs/day123/include" --include_path="C:/tliu61_xz7/mylabs/day123/day123Project/Debug" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/rtdx/include/c6000" --define=RUNNING_ON_OMAPL138 --define=_DEBUG --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="ColorLCD.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ColorVision.obj: C:/tliu61_xz7/mylabs/day123/src/ColorVision.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/bin/cl6x" -mv6740 --abi=coffabi -O3 -g --include_path="C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/include" --include_path="C:/tliu61_xz7/_shared/bsl/inc" --include_path="C:/tliu61_xz7/mylabs/day123" --include_path="C:/tliu61_xz7/_shared/c67xmathlib_2_01_00_00/inc" --include_path="C:/tliu61_xz7/_shared/mcbsp_com" --include_path="C:/tliu61_xz7/_shared/sharedmem_com" --include_path="C:/tliu61_xz7/mylabs/day123/include" --include_path="C:/tliu61_xz7/mylabs/day123/day123Project/Debug" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/rtdx/include/c6000" --define=RUNNING_ON_OMAPL138 --define=_DEBUG --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="ColorVision.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

LCDprintf.obj: C:/tliu61_xz7/mylabs/day123/src/LCDprintf.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/bin/cl6x" -mv6740 --abi=coffabi -O3 -g --include_path="C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/include" --include_path="C:/tliu61_xz7/_shared/bsl/inc" --include_path="C:/tliu61_xz7/mylabs/day123" --include_path="C:/tliu61_xz7/_shared/c67xmathlib_2_01_00_00/inc" --include_path="C:/tliu61_xz7/_shared/mcbsp_com" --include_path="C:/tliu61_xz7/_shared/sharedmem_com" --include_path="C:/tliu61_xz7/mylabs/day123/include" --include_path="C:/tliu61_xz7/mylabs/day123/day123Project/Debug" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/rtdx/include/c6000" --define=RUNNING_ON_OMAPL138 --define=_DEBUG --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="LCDprintf.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Ladar.obj: C:/tliu61_xz7/mylabs/day123/src/Ladar.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/bin/cl6x" -mv6740 --abi=coffabi -O3 -g --include_path="C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/include" --include_path="C:/tliu61_xz7/_shared/bsl/inc" --include_path="C:/tliu61_xz7/mylabs/day123" --include_path="C:/tliu61_xz7/_shared/c67xmathlib_2_01_00_00/inc" --include_path="C:/tliu61_xz7/_shared/mcbsp_com" --include_path="C:/tliu61_xz7/_shared/sharedmem_com" --include_path="C:/tliu61_xz7/mylabs/day123/include" --include_path="C:/tliu61_xz7/mylabs/day123/day123Project/Debug" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/rtdx/include/c6000" --define=RUNNING_ON_OMAPL138 --define=_DEBUG --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="Ladar.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MatrixMath.obj: C:/tliu61_xz7/mylabs/day123/src/MatrixMath.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/bin/cl6x" -mv6740 --abi=coffabi -O3 -g --include_path="C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/include" --include_path="C:/tliu61_xz7/_shared/bsl/inc" --include_path="C:/tliu61_xz7/mylabs/day123" --include_path="C:/tliu61_xz7/_shared/c67xmathlib_2_01_00_00/inc" --include_path="C:/tliu61_xz7/_shared/mcbsp_com" --include_path="C:/tliu61_xz7/_shared/sharedmem_com" --include_path="C:/tliu61_xz7/mylabs/day123/include" --include_path="C:/tliu61_xz7/mylabs/day123/day123Project/Debug" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/rtdx/include/c6000" --define=RUNNING_ON_OMAPL138 --define=_DEBUG --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="MatrixMath.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

build-1005363553:
	@$(MAKE) -Onone -f subdir_rules.mk build-1005363553-inproc

build-1005363553-inproc: C:/tliu61_xz7/mylabs/day123/DSPBIOS/day123.tcf
	@echo 'Building file: $<'
	@echo 'Invoking: TConf'
	"C:/CCStudio_v7/bios_5_42_02_10/xdctools/tconf" -b -Dconfig.importPath="C:/CCStudio_v7/bios_5_42_02_10/packages;C:/tliu61_xz7/mylabs/day123/DSPBIOS;" "$<"
	@echo 'Finished building: $<'
	@echo ' '

day123cfg.cmd: build-1005363553 C:/tliu61_xz7/mylabs/day123/DSPBIOS/day123.tcf
day123cfg.s??: build-1005363553
day123cfg_c.c: build-1005363553
day123cfg.h: build-1005363553
day123cfg.h??: build-1005363553
day123.cdb: build-1005363553

day123cfg.obj: ./day123cfg.s?? $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/bin/cl6x" -mv6740 --abi=coffabi -O3 -g --include_path="C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/include" --include_path="C:/tliu61_xz7/_shared/bsl/inc" --include_path="C:/tliu61_xz7/mylabs/day123" --include_path="C:/tliu61_xz7/_shared/c67xmathlib_2_01_00_00/inc" --include_path="C:/tliu61_xz7/_shared/mcbsp_com" --include_path="C:/tliu61_xz7/_shared/sharedmem_com" --include_path="C:/tliu61_xz7/mylabs/day123/include" --include_path="C:/tliu61_xz7/mylabs/day123/day123Project/Debug" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/rtdx/include/c6000" --define=RUNNING_ON_OMAPL138 --define=_DEBUG --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="day123cfg.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

day123cfg_c.obj: ./day123cfg_c.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/bin/cl6x" -mv6740 --abi=coffabi -O3 -g --include_path="C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/include" --include_path="C:/tliu61_xz7/_shared/bsl/inc" --include_path="C:/tliu61_xz7/mylabs/day123" --include_path="C:/tliu61_xz7/_shared/c67xmathlib_2_01_00_00/inc" --include_path="C:/tliu61_xz7/_shared/mcbsp_com" --include_path="C:/tliu61_xz7/_shared/sharedmem_com" --include_path="C:/tliu61_xz7/mylabs/day123/include" --include_path="C:/tliu61_xz7/mylabs/day123/day123Project/Debug" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/rtdx/include/c6000" --define=RUNNING_ON_OMAPL138 --define=_DEBUG --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="day123cfg_c.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pQueue.obj: C:/tliu61_xz7/mylabs/day123/src/pQueue.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/bin/cl6x" -mv6740 --abi=coffabi -O3 -g --include_path="C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/include" --include_path="C:/tliu61_xz7/_shared/bsl/inc" --include_path="C:/tliu61_xz7/mylabs/day123" --include_path="C:/tliu61_xz7/_shared/c67xmathlib_2_01_00_00/inc" --include_path="C:/tliu61_xz7/_shared/mcbsp_com" --include_path="C:/tliu61_xz7/_shared/sharedmem_com" --include_path="C:/tliu61_xz7/mylabs/day123/include" --include_path="C:/tliu61_xz7/mylabs/day123/day123Project/Debug" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/rtdx/include/c6000" --define=RUNNING_ON_OMAPL138 --define=_DEBUG --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="pQueue.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pru.obj: C:/tliu61_xz7/mylabs/day123/src/pru.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/bin/cl6x" -mv6740 --abi=coffabi -O3 -g --include_path="C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/include" --include_path="C:/tliu61_xz7/_shared/bsl/inc" --include_path="C:/tliu61_xz7/mylabs/day123" --include_path="C:/tliu61_xz7/_shared/c67xmathlib_2_01_00_00/inc" --include_path="C:/tliu61_xz7/_shared/mcbsp_com" --include_path="C:/tliu61_xz7/_shared/sharedmem_com" --include_path="C:/tliu61_xz7/mylabs/day123/include" --include_path="C:/tliu61_xz7/mylabs/day123/day123Project/Debug" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/rtdx/include/c6000" --define=RUNNING_ON_OMAPL138 --define=_DEBUG --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="pru.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

user_day123.obj: C:/tliu61_xz7/mylabs/day123/src/user_day123.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/bin/cl6x" -mv6740 --abi=coffabi -O3 -g --include_path="C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/include" --include_path="C:/tliu61_xz7/_shared/bsl/inc" --include_path="C:/tliu61_xz7/mylabs/day123" --include_path="C:/tliu61_xz7/_shared/c67xmathlib_2_01_00_00/inc" --include_path="C:/tliu61_xz7/_shared/mcbsp_com" --include_path="C:/tliu61_xz7/_shared/sharedmem_com" --include_path="C:/tliu61_xz7/mylabs/day123/include" --include_path="C:/tliu61_xz7/mylabs/day123/day123Project/Debug" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/rtdx/include/c6000" --define=RUNNING_ON_OMAPL138 --define=_DEBUG --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="user_day123.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

user_xy.obj: C:/tliu61_xz7/mylabs/day123/src/user_xy.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/bin/cl6x" -mv6740 --abi=coffabi -O3 -g --include_path="C:/CCStudio_v7/ccsv7/tools/compiler/c6000_7.4.22/include" --include_path="C:/tliu61_xz7/_shared/bsl/inc" --include_path="C:/tliu61_xz7/mylabs/day123" --include_path="C:/tliu61_xz7/_shared/c67xmathlib_2_01_00_00/inc" --include_path="C:/tliu61_xz7/_shared/mcbsp_com" --include_path="C:/tliu61_xz7/_shared/sharedmem_com" --include_path="C:/tliu61_xz7/mylabs/day123/include" --include_path="C:/tliu61_xz7/mylabs/day123/day123Project/Debug" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/CCStudio_v7/bios_5_42_02_10/packages/ti/rtdx/include/c6000" --define=RUNNING_ON_OMAPL138 --define=_DEBUG --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="user_xy.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


