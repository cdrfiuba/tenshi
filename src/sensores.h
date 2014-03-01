#ifndef _SENSORES_H_
#define _SENSORES_H_

#include <avr/io.h>
#include "definiciones.h"

/* Sensores Superiores */
/*EMI = Emisor*/
#define PORT_EMI_NAME B
#define EMI_NUMBER    7

/*RFI = Receptor Frontal Izquierdo*/
#define PORT_RA_NAME D
#define RA_NUMBER    2

/*RFD = Receptor Frontal Derecho*/
#define PORT_RB_NAME D
#define RB_NUMBER    3

/*RTI = Receptor Trasero Izquierdo*/
#define PORT_RC_NAME D
#define RC_NUMBER    4

/*RTD = Receptor Trasero Derecho*/
#define PORT_RD_NAME D
#define RD_NUMBER    5

#define PORT_EMI  def_port_reg(PORT_EMI_NAME)
#define PIN_EMI   def_pin_reg(PORT_EMI_NAME)
#define DDR_EMI   def_ddr_reg(PORT_EMI_NAME)

#define PORT_RA  def_port_reg(PORT_RA_NAME)
#define PIN_RA   def_pin_reg(PORT_RA_NAME)
#define DDR_RA   def_ddr_reg(PORT_RA_NAME)

#define PORT_RB  def_port_reg(PORT_RB_NAME)
#define PIN_RB   def_pin_reg(PORT_RB_NAME)
#define DDR_RB   def_ddr_reg(PORT_RB_NAME)

#define PORT_RC  def_port_reg(PORT_RC_NAME)
#define PIN_RC   def_pin_reg(PORT_RC_NAME)
#define DDR_RC   def_ddr_reg(PORT_RC_NAME)

#define PORT_RD  def_port_reg(PORT_RD_NAME)
#define PIN_RD   def_pin_reg(PORT_RD_NAME)
#define DDR_RD   def_ddr_reg(PORT_RD_NAME)

// el período de la salida del emisor son 215 ciclos de reloj
// ( 8 MHz / 38 KHz)
#define OCR_EMISOR_TIEMPO_EN_ALTO		    107
#define OCR_EMISOR_TIEMPO_EN_BAJO		    108

#define TIMER_ON (0<<CS22)|(0<<CS21)|(1<<CS20)
#define TIMER_OFF (0<<CS22)|(0<<CS21)|(0<<CS20)


void configurarPinSensoresSup();
void configurarTimerSensoresSup();

void encenderEmisorSuperior();
void apagarEmisorSuperior();

#endif
