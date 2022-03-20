#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

TARGET := z80
PROJECT_NAME := z80_Computer

# define the C compiler to use
CC := sdcc
AS := sdasz80
# define any compile-time flags
#
CFLAGS	:= --no-std-crt0 --debug -m$(TARGET) --vc


# define source directory
SRC       	:= src
BUILD 		:= build
OUTPUT		:= output
INCLUDE		:= include
LIB			:= lib
CRT		:= crt

#Command Alias
MKDIR		:= cmd /c mkdir

#ASM       	:= $(powershell find src/ -type f -name '*.asm')
#LIBC_PATH 	:= $(subst \,/,$(powershell sdcc -m$(TARGET) --print-search-dirs | where Path -contains $(TARGET) | tail -n 1))/../src
#REL		:= $(patsubst %, $(BUILD)/%.o, $(ASM) $(SRC)) $(patsubst %, $(BUILD)/libc/%.o, $(LIBC))

# define include directory

# define lib directory

# define any directories containing header files other than /usr/include
#INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

# define the C libs
#LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

# define the C source files
#SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))

# define the C object files 
#OBJECTS		:= $(SOURCES:.c=.o)

all: clean create_dirs $(OUTPUT)/$(PROJECT_NAME).bin
	@echo Executing 'all' complete!


$(BUILD)/%.rel : $(SRC)/%.c
	@echo Compiling $<
	$(CC)  -o $(dir $@) -c $(CFLAGS) $<

$(CRT)/crt0.rel : $(CRT)/crt0.s
	@echo Assembling $<
	@$(AS) -xlos -y -g $<


# $(OUTPUT)/$(PROJECT_NAME).bin: $(INCLUDE)/crt0.rel $(BUILD)/main.rel
# 	@$(CC) $(CFLAGS) -o $(BUILD) $^
	
#	@./hex2bin.exe -e .bin -c $<

#To make the intel hex file, we need to link the main.c & crt0.rel
$(BUILD)/main.ihx: $(CRT)/crt0.rel  $(BUILD)/main.rel $(BUILD)/lcd.rel $(BUILD)/sd.rel 
	@echo Linking $^
#	@sdld -i $@ $^
	@$(CC) -o $@ $(CFLAGS) --data-loc 0xA000 --stack-loc 0xAFFF $^ z80.lib -L 'C:\Program Files\SDCC\lib\z80\z80.lib'
	

# To make the .bin, we need to pack the .ihx file
$(OUTPUT)/$(PROJECT_NAME).bin: $(BUILD)/main.ihx
	@echo Creating final $@
#	hex2bin.exe $<
	sdobjcopy -I ihex -O binary $< $@

create_dirs:
	@echo Making Directories
	@if not exist $(BUILD) mkdir $(BUILD)
	@if not exist $(OUTPUT) mkdir $(OUTPUT)

upload:
	python.exe '.\\Arduino EEPROM Programmer\\eeprom.py' --port COM12 load -f '$(OUTPUT)/$(PROJECT_NAME).bin'

.PHONY: clean
clean:
	@if exist $(BUILD) del /Q /F $(BUILD)
	@del /Q /F $(CRT)\\crt0.rel
	@del /Q /F $(CRT)\\crt0.lst
	@del /Q /F $(CRT)\\crt0.sym
	@echo Cleanup complete!

#get the main.ihx from main.c & crt0.rel
#
#
#
#