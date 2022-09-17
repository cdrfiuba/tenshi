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
volatile uint8_t esNecesarioCheckearActivador = 0;

int main() {
    estado_activacion_t estadoActivacion = APAGADO;
    uint8_t modoAccionNuevo = GIRANDO;
    uint8_t modoAccion = GIRANDO;
    uint8_t diferenciaValoresAB;
    uint8_t diferenciaValoresCD;
    direcciones_t ultimaDireccion = DERECHA;

    setup();
    
    //while (1) {
        //if (IsActivadorSet() == true) {
            //LedAOn();
        //} else {
            //LedAOff();
        //}
    //}
    
    while (1) {
        if (estadoActivacion == PRENDIDO) {


            // para cada par de receptores (frontales AB y traseros CD) se realiza 
            // lo siguiente: 
            // si se encuentran entre dos límites permitidos (MINIMO y MAXIMO), 
            // se toma la diferencia entre ellos, y si esa diferencia es inferior 
            // a otro límite (DIFERENCIA_RELEVANTE) se asume que el oponente está 
            // justo adelante del robot. Si está por debajo de ese límite, según 
            // cuál de los sensores tiene el mayor valor (esto es, que está a 
            // menor distancia del objetivo), se asume que el oponente está a la 
            // izquierda o a la derecha.
            // Cada modo de acción se obtiene sumando un 1 o un 0 para cada receptor,
            // como está definido en el enum modo_accion_t.
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
						ultimaDireccion = DERECHA;
						break;
					case ATACANDO_ADELANTE_IZQUIERDA:
						motoresAvanzarYGirarIzquierda();
						LedsAvanzarYGirarIzquierda();
						ultimaDireccion = IZQUIERDA;
						break;
					case ATACANDO_ATRAS:
						motoresRetroceder();
						LedsRetroceder();
						break;
					case ATACANDO_ATRAS_DERECHA:
						motoresRetrocederYGirarDerecha();
						LedsRetrocederYGirarDerecha();
						ultimaDireccion = IZQUIERDA;
						break;
					case ATACANDO_ATRAS_IZQUIERDA:
						motoresRetrocederYGirarIzquierda();
						LedsRetrocederYGirarIzquierda();
						ultimaDireccion = DERECHA;
						break;
					case GIRANDO:
					default:
					    if (ultimaDireccion == IZQUIERDA) {
					        motoresGirarQuietoIzquierda();
					        LedsGirarQuietoIzquierda();
					    } else {
						    motoresGirarQuietoDerecha();
						    LedsGirarQuietoDerecha();
						}
						break;
				}
                // cambiar estado
                modoAccion = modoAccionNuevo;
                _delay_ms(5);
                
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
            esNecesarioCheckearBoton = 0;
            if (IsPulsadorSet() == true) {
                _delay_ms(20);
                if (IsPulsadorSet() == true) {
                    if (estadoActivacion == APAGADO) {
                        //_delay_ms(1000); // para competir hay que esperar 5 segundos
                        estadoActivacion = PRENDIDO;
                        encenderTodo();
                    } else {
                        estadoActivacion = APAGADO;
                        apagarTodo();
                    }
                }
            }

            SetBit(PCMSK0, PCINT0); // activa interrupción botón
        }
        
        // cambia a PRENDIDO o APAGADO según el estado del activador
        /*if (esNecesarioCheckearActivador == 1) {
            //ClearBit(PCMSK0, PCINT1); // desactiva interrupción activador
            _delay_ms(5);
            if (IsActivadorSet() == true) {
                estadoActivacion = PRENDIDO;
                encenderTodo();
            } else {
                estadoActivacion = APAGADO;
                //apagarTodo();
            }
            esNecesarioCheckearActivador = 0;
            //SetBit(PCMSK0, PCINT1); // activa interrupción botón
        }*/
    }
}


void setup() {
    LedDInit(); 
    LedCInit(); 
    LedBInit(); 
    LedAInit(); 
    
    configurarPulsadorYActivador();
    configurarMotores();
    configurarSensoresSuperiores();
    configurarMotorPolleras();
    
    sei();
}

void configurarPulsadorYActivador() {
    PulsadorInit();
    //ActivadorInit();
    // Configuro el pin change
    PCICR |= (1 << PCIE0);
    PCMSK0 = (1 << PCINT0);
}

ISR(PCINT0_vect) {
    esNecesarioCheckearBoton = 1;
}
/*ISR(PCINT1_vect) {
    esNecesarioCheckearActivador = 0;
}*/


//void bajarPollera() {
    //unsigned char aux = 10;
    //while (aux > 0) {
        //SetBit(PORT_SERVO, SERVO_NUMBER);
        //_delay_ms(1);
        //ClearBit(PORT_SERVO, SERVO_NUMBER);
        //_delay_ms(19);
        //aux--;
    //}
//}

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
