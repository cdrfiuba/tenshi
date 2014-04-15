#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "motores.h"
#include "sensores.h"
#include "tenshi.h"

volatile estados estadoActual;

int main () {
    setup();

    while (estadoActual == DETENIDO);
    while (1) {
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
