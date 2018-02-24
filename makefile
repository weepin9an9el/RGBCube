#
MCU:=atmega328
PROGRAMMER:=usbtiny

CC:=avr-gcc
OC:=avr-objcopy
DUDE:=avrdude

#Add support for floating points 
#Also need the math library (-lm)
#PRINTF_LIB_FLOAT:= -Wl,-u,vfprintf -lm -lprintf_flt

PRINTF_LIB_FLOAT:= 

CC_FLAGS += -c -Os
OC_FLAGS += -O ihex
LD_FLAGS += $(PRINTF_LIB_FLOAT)

#use wildcard expression to include all .c files as part of SRC variable
#SRCS := $(wildcard *.c)
#OBJS := $(SRCS:.c=.o)

.PHONY: all clean

all: main.hex

main.hex: main.elf
	$(OC) -j .text -j .data $(OC_FLAGS) $< $@

main.elf: main.o 
	$(CC) -mmcu=$(MCU) $(LD_FLAGS) -o $@ main.o 

main.o: main.c
	$(CC) $(CC_FLAGS) -mmcu=$(MCU) -o $@ $<

prog: main.hex
	$(DUDE) -p $(MCU) -c $(PROGRAMMER) -e -U flash:w:$<
clean:
	rm *.o *.elf *.hex
