GCC_BIN = /Users/user/Documents/arm-none-eabi-gcc/bin/
OBJDIR = Builds
SOURCES = $(shell find -E . -regex '^.*\.(c(pp)?|[sS])$$' | sed -E -e 's/\.(c(pp)?|[sS])$$/.o/g')
OBJECTS = $(patsubst %,$(OBJDIR)/%,$(filter-out $(PROJECT).o,$(SOURCES)))
SYS_OBJECTS = $(shell find -E . -regex '^.*\.o$$' | sed -e 's/^.\/Builds\/.*$$//g')
INCLUDE_PATHS = -I. $(shell find -E . -regex '^.*\.h$$' | sed -e 's/^\(.*\)\/[^\/]*$$/-I\1/g' | sort | uniq)
LIBRARY_PATHS = $(shell find -E . -regex '^.*\.a$$' | sed -e 's/^\(.*\)\/[^\/]*$$/-L\1/g' | sort | uniq)
LIBRARIES = -lmbed
LINKER_SCRIPT = $(shell find -E . -regex '^.*\.ld$$')

###############################################################################
AS      = $(GCC_BIN)arm-none-eabi-as
CC      = $(GCC_BIN)arm-none-eabi-gcc
CPP     = $(GCC_BIN)arm-none-eabi-g++
LD      = $(GCC_BIN)arm-none-eabi-gcc
OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy
OBJDUMP = $(GCC_BIN)arm-none-eabi-objdump
SIZE 	= $(GCC_BIN)arm-none-eabi-size

CPU = -mcpu=cortex-m3 -mthumb
CC_FLAGS = $(CPU) -c -g -fno-common -fmessage-length=0 -Wall -Wextra -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -MMD -MP
CC_SYMBOLS = -DTOOLCHAIN_GCC_ARM -DTOOLCHAIN_GCC -DARM_MATH_CM3 -DTARGET_CORTEX_M -DMBED_BUILD_TIMESTAMP=1445859779.29 -DTARGET_LPC176X -DTARGET_NXP -DTARGET_MBED_LPC1768 -DTARGET_LPC1768 -D__CORTEX_M3 -DTARGET_M3 -D__MBED__=1

LD_FLAGS = $(CPU) -Wl,--gc-sections --specs=nano.specs -u _printf_float -u _scanf_float -Wl,--wrap,main -Wl,-Map=Builds/$(PROJECT).map,--cref
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys

CXX_FLAGS =
#CXX_FLAGS += -Wextra -Weffc++ -Wno-non-virtual-dtor -Wcast-align -Wundef -Wmissing-include-dirs -Wunused-macros -Wmissing-noreturn -Wmissing-format-attribute -Wcast-qual -Wunused -Wdisabled-optimization -Wfloat-equal -Wold-style-cast -Winline -Winit-self -Wformat-nonliteral -Wunsafe-loop-optimizations -Wunreachable-code -Wformat-security -Wlogical-op -Wformat -Woverloaded-virtual

ifeq ($(HARDFP),1)
	FLOAT_ABI = hard
else
	FLOAT_ABI = softfp
endif

ifeq ($(DEBUG), 1)
  CC_FLAGS += -DDEBUG -O0
else
  CC_FLAGS += -DNDEBUG -Os
endif

createObjDir:
	@if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi

all: clean build upload

build: createObjDir $(OBJDIR)/$(PROJECT).bin

upload:
	@echo "Upload"
	@if [ ! -d /Volumes/MBED ]; then echo Connect Mbed; exit 1; fi
	cp $(OBJDIR)/$(PROJECT).bin /Volumes/MBED

buildAndUpload: build upload

clean:
	@if [ -d $(OBJDIR) ]; then rm -rf $(OBJDIR); fi

$(OBJDIR)/%.o: 	%.s
	@echo "Assemble $<"
	@mkdir -p $(dir $@)
	$(AS) $(CPU) -o $@ $<

$(OBJDIR)/%.o: 	%.S
	@echo "Assemble $<"
	@mkdir -p $(dir $@)
	$(AS) $(CPU) -o $@ $<

$(OBJDIR)/%.o: 	%.c
	@echo "Compile $<"
	@mkdir -p $(dir $@)
	$(CC)  $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu99 $(INCLUDE_PATHS) -o $@ $<

$(OBJDIR)/%.d: %.c
	@echo "Generate dependency of $<"
	@mkdir -p $(dir $@)
	$(CC) -MM $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu99 $(INCLUDE_PATHS) $< -MF $@ -MT $(@:.d=.o)

$(OBJDIR)/%.o: 	%.cpp
	@echo "Compile $<"
	@mkdir -p $(dir $@)
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) $(CXX_FLAGS) -std=gnu++14 -fno-rtti $(INCLUDE_PATHS) -o $@ $<

$(OBJDIR)/%.d: %.cpp
	@echo "Generate dependency of $<"
	@mkdir -p $(dir $@)
	$(CPP) -MM $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++14 -fno-rtti $(INCLUDE_PATHS) $< -MF $@ -MT $(@:.d=.o)

$(OBJDIR)/$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS)
	@echo Link
	$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $^ $(LIBRARIES) $(LD_SYS_LIBS) $(LIBRARIES) $(LD_SYS_LIBS)
	$(SIZE) $@

$(OBJDIR)/$(PROJECT).bin: $(OBJDIR)/$(PROJECT).elf
	@echo Copy
	$(OBJCOPY) -O binary $< $@
