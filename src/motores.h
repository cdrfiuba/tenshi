#ifndef _MOTORES_H_
#define _MOTORES_H_

#include <avr/io.h>
#include "definiciones.h"

/* Definiciones de los pines correspondientes a los motores */

/*MD_PWM = Motor Derecho (A) Enable (Enable)*/
#define PORT_MD_EN_NAME  B
#define MD_EN_NUMBER     1
/*MI_WPM = Motor Izquierdo PWM (Enable)*/
#define PORT_MI_EN_NAME  B
#define MI_EN_NUMBER     2

#define PORT_MD_EN     def_port_reg(PORT_MD_EN_NAME)
#define PIN_MD_EN      def_pin_reg(PORT_MD_EN_NAME)
#define DDR_MD_EN      def_ddr_reg(PORT_MD_EN_NAME)

#define PORT_MI_EN     def_port_reg(PORT_MI_EN_NAME)
#define PIN_MI_EN      def_pin_reg(PORT_MI_EN_NAME)
#define DDR_MI_EN      def_ddr_reg(PORT_MI_EN_NAME)


/*MI_IN1 = Motor Izquierdo IN1*/
#define PORT_MI_IN1_NAME  C
#define MI_IN1_NUMBER     4
/*MI_IN2 = Motor Izquierdo IN2*/
#define PORT_MI_IN2_NAME	 C
#define MI_IN2_NUMBER		   5

/*MD_IN1 = Motor Derecho IN1*/
#define PORT_MD_IN1_NAME  D
#define MD_IN1_NUMBER     0
/*MD_IN2 = Motor Right IN2*/
#define PORT_MD_IN2_NAME  D
#define MD_IN2_NUMBER     1

#define PORT_MD_IN1     def_port_reg(PORT_MD_IN1_NAME)
#define PIN_MD_IN1      def_pin_reg(PORT_MD_IN1_NAME)
#define DDR_MD_IN1      def_ddr_reg(PORT_MD_IN1_NAME)

#define PORT_MD_IN2     def_port_reg(PORT_MD_IN2_NAME)
#define PIN_MD_IN2      def_pin_reg(PORT_MD_IN2_NAME)
#define DDR_MD_IN2      def_ddr_reg(PORT_MD_IN2_NAME)

#define PORT_MI_IN1     def_port_reg(PORT_MI_IN1_NAME)
#define PIN_MI_IN1      def_pin_reg(PORT_MI_IN1_NAME)
#define DDR_MI_IN1      def_ddr_reg(PORT_MI_IN1_NAME)

#define PORT_MI_IN2     def_port_reg(PORT_MI_IN2_NAME)
#define PIN_MI_IN2      def_pin_reg(PORT_MI_IN2_NAME)
#define DDR_MI_IN2      def_ddr_reg(PORT_MI_IN2_NAME)

/* Servo Motor*/
#define PORT_SERVO_NAME  B
#define SERVO_NUMBER     6

#define PORT_SERVO     def_port_reg(PORT_SERVO_NAME)
#define PIN_SERVO      def_pin_reg(PORT_SERVO_NAME)
#define DDR_SERVO      def_ddr_reg(PORT_SERVO_NAME)


/* Macros */
#define apagarMotores() {ClearBit(PORT_MD_EN, MD_EN_NUMBER);ClearBit(PORT_MI_EN, MI_EN_NUMBER);}
#define encenderMotores() {SetBit(PORT_MD_EN, MD_EN_NUMBER);SetBit(PORT_MI_EN, MI_EN_NUMBER);}

/*-----------------------------------------------*/

void motoresApagar(void);
void motoresEncender(void);
void configurarMotores(void);

void motoresAvanzar();
void motoresRetroceder();
void motoresGirarIzquierda();
void motoresGirarDerecha();

void configurarMotorPolleras();
#endif
