#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "motores.h"
#include "sensores.h"
#include "tenshi.h"

volatile estados estadoActual;

void setup();
void configurarPulsador(void);
void bajarPollera();

int main (void) {
  setup();

  while (estadoActual == DETENIDO);
  while(1){
    motoresAvanzar();
    _delay_ms(250);
    motoresRetroceder();
    _delay_ms(250);
    motoresGirarDerecha();
    _delay_ms(250);
    motoresGirarIzquierda();
    _delay_ms(250);
  }
}

void setup() {
	LedDInit(); 
	LedCInit(); 
	LedBInit(); 
	LedAInit(); 
	configurarPulsador();
	configurarMotores();
	//  configurarPinSensoresSup();
	//  configurarTimerSensoresSup();
	//  configurarMotorPolleras();
	estadoActual = DETENIDO;
	sei();
}

void configurarPulsador(void){
	PulsadorInit();
	// Configuro el pin change
	PCICR |= (1 << PCIE0);
	PCMSK0 = (1 << PCINT0);
}

ISR(PCINT0_vect) {
	// Delay para debounce
	// Dado que no tenemos necesidad de hacer nada mientras esperamos por el
	// debounce lo dejamos asi. Sino, deberiamos utilizar algun timer
	_delay_ms(50);

	if (IsPulsadorSet()==true) { 
		// significa que esta en 1 y hubo flanco ascendente genuino
		// se podria reemplazar la variable por poner apagar todo, poner 
		// el micro a dormir esperando solo esta interrupcion y luego
		// despertalo. Aca se lo despertaria
//    encenderMotores();
    encenderEmisorSuperior();
    estadoActual = TRACKING;
	}

  // Este flag se clerea a mano porque el clear por hardware se realiza en el
  // momento que se atiende la interrupcion y no cuando se sale de ella.
  // Esto hace que mientras se esta dentro de la interrupcion, puedan generarse
  // nuevos flancos (ruido) que no queremos atender
  SetBit(EIFR, INTF0);
}


void bajarPollera() {
  unsigned char aux = 10;
  while(aux>0) {
    SetBit(PORT_SERVO, SERVO_NUMBER);
    _delay_ms(1);
    ClearBit(PORT_SERVO, SERVO_NUMBER);
    _delay_ms(19);
    aux--;
  }
}
