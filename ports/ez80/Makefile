include ../../py/mkenv.mk

INIT_LOC ?= 0

empty :=
space := $(empty) $(empty)
comma := ,

CROSS = 1
CEDEV_TOOLCHAIN ?= $(shell cedev-config --prefix)

ifeq ($(OS),Windows_NT)
SHELL = cmd.exe
NATIVEPATH = $(subst /,\,$1)
QUOTE_ARG = "$(subst ",',$1)"#'
else
NATIVEPATH = $(subst \,/,$1)
QUOTE_ARG = '$(subst ','\'',$1)'#'
endif

FASMG_FILES = $(subst $(space),$(comma) ,$(patsubst %,"%",$(subst ",\",$(subst \,\\,$(call NATIVEPATH,$1)))))#"
LINKER_SCRIPT ?= $(CEDEV_TOOLCHAIN)/meta/linker_script

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h

# MicroPython feature configurations
MICROPY_ROM_TEXT_COMPRESSION ?= 0

# include py core make definitions
include $(TOP)/py/py.mk

CC = ez80-clang
LD = fasmg

INC += -I.
INC += -I$(TOP)
INC += -I$(BUILD)

DFU = $(TOP)/tools/dfu.py
PYDFU = $(TOP)/tools/pydfu.py
CFLAGS += -S -Wall -Werror -std=c99 -Wdouble-promotion -Wfloat-conversion -Oz -nostdlib -nostdinc -isystem $(CEDEV_TOOLCHAIN)/include $(INC)
CFLAGS += -fno-threadsafe-statics -Xclang -fforce-mangle-main-argc-argv -mllvm -profile-guided-section-prefix=false -D_EZ80 -DHAS_PRINTF=1
CFLAGS += $(CFLAGS_MOD)
CXXFLAGS += -fno-exceptions -fno-use-cxa-atexit $(filter-out -std=c99,$(CFLAGS))

LDFLAGS += \
	-n \
	$(call QUOTE_ARG,$(call NATIVEPATH,$(CEDEV_TOOLCHAIN)/meta/ld.alm)) \
	-i $(call QUOTE_ARG,DEBUG := 0) \
	-i $(call QUOTE_ARG,STATIC := 0) \
	-i $(call QUOTE_ARG,include $(call FASMG_FILES,$(LINKER_SCRIPT))) \
	-i $(call QUOTE_ARG,range .bss $$$(BSSHEAP_LOW) : $$$(BSSHEAP_HIGH)) \
	-i $(call QUOTE_ARG,provide __stack = $$$(STACK_HIGH)) \
	-i $(call QUOTE_ARG,locate .header at $$$(INIT_LOC))

# Flags for user C modules
CFLAGS += $(CFLAGS_MOD)
CXXFLAGS += $(CXXFLAGS_MOD)
LDFLAGS += $(LDFLAGS_MOD)

LIBS =

SRC_C = \
	main.c \
	uart_core.c \
	shared/libc/printf.c \
	shared/readline/readline.c \
	shared/runtime/pyexec.c \
	shared/runtime/stdout_helpers.c \
	$(BUILD)/_frozen_mpy.c \

SRC_C += shared/libc/string0.c

SRC_C += $(SRC_MOD)

SRC_CXX += $(SRC_MOD_CXX)

SRC_QSTR += $(SRC_MOD) $(SRC_MOD_CXX)

OBJ += $(PY_CORE_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_CXX:.cpp=.o))

all: $(BUILD)/firmware.bin

$(BUILD)/_frozen_mpy.c: frozentest.mpy $(BUILD)/genhdr/qstrdefs.generated.h
	$(ECHO) "MISC freezing bytecode"
	$(Q)$(TOP)/tools/mpy-tool.py -f -q $(BUILD)/genhdr/qstrdefs.preprocessed.h -mlongint-impl=none $< > $@

$(BUILD)/firmware.bin: $(CEDEV_TOOLCHAIN)/lib/shared/crt0.src $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(LD) $(LDFLAGS) -i $(call QUOTE_ARG,source $(call FASMG_FILES,$^)) $(call NATIVEPATH,$@)

# Disable errors for array-bounds warnings on "sp[-MP_OBJ_ITER_BUF_NSLOTS + *]" access.
$(BUILD)/py/vm.o: CFLAGS += -Wno-error=array-bounds

include $(TOP)/py/mkrules.mk
