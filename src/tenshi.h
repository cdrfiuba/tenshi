#ifndef _MJOLNIR_H_
#define _MJOLNIR_H_

#include <avr/io.h>
#include "definiciones.h"

/* Definiciones correspondientes a los pines de los LEDs */

/*LEDD = LED D Atras Derecha*/
#define PORT_LEDD_NAME	C
#define LEDD_NUMBER	    2

/*LEDC = LED C Atras Izquierda*/
#define PORT_LEDC_NAME	C
#define LEDC_NUMBER	    3

/*LEDB = LED B Adelante Derecha*/
#define PORT_LEDB_NAME	C
#define LEDB_NUMBER	    1

/*LEDA = LED A  Adelante Izquierda*/
#define PORT_LEDA_NAME	C
#define LEDA_NUMBER	    0

#define PORT_LEDD     def_port_reg(PORT_LEDD_NAME)
#define PIN_LEDD      def_pin_reg(PORT_LEDD_NAME)
#define DDR_LEDD      def_ddr_reg(PORT_LEDD_NAME)

#define PORT_LEDC	def_port_reg(PORT_LEDC_NAME)
#define PIN_LEDC	def_pin_reg(PORT_LEDC_NAME)
#define DDR_LEDC	def_ddr_reg(PORT_LEDC_NAME)

#define PORT_LEDB	def_port_reg(PORT_LEDB_NAME)
#define PIN_LEDB	def_pin_reg(PORT_LEDB_NAME)
#define DDR_LEDB	def_ddr_reg(PORT_LEDB_NAME)

#define PORT_LEDA	def_port_reg(PORT_LEDA_NAME)
#define PIN_LEDA	def_pin_reg(PORT_LEDA_NAME)
#define DDR_LEDA	def_ddr_reg(PORT_LEDA_NAME)



#define LedDOff()    SetBit(PORT_LEDD, LEDD_NUMBER)
#define LedDOn()   ClearBit(PORT_LEDD, LEDD_NUMBER)

#define IsLedDOn()    IsBitSet(PORT_LEDD, LEDD_NUMBER)
#define LedDToggle()  SetBit(PIN_LEDD, LEDD_NUMBER)

#define LedCOff()    SetBit(PORT_LEDC, LEDC_NUMBER)
#define LedCOn()   ClearBit(PORT_LEDC, LEDC_NUMBER)

#define IsLedCOn()    IsBitSet(PORT_LEDC, LEDC_NUMBER)
#define LedCToggle()  SetBit(PIN_LEDC, LEDC_NUMBER)

#define LedBOff()    SetBit(PORT_LEDB, LEDB_NUMBER)
#define LedBOn()   ClearBit(PORT_LEDB, LEDB_NUMBER)

#define IsLedBOn()    IsBitSet(PORT_LEDB, LEDB_NUMBER)
#define LedBToggle()  SetBit(PIN_LEDB, LEDB_NUMBER)

#define LedAOff()    SetBit(PORT_LEDA, LEDA_NUMBER)
#define LedAOn()   ClearBit(PORT_LEDA, LEDA_NUMBER)

#define IsLedAOn()    IsBitSet(PORT_LEDA, LEDA_NUMBER)
#define LedAToggle()  SetBit(PIN_LEDA, LEDA_NUMBER)


#define LedDInit()  {SetBit(DDR_LEDD, LEDD_NUMBER);LedDOff();}
#define LedCInit()  {SetBit(DDR_LEDC, LEDC_NUMBER);LedCOff();}
#define LedBInit()  {SetBit(DDR_LEDB, LEDB_NUMBER);LedBOff();}
#define LedAInit()  {SetBit(DDR_LEDA, LEDA_NUMBER);LedAOff();}



/* INT_ARRANQUE = Pulsador de Arranque */
#define PORT_PULSADOR_NAME   B
#define PULSADOR_NUMBER      0

#define PORT_PULSADOR  def_port_reg(PORT_PULSADOR_NAME)
#define PIN_PULSADOR   def_pin_reg(PORT_PULSADOR_NAME)
#define DDR_PULSADOR   def_ddr_reg(PORT_PULSADOR_NAME)


/* Macros */
// Se setea como entrada y se pone el pin en '1'. Esto último hace que se 
// active el pull-up interno
#define PulsadorInit()  {ClearBit(DDR_PULSADOR, PULSADOR_NUMBER); SetBit(PORT_PULSADOR, PULSADOR_NUMBER);}

// lee el pin del boton de arranque
#define IsPulsadorSet()   IsBitSet(PIN_PULSADOR, PULSADOR_NUMBER)


typedef enum {
	FIGHT_ADELANTE,
  FIGHT_ATRAS,
	TRACKING,
	DETENIDO
} estados;


#endif
