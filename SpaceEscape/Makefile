###############################################################################
# Project settings
PROJECT := spaceescape
###############################################################################

# add files to be compiled

POKITTO_LIB_PATH = ../lib/PokittoLib/Pokitto

OBJECTS += assets/StationTiles.o
OBJECTS += assets/Map.o
OBJECTS += assets/Scene.o
OBJECTS += Main.o
#OBJECTS += World.o
#OBJECTS += Player.o

###############################################################################
# Boiler-plate

# cross-platform directory manipulation
ifeq ($(shell echo $$OS),$$OS)
    MAKEDIR = if not exist "$(1)" mkdir "$(1)"
    RM = rmdir /S /Q "$(1)"
else
    MAKEDIR = '$(SHELL)' -c "mkdir -p \"$(1)\""
    RM = '$(SHELL)' -c "rm -rf \"$(1)\""
endif

OBJDIR := BUILD
# Move to the build directory
ifeq (,$(filter $(OBJDIR),$(notdir $(CURDIR))))
.SUFFIXES:
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
MAKETARGET = '$(MAKE)' --no-print-directory -C $(OBJDIR) -f '$(mkfile_path)' \
		'SRCDIR=$(CURDIR)' $(MAKECMDGOALS)
.PHONY: $(OBJDIR) clean
all:
	+@$(call MAKEDIR,$(OBJDIR))
	+@$(MAKETARGET)
$(OBJDIR): all
Makefile : ;
% :: $(OBJDIR) ; :
clean :
	$(call RM,$(OBJDIR))

else

# trick rules into thinking we are in the root, when we are in the bulid dir
VPATH = ..

###############################################################################
# Objects and Paths

OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/TIC806x6.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/ZXSpec.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/adventurer12x16.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/donut7x10.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/dragon6x8.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/font3x3.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/font3x5.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/font5x7.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/fontC64.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/fontC64UIGfx.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/fontMonkey.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/karateka8x11.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/koubit7x7.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/mini4x6.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/runes6x8.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/tight4x7.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS/tiny5x7.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PALETTES/palAction.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PALETTES/palCGA.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PALETTES/palDB16.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PALETTES/palDefault.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PALETTES/palGameboy.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PALETTES/palMagma.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PALETTES/palMono.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PALETTES/palPico.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PALETTES/palRainbow.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PALETTES/palZXSpec.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PokittoBacklight.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PokittoBattery.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PokittoButtons.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PokittoConsole.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PokittoCore.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PokittoDisk.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PokittoDisplay.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/TASMODE.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PokittoFramebuffer.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PokittoItoa.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PokittoLogos.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PokittoPalette.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_CORE/PokittoSound.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_HW/HWButtons.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_HW/HWLCD.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_HW/HWSound.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_HW/PokittoClock.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_HW/PokittoHW.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_HW/Pokitto_extport.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_HW/SoftwareI2C.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_HW/clock_11u6x.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_HW/dma_11u6x.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_HW/iap.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_HW/timer_11u6x.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_HW/asm/mode1.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_HW/asm/mode2.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_HW/asm/mode13.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_HW/asm/mode15.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_HW/asm/mode64.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_LIBS/Synth/Synth.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_LIBS/Synth/Synth_envfuncs.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_LIBS/Synth/Synth_helpers.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_LIBS/Synth/Synth_mixfuncs.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_LIBS/Synth/Synth_oscfuncs.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_LIBS/Synth/Synth_songfuncs.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_LIBS/Synth/Synth_wavefuncs.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_LIBS/Tilemap/Tilemap.o
OBJECTS += $(POKITTO_LIB_PATH)/POKITTO_XTERNALS/Arduino/delay.o
OBJECTS += $(POKITTO_LIB_PATH)/libpff/mmc.o
OBJECTS += $(POKITTO_LIB_PATH)/libpff/pff.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/BusIn.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/BusInOut.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/BusOut.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/CAN.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/CallChain.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/Ethernet.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/FileBase.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/FileLike.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/FilePath.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/FileSystemLike.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/I2C.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/I2CSlave.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/InterruptIn.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/InterruptManager.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/LocalFileSystem.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/RawSerial.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/SPI.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/SPISlave.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/Serial.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/SerialBase.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/Stream.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/Ticker.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/Timeout.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/Timer.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/TimerEvent.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/assert.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/board.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/error.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/gpio.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/lp_ticker_api.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/mbed_interface.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/pinmap_common.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/retarget.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/rtc_time.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/semihost_api.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/ticker_api.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/us_ticker_api.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/common/wait_api.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/targets/cmsis/TARGET_NXP/TARGET_LPC11U6X/TOOLCHAIN_GCC_ARM/TARGET_LPC11U68/startup_LPC11U68.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/targets/cmsis/TARGET_NXP/TARGET_LPC11U6X/cmsis_nvic.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/targets/cmsis/TARGET_NXP/TARGET_LPC11U6X/system_LPC11U6x.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal/TARGET_NXP/TARGET_LPC11U6X/analogin_api.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal/TARGET_NXP/TARGET_LPC11U6X/gpio_api.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal/TARGET_NXP/TARGET_LPC11U6X/gpio_irq_api.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal/TARGET_NXP/TARGET_LPC11U6X/i2c_api.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal/TARGET_NXP/TARGET_LPC11U6X/pinmap.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal/TARGET_NXP/TARGET_LPC11U6X/pwmout_api.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal/TARGET_NXP/TARGET_LPC11U6X/rtc_api.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal/TARGET_NXP/TARGET_LPC11U6X/serial_api.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal/TARGET_NXP/TARGET_LPC11U6X/sleep.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal/TARGET_NXP/TARGET_LPC11U6X/spi_api.o
OBJECTS += $(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal/TARGET_NXP/TARGET_LPC11U6X/us_ticker.o

INCLUDE_PATHS += -I../:
INCLUDE_PATHS += -I../.
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/POKITTO_CORE
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/POKITTO_CORE/PALETTES
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/POKITTO_HW
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/POKITTO_LIBS
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/POKITTO_LIBS/ImageFormat
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/POKITTO_LIBS/Synth
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/POKITTO_LIBS/Tilemap
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/POKITTO_XTERNALS
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/POKITTO_XTERNALS/Arduino
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/libpff
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/mbed-pokitto
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/api
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/common
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/hal
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/cmsis
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/cmsis/TARGET_NXP
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/cmsis/TARGET_NXP/TARGET_LPC11U6X
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/cmsis/TARGET_NXP/TARGET_LPC11U6X/TOOLCHAIN_GCC_ARM
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/cmsis/TARGET_NXP/TARGET_LPC11U6X/TOOLCHAIN_GCC_ARM/TARGET_LPC11U68
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/cmsis/TOOLCHAIN_GCC
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal/TARGET_NXP
INCLUDE_PATHS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal/TARGET_NXP/TARGET_LPC11U6X

LIBRARY_PATHS :=
LIBRARIES :=
LINKER_SCRIPT ?= $(POKITTO_LIB_PATH)/mbed-pokitto/targets/cmsis/TARGET_NXP/TARGET_LPC11U6X/TOOLCHAIN_GCC_ARM/TARGET_LPC11U68/LPC11U68.ld

# Objects and Paths
###############################################################################
# Tools and Flags

AS      = 'arm-none-eabi-gcc' '-x' 'assembler-with-cpp' '-c' '-Wall' '-Wextra' '-Wno-unused-parameter' '-Wno-missing-field-initializers' '-fmessage-length=0' '-fno-exceptions' '-fno-builtin' '-ffunction-sections' '-fdata-sections' '-funsigned-char' '-MMD' '-fno-delete-null-pointer-checks' '-fomit-frame-pointer' '-O3' '-g1' '-DMBED_RTOS_SINGLE_THREAD' '-mcpu=cortex-m0plus' '-mthumb' '-fstrict-aliasing'
CC      = 'arm-none-eabi-gcc' '-std=gnu99' '-c' '-Wall' '-Wextra' '-Wno-unused-parameter' '-Wno-missing-field-initializers' '-fmessage-length=0' '-fno-exceptions' '-fno-builtin' '-ffunction-sections' '-fdata-sections' '-funsigned-char' '-MMD' '-fno-delete-null-pointer-checks' '-fomit-frame-pointer' '-O3' '-g1' '-DMBED_RTOS_SINGLE_THREAD' '-mcpu=cortex-m0plus' '-mthumb' '-fstrict-aliasing'
CPP     = 'arm-none-eabi-g++' '-std=c++17' '-fno-rtti' '-Wvla' '-c' '-Wall' '-Wextra' '-Wno-unused-parameter' '-Wno-missing-field-initializers' '-fmessage-length=0' '-fno-exceptions' '-fno-builtin' '-ffunction-sections' '-fdata-sections' '-funsigned-char' '-MMD' '-fno-delete-null-pointer-checks' '-fomit-frame-pointer' '-O3' '-g1' '-DMBED_RTOS_SINGLE_THREAD' '-mcpu=cortex-m0plus' '-mthumb' '-fstrict-aliasing'
LD      = 'arm-none-eabi-gcc' '-fstrict-aliasing'
ELF2BIN = 'arm-none-eabi-objcopy'
PREPROC = 'arm-none-eabi-cpp' '-E' '-P' '-Wl,--gc-sections' '-Wl,--wrap,main' '-Wl,--wrap,_malloc_r' '-Wl,--wrap,_free_r' '-Wl,--wrap,_realloc_r' '-Wl,--wrap,_memalign_r' '-Wl,--wrap,_calloc_r' '-Wl,--wrap,exit' '-Wl,--wrap,atexit' '-Wl,-n' '--specs=nano.specs' '-mcpu=cortex-m0plus' '-mthumb'

C_FLAGS += -std=gnu99
C_FLAGS += -O3
C_FLAGS += -DTARGET_LPC11U68
C_FLAGS += -D__MBED__=1
C_FLAGS += -DDEVICE_I2CSLAVE=1
C_FLAGS += -DTARGET_LIKE_MBED
C_FLAGS += -DTARGET_NXP
C_FLAGS += -D__MBED_CMSIS_RTOS_CM
C_FLAGS += -DDEVICE_RTC=1
C_FLAGS += -DTOOLCHAIN_object
C_FLAGS += -D__CMSIS_RTOS
C_FLAGS += -DTOOLCHAIN_GCC
C_FLAGS += -DTARGET_CORTEX_M
C_FLAGS += -DTARGET_M0P
C_FLAGS += -DTARGET_UVISOR_UNSUPPORTED
C_FLAGS += -DDEVICE_SERIAL=1
C_FLAGS += -DDEVICE_INTERRUPTIN=1
C_FLAGS += -DTARGET_LPCTarget
C_FLAGS += -DTARGET_CORTEX
C_FLAGS += -DDEVICE_I2C=1
C_FLAGS += -D__CORTEX_M0PLUS
C_FLAGS += -DTARGET_FF_ARDUINO
C_FLAGS += -DTARGET_RELEASE
C_FLAGS += -DMBED_BUILD_TIMESTAMP=1526394586.66
C_FLAGS += -DARM_MATH_CM0PLUS
C_FLAGS += -DTARGET_LPC11U6X
C_FLAGS += -DDEVICE_SLEEP=1
C_FLAGS += -DTOOLCHAIN_GCC_ARM
C_FLAGS += -DDEVICE_SPI=1
C_FLAGS += -DDEVICE_ANALOGIN=1
C_FLAGS += -DDEVICE_PWMOUT=1
C_FLAGS += -DTARGET_LIKE_CORTEX_M0

CXX_FLAGS += -std=c++17
CXX_FLAGS += -O3
CXX_FLAGS += -fno-rtti
CXX_FLAGS += -Wvla
CXX_FLAGS += -DTARGET_LPC11U68
CXX_FLAGS += -D__MBED__=1
CXX_FLAGS += -DDEVICE_I2CSLAVE=1
CXX_FLAGS += -DTARGET_LIKE_MBED
CXX_FLAGS += -DTARGET_NXP
CXX_FLAGS += -D__MBED_CMSIS_RTOS_CM
CXX_FLAGS += -DDEVICE_RTC=1
CXX_FLAGS += -DTOOLCHAIN_object
CXX_FLAGS += -D__CMSIS_RTOS
CXX_FLAGS += -DTOOLCHAIN_GCC
CXX_FLAGS += -DTARGET_CORTEX_M
CXX_FLAGS += -DTARGET_M0P
CXX_FLAGS += -DTARGET_UVISOR_UNSUPPORTED
CXX_FLAGS += -DDEVICE_SERIAL=1
CXX_FLAGS += -DDEVICE_INTERRUPTIN=1
CXX_FLAGS += -DTARGET_LPCTarget
CXX_FLAGS += -DTARGET_CORTEX
CXX_FLAGS += -DDEVICE_I2C=1
CXX_FLAGS += -D__CORTEX_M0PLUS
CXX_FLAGS += -DTARGET_FF_ARDUINO
CXX_FLAGS += -DTARGET_RELEASE
CXX_FLAGS += -DMBED_BUILD_TIMESTAMP=1526394586.66
CXX_FLAGS += -DARM_MATH_CM0PLUS
CXX_FLAGS += -DTARGET_LPC11U6X
CXX_FLAGS += -DDEVICE_SLEEP=1
CXX_FLAGS += -DTOOLCHAIN_GCC_ARM
CXX_FLAGS += -DDEVICE_SPI=1
CXX_FLAGS += -DDEVICE_ANALOGIN=1
CXX_FLAGS += -DDEVICE_PWMOUT=1
CXX_FLAGS += -DTARGET_LIKE_CORTEX_M0

ASM_FLAGS += -x
ASM_FLAGS += assembler-with-cpp
ASM_FLAGS += -D__CMSIS_RTOS
ASM_FLAGS += -D__MBED_CMSIS_RTOS_CM
ASM_FLAGS += -D__CORTEX_M0PLUS
ASM_FLAGS += -DARM_MATH_CM0PLUS
ASM_FLAGS += -I../.
ASM_FLAGS += -I$(POKITTO_LIB_PATH)
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/POKITTO_CORE
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/POKITTO_CORE/FONTS
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/POKITTO_CORE/PALETTES
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/POKITTO_HW
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/POKITTO_LIBS
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/POKITTO_LIBS/ImageFormat
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/POKITTO_LIBS/Synth
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/POKITTO_LIBS/Tilemap
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/POKITTO_XTERNALS
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/POKITTO_XTERNALS/Arduino
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/libpff
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/mbed-pokitto
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/api
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/common
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/hal
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/cmsis
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/cmsis/TARGET_NXP
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/cmsis/TARGET_NXP/TARGET_LPC11U6X
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/cmsis/TARGET_NXP/TARGET_LPC11U6X/TOOLCHAIN_GCC_ARM
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/cmsis/TARGET_NXP/TARGET_LPC11U6X/TOOLCHAIN_GCC_ARM/TARGET_LPC11U68
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/cmsis/TOOLCHAIN_GCC
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal/TARGET_NXP
ASM_FLAGS += -I$(POKITTO_LIB_PATH)/mbed-pokitto/targets/hal/TARGET_NXP/TARGET_LPC11U6X

LD_FLAGS :=-Wl,--gc-sections -Wl,--wrap,main -Wl,--wrap,_memalign_r -Wl,-n --specs=nano.specs -mcpu=cortex-m0plus -mthumb -Wl,-Map=map.txt
LD_SYS_LIBS :=-Wl,--start-group -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys  -Wl,--end-group

# Tools and Flags
###############################################################################
# Rules

.PHONY: all lst size

all: $(PROJECT).bin $(PROJECT).hex size

.s.o:
	+@$(call MAKEDIR,$(dir $@))
	+@echo "Assemble: $(notdir $<)"
  
	@$(AS) -c $(ASM_FLAGS) -o $@ $<
  
.S.o:
	+@$(call MAKEDIR,$(dir $@))
	+@echo "Assemble: $(notdir $<)"
  
	@$(AS) -c $(ASM_FLAGS) -o $@ $<
 
.c.o:
	+@$(call MAKEDIR,$(dir $@))
	+@echo "Compile: $(notdir $<)"
	@$(CC) $(C_FLAGS) $(INCLUDE_PATHS) -o $@ $<

.cpp.o:
	+@$(call MAKEDIR,$(dir $@))
	+@echo "Compile: $(notdir $<)"
	@$(CPP) $(CXX_FLAGS) $(INCLUDE_PATHS) -o $@ $<

$(PROJECT).link_script.ld: $(LINKER_SCRIPT)
	@$(PREPROC) $< -o $@

$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS) $(PROJECT).link_script.ld 
	+@echo "link: $(notdir $@)"
	@$(LD) $(LD_FLAGS) -T $(filter-out %.o, $^) $(LIBRARY_PATHS) --output $@ $(filter %.o, $^) $(LIBRARIES) $(LD_SYS_LIBS)

$(PROJECT).bin: $(PROJECT).elf
	$(ELF2BIN) -O binary $< $@
	+@echo "===== bin file ready to flash: $(OBJDIR)/$@ =====" 

$(PROJECT).hex: $(PROJECT).elf
	$(ELF2BIN) -O ihex $< $@

# Rules
###############################################################################
# Dependencies

DEPS = $(OBJECTS:.o=.d) $(SYS_OBJECTS:.o=.d)
-include $(DEPS)
endif

# Dependencies
###############################################################################

