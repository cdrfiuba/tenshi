#include <avr/interrupt.h>
#include "sensores.h"

#include "tenshi.h"
#include <util/delay.h>
/*
COMO USAR EL SENSOR PL-IRM0101-3
Necesita pulsos de 38kHz y leds emisores de 940nm.

Para funcionar, el sensor necesita recibir una señal cuadrada de 1200 us de 
período. Con un duty cycle de 0.5, 600 us pasan en 0, y 600 us pasan a su vez 
con un pulso de 38KHz.

El ATmega88 que usamos está a 8 MHz. Con un timer en CTC (clear timer on 
compare match) sin prescaler seteamos el punto de comparación en 105, para 
que el ciclo conste de 210 ciclos de maquina ((8 MHz / 38 KHz) = 210,5263). 
Contando cada 210 ciclos, la frecuencia que se obtiene es de 38,095 KHz.

En la interrupción del timer, usamos un contador para medir pulsos de 600us, 
y usamos una variable de control para determinar si la señal que se genera 
está en modo oscilar (a 38 KHz) o en modo cero. Cuando se cambia a modo cero
solamente se setea el PORT en cero. Cuando se está en modo oscilar, se hace
un toggle del PORT en cada interrupción. En ambos modos se cuentan 23 
interrupciones (1 / 38095 Hz * 1000 * 1000 = 26,25 us ==> 23 interrupciones 
son 603,75 us) para cambiar de modo.

*/

volatile uint8_t contadorInterrupcionesEmisorSuperior = 0;
typedef enum {
    MODO_CERO,
    MODO_OSCILAR
} t_modosOperacionEmisorSuperior;
volatile t_modosOperacionEmisorSuperior modoOperacionEmisorSuperior;

ISR(TIMER2_COMPA_vect) {
    contadorInterrupcionesEmisorSuperior++;
	if (contadorInterrupcionesEmisorSuperior == CANTIDAD_DE_INTERRUPCIONES) {
        contadorInterrupcionesEmisorSuperior = 0;
        if (modoOperacionEmisorSuperior == MODO_CERO) {
            ClearBit(PORT_EMI, EMI_NUMBER);
            modoOperacionEmisorSuperior = MODO_OSCILAR;
        } else {
            modoOperacionEmisorSuperior = MODO_CERO;
        }
    }
    if (modoOperacionEmisorSuperior == MODO_OSCILAR) {
        // escribir al PIN implica un ToggleBit
        SetBit(PIN_EMI, EMI_NUMBER); 
    }
}

void configurarSensoresSuperiores() {
	// Se configura el timer 2 en modo CTC segun las definiciones del .h

	TCCR2A = (0 << COM2A1) | (0 << COM2A0) | (0 << COM2B1) | (0 << COM2B0) | (1 << WGM21) | (0 << WGM20);
	TCCR2B = (0 << WGM22) | TIMER_ON;
	
	TCNT2 = 0;
	OCR2A = OCR_EMISOR_TIEMPO_CICLOS;

	// CTC esta con OCR2A
	TIMSK2 = (0 << OCIE2B) | (1 << OCIE2A) | (0 << TOIE2);

    // configura emisor como salida, receptores como entrada
    SetBit(DDR_EMI, EMI_NUMBER);
    ClearBit(PORT_EMI, EMI_NUMBER);

    ClearBit(DDR_RA, RA_NUMBER);
    SetBit(PORT_RA, RA_NUMBER);

    ClearBit(DDR_RB, RB_NUMBER);
    SetBit(PORT_RB, RB_NUMBER);

    ClearBit(DDR_RC, RC_NUMBER);
    SetBit(PORT_RC, RC_NUMBER);

    ClearBit(DDR_RD, RD_NUMBER);
    SetBit(PORT_RD, RD_NUMBER);

    // interrupciones PCINT16~23 en botón
    PCICR |= (1 << PCIE2);

	// los sensores están en PCINT19, PCINT21, PCINT20, PCINT18
    // activa interrupciones (los PC son por toggle)
    PCMSK2 = (1 << PCINT18) | (1 << PCINT19) | (1 << PCINT20) | (1 << PCINT21);
}

void encenderEmisorSuperior() {
    TCCR2B |= TIMER_ON;
}

void apagarEmisorSuperior() {
    TCCR2B &= ~(TIMER_OFF_MASK);
}

// interrupciones de sensores
ISR(PCINT2_vect) {
	IsBitSet(PIN_RA, RA_NUMBER) ? LedAOn() : LedAOff();
	IsBitSet(PIN_RB, RB_NUMBER) ? LedBOn() : LedBOff();
	IsBitSet(PIN_RC, RC_NUMBER) ? LedCOn() : LedCOff();
	IsBitSet(PIN_RD, RD_NUMBER) ? LedDOn() : LedDOff();
}

