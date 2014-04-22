#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "motores.h"
#include "sensores.h"
#include "tenshi.h"

// sensores
extern volatile uint32_t acumuladorReceptorA;
extern volatile uint32_t acumuladorReceptorB;
extern volatile uint32_t acumuladorReceptorC;
extern volatile uint32_t acumuladorReceptorD;

volatile estados estadoActual;

int main () {
    setup();

    while (estadoActual == DETENIDO);
    while (1) {

        if (acumuladorReceptorD < 20) {
            encenderMotores();
            motoresAvanzar();
        } else if (acumuladorReceptorD >= 20 && acumuladorReceptorD <= 70) {
            apagarMotores();
        } else if (acumuladorReceptorD > 70) {
            encenderMotores();
            motoresRetroceder();
        }

    }
}

void setup() {
    LedDInit(); 
    LedCInit(); 
    LedBInit(); 
    LedAInit(); 
    configurarPulsador();
    configurarMotores();
    configurarSensoresSuperiores();
    configurarMotorPolleras();
    estadoActual = DETENIDO;
    sei();
}

void configurarPulsador(){
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

    if (IsPulsadorSet() == true) { 
        // significa que esta en 1 y hubo flanco ascendente genuino
        // se podria reemplazar la variable por poner apagar todo, poner 
        // el micro a dormir esperando solo esta interrupcion y luego
        // despertalo. Aca se lo despertaria
        //encenderMotores();
        encenderEmisorSuperior();
        estadoActual = TRACKING;
    }

    // Clear de hardware de la interrupción: de esta manera, si se 
    // dispararon nuevas interrupciones entre que se activó la 
    // interrupción actual, con este SetBit se ignoran.
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
