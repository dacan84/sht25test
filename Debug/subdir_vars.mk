################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../lnk_msp430fr5739.cmd 

CFG_SRCS += \
../main.cfg 

C_SRCS += \
../I2C_HAL.c \
../SHT2x.c \
../System.c \
../main.c 

OBJS += \
./I2C_HAL.obj \
./SHT2x.obj \
./System.obj \
./main.obj 

C_DEPS += \
./I2C_HAL.pp \
./SHT2x.pp \
./System.pp \
./main.pp 

GEN_MISC_DIRS += \
./configPkg/ 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_OPTS += \
./configPkg/compiler.opt 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_FILES__QUOTED += \
"configPkg\linker.cmd" \
"configPkg\compiler.opt" 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

C_DEPS__QUOTED += \
"I2C_HAL.pp" \
"SHT2x.pp" \
"System.pp" \
"main.pp" 

OBJS__QUOTED += \
"I2C_HAL.obj" \
"SHT2x.obj" \
"System.obj" \
"main.obj" 

C_SRCS__QUOTED += \
"../I2C_HAL.c" \
"../SHT2x.c" \
"../System.c" \
"../main.c" 

GEN_CMDS__FLAG += \
-l"./configPkg/linker.cmd" 

GEN_OPTS__FLAG += \
--cmd_file="./configPkg/compiler.opt" 


