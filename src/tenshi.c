#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "motores.h"
#include "sensores.h"
#include "tenshi.h"

// sensores

extern volatile uint8_t valorReceptorA;
extern volatile uint8_t valorReceptorB;
extern volatile uint8_t valorReceptorC;
extern volatile uint8_t valorReceptorD;

volatile estados estadoActual;
volatile uint8_t esNecesarioCheckearBoton = 0;

#define MAXIMO_PERMITIDO      150
#define MINIMO_PERMITIDO       70
#define DIFERENCIA_RELEVANTE   20
#define DIFERENCIA_EXCESIVA    50

typedef enum {
    ESPERAR,
    SEGUIR
} modo_t;

#define AvanzarAdelante()         motoresAvanzar()
#define GirarAvanzandoDerecha( )  motoresGirarDerecha()
#define GirarAvanzandoIzquierda() motoresGirarIzquierda()
#define GirarQuietoDerecha()      motoresGirarQuietoDerecha()
#define GirarQuietoIzquierda()    motoresGirarQuietoIzquierda()


// Si va a avanzar derecho, prende todos los leds. Si tiene que girar, prende los leds de el lado para el cual doblar.
#define LedsModoAvanzarAdelante()         LedAOn();  LedBOn();  LedCOn();  LedDOn(); 

#define LedsModoGirarAvanzandoDerecha()   LedAOff(); LedBOn();  LedCOff(); LedDOn();
#define LedsModoGirarAvanzandoIzquierda() LedAOn();  LedBOff(); LedCOn();  LedDOff();

#define LedsModoGirarQuietoDerecha()      LedAOff(); LedBOn();  LedCOff(); LedDOff();
#define LedsModoGirarQuietoIzquierda()    LedAOn();  LedBOff(); LedCOff(); LedDOff();

#define LedsModoEsperar()                 LedAOff(); LedBOff(); LedCOff(); LedDOff();

int main() {
    modo_t modo;
    uint8_t diferenciaValores;

    setup();
    
    while (1) {
        if (estadoActual == TRACKING) {
            
            diferenciaValores = max(valorReceptorA, valorReceptorB) - min(valorReceptorA, valorReceptorB);

            if ((valorReceptorA > MINIMO_PERMITIDO && valorReceptorA < MAXIMO_PERMITIDO) || (valorReceptorB > MINIMO_PERMITIDO && valorReceptorB < MAXIMO_PERMITIDO)) {
                modo = SEGUIR;
            } else { 
                modo = ESPERAR;
            }

            switch (modo) {
                case ESPERAR:
                    ApagarMotores();
                    LedsModoEsperar(); 
                    break;
                case SEGUIR:
                    EncenderMotores();
                    if (diferenciaValores < DIFERENCIA_RELEVANTE) {
                        LedsModoAvanzarAdelante();
                        motoresAvanzar();
                    /*} else if (diferenciaValores < DIFERENCIA_EXCESIVA) {
                        if (valorReceptorA < valorReceptorB) {
                            LedsModoGirarAvanzandoDerecha();
                        } else {
                            LedsModoGirarAvanzandoIzquierda();
                        }*/
                    } else { 
                        if (valorReceptorA < valorReceptorB) {
                            //LedsModoGirarQuietoDerecha();
                            LedsModoGirarAvanzandoDerecha();
                            motoresGirarDerecha();
                        } else {
                            //LedsModoGirarQuietoIzquierda();
                            LedsModoGirarAvanzandoIzquierda();
                            motoresGirarIzquierda();
                        }
                    }
                    break;
            }
            
        }
        
        if (esNecesarioCheckearBoton == 1) {
            ClearBit(PCMSK0, PCINT0); // desactiva interrupción botón
            if (IsPulsadorSet() == true) {
                _delay_ms(50);
                if (IsPulsadorSet() == true) {
                    if (estadoActual == DETENIDO) {
                        estadoActual = TRACKING;
                        encenderTodo();
                    } else {
                        estadoActual = DETENIDO;
                        apagarTodo();
                    }
                }
            }
            esNecesarioCheckearBoton = 0;
            SetBit(PCMSK0, PCINT0); // activa interrupción botón
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

void configurarPulsador() {
    PulsadorInit();
    // Configuro el pin change
    PCICR |= (1 << PCIE0);
    PCMSK0 = (1 << PCINT0);
}

ISR(PCINT0_vect) {
    esNecesarioCheckearBoton = 1;
}


void bajarPollera() {
    unsigned char aux = 10;
    while (aux > 0) {
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
    valorReceptorA = 0;
    valorReceptorB = 0;
    valorReceptorC = 0;
    valorReceptorD = 0;
}

void encenderTodo() {
    EncenderMotores();
    encenderEmisorSuperior();
}
