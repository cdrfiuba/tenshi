#ifndef _DEFINICIONES_H_
#define _DEFINICIONES_H_
/* Defines y Macros de proposito general */

#include <stdbool.h>

#define Nop()      asm volatile("nop")
#define Reti()      asm volatile("reti")

#define LOW(a)    (char)(a & 0x00ff)
#define    HIGH(a)   (char)(a >> 8)

#define SetBit(Byte, Bit)     (Byte |= (1 << Bit))
#define    ClearBit(Byte, Bit)     (Byte &= (~(1 << Bit)))
#define IsBitSet(Byte, Bit)     ( (Byte >> Bit) & 0x01)

#define max(a, b)            ( a > b ? a : b )
#define min(a, b)            ( a < b ? a : b )

#define concat(a, b)         a ## b
#define def_port_reg(name)  concat(PORT,name)
#define def_pin_reg(name)   concat(PIN,name)
#define def_ddr_reg(name)   concat(DDR,name)

#endif
