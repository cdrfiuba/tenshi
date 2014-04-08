CLK = 8000000UL

# TARGET es el nombre del proyecto
TARGET = tenshi

# MMCU es el microcontralador para el target para el avr-gcc
# Para ver el listado de posibles opciones ir a:
#      http://avr-libc.nongnu.org/user-manual/index.html
MMCU = atmega88

# TARGET_P es el microcontrolador para el target del programador
# Para el Atemga88: m88
# Para ver el listado de posibles opciones hacer:
#      avrdude -p ?
TARGET_P = m88

# HFUSE 
# Para el Atmega88 (pagina 299)
# 0xDF es el default
# 0xD7 para no borrar la eeprom con cada repgramado
HFUSE = 0xDF

# LFUSE
# Para el Atemega88 (pagina 301)
# 0x62 es el default, con clk_div = 8
# 0xE2 es el default  sin clk_div
LFUSE = 0xE2

# SRC contiene el nombre de todos los .c existentes en el directorio actual
SRC = tenshi.c motores.c sensores.c
# INC contiene el nombre de todos los .h existentes en el directorio actual
INC = tenshi.h motores.h sensores.h definiciones.h 

# gcc manual: http://gcc.gnu.org/onlinedocs/gcc/
# -Os: [gcc manual] Optimize for size. -Os enables all -O2 optimizations that do not typically increase code size. It also performs further optimizations designed to reduce code size. 
# -Wall -Wextra: a lot of warnings.
# -funsafe-loop-optimizations -Wunsafe-loop-optimizations: optimize out-of-bounds loops by removing check, but do the check at compile time.
# -mcall-prologues: [gcc manual] Functions prologues/epilogues are expanded as calls to appropriate subroutines. Code size is smaller.
# -std=gnu99: uses the extended C 99 standard. See http://gcc.gnu.org/onlinedocs/gcc/Standards.html
# -mrelax: [gcc manual] Try to replace CALL resp. JMP instruction by the shorter RCALL resp. RJMP instruction if applicable.
CFLAGS = -Os -Wall -Wextra -funsafe-loop-optimizations -Wunsafe-loop-optimizations -mcall-prologues -std=gnu99 -mrelax

CDEFINES = -DF_CPU=$(CLK)

all: hex

hex: $(SRC) $(INC)
	avr-gcc $(CFLAGS) $(CDEFINES) -mmcu=$(MMCU) -o $(TARGET).bin -I/usr/avr/include/ $(SRC)
	avr-objcopy -j .text -O ihex  $(TARGET).bin $(TARGET).hex
	avr-objdump -h -S $(TARGET).bin > "$(TARGET).lst"
	avr-size $(TARGET).bin

program: hex
	avrdude -F -c usbtiny -p $(TARGET_P) -U flash:w:$(TARGET).hex:i

fuses_write:
	avrdude -c usbtiny -p $(TARGET_P) -U hfuse:w:$(HFUSE):m
	avrdude -c usbtiny -p $(TARGET_P) -U lfuse:w:$(LFUSE):m

fuses_read:
	@ avrdude -c usbtiny -p $(TARGET_P) -U hfuse:r:hfuse.hex:h
	@ avrdude -c usbtiny -p $(TARGET_P) -U lfuse:r:lfuse.hex:h
#	@ avrdude -c usbtiny -p $(TARGET_P) -U efuse:r:efuse.hex:h
	@ echo "HFuse = "
	@ cat hfuse.hex
	@ echo "LFuse = " 
	@ cat lfuse.hex
#	@ echo "EFuse = "
#	@ cat efuse.hex

clean:
	rm -rf $(TARGET).hex $(TARGET).bin $(TARGET).s $(TARGET).lst hfuse.hex lfuse.hex efuse.hex eeprom.hex

editgvim:
	gvim -p $(SRC) $(INC) Makefile

eeprom_read:
	avrdude -c usbtiny -p $(TARGET_P) -U eeprom:r:eeprom.hex:r

eeprom_write:
	avrdude -c usbtiny -p $(TARGET_P) -U eeprom:w:eeprom.hex:r

