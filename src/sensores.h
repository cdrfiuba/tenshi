#ifndef _SENSORES_H_
#define _SENSORES_H_

#include <avr/io.h>
#include "definiciones.h"

/* Sensores Superiores */
/*EMI = Emisor*/
#define PORT_EMI_NAME B
#define EMI_NUMBER    7

/*RFI = Receptor Frontal Izquierdo*/
#define PORT_RA_NAME  D
#define RA_NUMBER     3

/*RFD = Receptor Frontal Derecho*/
#define PORT_RB_NAME  D
#define RB_NUMBER     5

/*RTI = Receptor Trasero Izquierdo*/
#define PORT_RC_NAME  D
#define RC_NUMBER     4

/*RTD = Receptor Trasero Derecho*/
#define PORT_RD_NAME  D
#define RD_NUMBER     2

#define PORT_EMI  def_port_reg(PORT_EMI_NAME)
#define PIN_EMI   def_pin_reg(PORT_EMI_NAME)
#define DDR_EMI   def_ddr_reg(PORT_EMI_NAME)

#define PORT_RA   def_port_reg(PORT_RA_NAME)
#define PIN_RA    def_pin_reg(PORT_RA_NAME)
#define DDR_RA    def_ddr_reg(PORT_RA_NAME)

#define PORT_RB   def_port_reg(PORT_RB_NAME)
#define PIN_RB    def_pin_reg(PORT_RB_NAME)
#define DDR_RB    def_ddr_reg(PORT_RB_NAME)

#define PORT_RC   def_port_reg(PORT_RC_NAME)
#define PIN_RC    def_pin_reg(PORT_RC_NAME)
#define DDR_RC    def_ddr_reg(PORT_RC_NAME)

#define PORT_RD   def_port_reg(PORT_RD_NAME)
#define PIN_RD    def_pin_reg(PORT_RD_NAME)
#define DDR_RD    def_ddr_reg(PORT_RD_NAME)

// ( 8 MHz / 38 KHz) = 210.5263 => 210 / 2 = 105
#define OCR_EMISOR_TIEMPO_CICLOS            105
// 1 / 38095 Hz * 1000 * 1000 = 26,25 us ==> 23 interrupciones son 603,75 us
#define CANTIDAD_DE_INTERRUPCIONES_EMISORES_SUPERIORES          23

// Como usamos el timer del emisor, contar 200 interrupciones implica
// contar 5,25 ms. Contamos en los posibles flancos altos del emisor, y en 
// el mismo intervalo durante el modo cero.
#define CANTIDAD_DE_INTERRUPCIONES_EMISORES_RECEPTORES         184 // deberia ser (N*2*CANTIDAD_DE_INTERRUPCIONES_EMISORES_SUPERIORES), de manera que sea un numero entero de ciclos completos de la interrupcion. dado que es 23 en este momento la cantidad de interrupciones, yo usaria N=4 o 5, dando esta cuenta 184 o 230, dependiendo cual se elija).

#define TIMER_ON       (0 << CS22) | (0 << CS21) | (1 << CS20)
#define TIMER_OFF      (0 << CS22) | (0 << CS21) | (0 << CS20)
#define TIMER_OFF_MASK (1 << CS22) | (1 << CS21) | (1 << CS20)

#define EsActivoReceptorA()   !IsBitSet(PIN_RA, RA_NUMBER)
#define EsActivoReceptorB()   !IsBitSet(PIN_RB, RB_NUMBER)
#define EsActivoReceptorC()   !IsBitSet(PIN_RC, RC_NUMBER)
#define EsActivoReceptorD()   !IsBitSet(PIN_RD, RD_NUMBER)


void configurarSensoresSuperiores();

void encenderEmisorSuperior();
void apagarEmisorSuperior();

#endif
