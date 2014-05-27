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

volatile uint8_t esNecesarioCheckearBoton = 0;

int main() {
    estado_activacion_t estadoActivacion = APAGADO;
    uint8_t modoAccionNuevo = GIRANDO;
    uint8_t modoAccion = GIRANDO;
    uint8_t diferenciaValoresAB;
    uint8_t diferenciaValoresCD;

    setup();
    
    while (1) {
        if (estadoActivacion == PRENDIDO) {

            // sensado
            modoAccionNuevo = 0;
            
            if ((valorReceptorA > MINIMO_PERMITIDO && valorReceptorA < MAXIMO_PERMITIDO) || (valorReceptorB > MINIMO_PERMITIDO && valorReceptorB < MAXIMO_PERMITIDO)) {
				diferenciaValoresAB = max(valorReceptorA, valorReceptorB) - min(valorReceptorA, valorReceptorB);
				if (diferenciaValoresAB < DIFERENCIA_RELEVANTE) {
					modoAccionNuevo |= ATACANDO_ADELANTE;
				} else if (valorReceptorA < valorReceptorB) {
					modoAccionNuevo |= ATACANDO_ADELANTE_DERECHA;
				} else {
					modoAccionNuevo |= ATACANDO_ADELANTE_IZQUIERDA;
				}
			}
            
            if ((valorReceptorC > MINIMO_PERMITIDO && valorReceptorC < MAXIMO_PERMITIDO) || (valorReceptorD > MINIMO_PERMITIDO && valorReceptorD < MAXIMO_PERMITIDO)) {
				diferenciaValoresCD = max(valorReceptorC, valorReceptorD) - min(valorReceptorC, valorReceptorD);
				if (diferenciaValoresCD < DIFERENCIA_RELEVANTE) {
					modoAccionNuevo |= ATACANDO_ATRAS;
				} else if (valorReceptorC < valorReceptorD) {
					modoAccionNuevo |= ATACANDO_ATRAS_DERECHA;
				} else {
					modoAccionNuevo |= ATACANDO_ATRAS_IZQUIERDA;
				}
			}

            if (modoAccionNuevo != modoAccion) {
                // cambio motores
				switch (modoAccionNuevo) {
					case ATACANDO_ADELANTE:
						motoresAvanzar();
						LedsAvanzar();
						break;
					case ATACANDO_ADELANTE_DERECHA:
						motoresAvanzarYGirarDerecha();
						LedsAvanzarYGirarDerecha();
						break;
					case ATACANDO_ADELANTE_IZQUIERDA:
						motoresAvanzarYGirarIzquierda();
						LedsAvanzarYGirarIzquierda();
						break;
					case ATACANDO_ATRAS:
						motoresRetroceder();
						LedsRetroceder();
						break;
					case ATACANDO_ATRAS_DERECHA:
						motoresRetrocederYGirarDerecha();
						LedsRetrocederYGirarDerecha();
						break;
					case ATACANDO_ATRAS_IZQUIERDA:
						motoresRetrocederYGirarIzquierda();
						LedsRetrocederYGirarIzquierda();
						break;
					case GIRANDO:
					default:
						motoresGirarQuietoDerecha();
						LedsGirarQuietoDerecha();
						break;
				}
                // cambiar estado
                modoAccion = modoAccionNuevo;
                
            }
            
            //diferenciaValores = max(valorReceptorA, valorReceptorB) - min(valorReceptorA, valorReceptorB);

            //if ((valorReceptorA > MINIMO_PERMITIDO && valorReceptorA < MAXIMO_PERMITIDO) || (valorReceptorB > MINIMO_PERMITIDO && valorReceptorB < MAXIMO_PERMITIDO)) {
                //modo = SEGUIR;
            //} else { 
                //modo = ESPERAR;
            //}

            //switch (modo) {
                //case ESPERAR:
                    //ApagarMotores();
                    //LedsModoEsperar(); 
                    //break;
                //case SEGUIR:
                    //EncenderMotores();
                    //if (diferenciaValores < DIFERENCIA_RELEVANTE) {
                        //LedsModoAvanzarAdelante();
                        //motoresAvanzar();
                    // /*} else if (diferenciaValores < DIFERENCIA_EXCESIVA) {
                        //if (valorReceptorA < valorReceptorB) {
                            //LedsModoGirarAvanzandoDerecha();
                        //} else {
                            //LedsModoGirarAvanzandoIzquierda();
                        //}*/
                    //} else { 
                        //if (valorReceptorA < valorReceptorB) {
                            ////LedsModoGirarQuietoDerecha();
                            //LedsModoGirarAvanzandoDerecha();
                            //motoresGirarDerecha();
                        //} else {
                            ////LedsModoGirarQuietoIzquierda();
                            //LedsModoGirarAvanzandoIzquierda();
                            //motoresGirarIzquierda();
                        //}
                    //}
                    //break;
            //}
            
        }
        
        
        // cambia entre los estados PRENDIDO y APAGADO si se apretó el botón
        if (esNecesarioCheckearBoton == 1) {
            ClearBit(PCMSK0, PCINT0); // desactiva interrupción botón
            if (IsPulsadorSet() == true) {
                _delay_ms(50);
                if (IsPulsadorSet() == true) {
                    if (estadoActivacion == APAGADO) {
                        //_delay_ms(5000); // para competir hay que esperar 5 segundos
                        estadoActivacion = PRENDIDO;
                        encenderTodo();
                    } else {
                        estadoActivacion = APAGADO;
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
