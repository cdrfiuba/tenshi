#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "motores.h"
#include "sensores.h"
#include "tenshi.h"

// sensores

extern volatile uint8_t acumuladorReceptorA_test;
extern volatile uint8_t acumuladorReceptorB_test;
extern volatile uint8_t acumuladorReceptorC_test;
extern volatile uint8_t acumuladorReceptorD_test;

volatile estados estadoActual;

#define MAXIMO_PERMITIDO 90
#define MINIMO_PERMITIDO 10
#define DISTANCIA_RELEVANTE 15
#define DISTANCIA_EXCESIVA 30

typedef enum{
ESPERAR=0,
SEGUIR=1
}modo_t;

/*#define avanzarDerecho() motoresAvanzar()
#define girarAvanzandoDerecha() motoresGirarDerecha()
#define girarAvanzandoIzquierda() motoresGirarIzquierda()
#define girarQuietoDerecha() motoresGirarQuietoDerecha()
#define girarQuietoIzquierda() motoresGirarQuietoIzquierda()
*/

#define avanzarDerecho() {LedAOn();LedBOn();LedCOn();LedDOn();} // Si va a avanzar derecho, prende todos los leds. Si tiene que girar, prende los leds de el lado para el cual doblar.
#define girarAvanzandoDerecha() {LedAOff();LedBOn();LedCOff();LedDOn();}
#define girarAvanzandoIzquierda() {LedAOn();LedBOff();LedCOn();LedDOff();}
#define girarQuietoDerecha() {LedAOff();LedBOn();LedCOff();LedDOff();}
#define girarQuietoIzquierda() {LedAOn();LedBOff();LedCOff();LedDOff();}

int main() {
    setup();
    encenderTodo();

// Codigo de seguimiento
//
// El objetivo del código es 

    modo_t modo;
    uint8_t distanciaMaxima, distanciaMinima;

    while(1){
        distanciaMaxima = max(acumuladorReceptorA_test, acumuladorReceptorB_test);
        distanciaMinima = min(acumuladorReceptorA_test, acumuladorReceptorB_test);

        if( distanciaMaxima > MAXIMO_PERMITIDO || distanciaMinima < MINIMO_PERMITIDO)
            modo = SEGUIR;
        else
            modo = ESPERAR;

        switch (modo){
            case ESPERAR: 
                break;
            case SEGUIR:
                if ((distanciaMaxima - distanciaMinima) < DISTANCIA_RELEVANTE){
                    avanzarDerecho();
                }else if ((distanciaMaxima - distanciaMinima) < DISTANCIA_EXCESIVA) {
                    if (acumuladorReceptorA_test < acumuladorReceptorB_test){
                        girarAvanzandoDerecha();
                    }else{
                        girarAvanzandoIzquierda();
                    }
                }else { 
                    if (acumuladorReceptorA_test < acumuladorReceptorB_test){
                        girarQuietoDerecha();
                    }else{
                        girarQuietoIzquierda();
                    }
                }
        }
    }

// 
// Fin de codigo de seguimiento


    while (estadoActual == DETENIDO);
    
    motoresAvanzar();
    while (1) {

        if (estadoActual == DETENIDO) {
            apagarTodo();
        } else {
            encenderTodo();
        }
        
        //if (acumuladorReceptorD < 30) {
        //    EncenderMotores();
        //} else { //if (acumuladorReceptorD >= 20 && acumuladorReceptorD <= 70) {
        //    ApagarMotores();
        //} else if (acumuladorReceptorD > 70) {
        //    encenderMotores();
        //    motoresRetroceder();
        //}

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

void configurarPulsador() {
    PulsadorInit();
    // Configuro el pin change
    PCICR |= (1 << PCIE0);
    PCMSK0 = (1 << PCINT0);
}

ISR(PCINT0_vect) {
    // Delay para debounce
    // Dado que no tenemos necesidad de hacer nada mientras esperamos por el
    // debounce lo dejamos asi. Sino, deberiamos utilizar algun timer
    _delay_ms(20);

    if (IsPulsadorSet() == true) { 
        // significa que esta en 1 y hubo flanco ascendente genuino
        // se podria reemplazar la variable por poner apagar todo, poner 
        // el micro a dormir esperando solo esta interrupcion y luego
        // despertalo. Aca se lo despertaria
        if (estadoActual == DETENIDO) {
            estadoActual = TRACKING;
        } else {
            estadoActual = DETENIDO;
        }
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

void apagarTodo() {
    ApagarMotores();
    LedAOff();
    LedBOff();
    LedCOff();
    LedDOff();
    apagarEmisorSuperior();
}

void encenderTodo() {
    EncenderMotores();
    encenderEmisorSuperior();
}
