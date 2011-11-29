#include <avr/interrupt.h>
#include "sensores.h"

#include "mjolnir.h"
#include <util/delay.h>
void configurarTimerSensoresSup () {
	// Se configura el timer 2 en modo CTC segun las definiciones del .h

	TCCR2A = (0<<COM2A1)|(0<<COM2A0)|(0<<COM2B1)|(0<<COM2B0)|(1<<WGM21)|(0<<WGM20);
	TCCR2B = (0<<WGM22);
	
	TCNT2 = 0;
	OCR2A = OCR_EMISORES_SUP;

	// CTC esta con OCR2A
	TIMSK2 = (0<<OCIE2B)|(1<<OCIE2A)|(0<<TOIE2);
}

void configurarPinSensoresSup () {
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

	PCICR |= (1<<PCIE2);
	//PCMSK2 = (1<<PCINT18) | (1<<PCINT19) | (1<<PCINT20) | (1<<PCINT21);
	PCMSK2 = (1<<PCINT21);

}

void encenderEmisorSuperior(){
		ClearBit(TCCR2B, CS22);
		ClearBit(TCCR2B, CS21);
		SetBit(TCCR2B, CS20);
}

void apagarEmisorSuperior(){
		ClearBit(TCCR2B, CS22);
		ClearBit(TCCR2B, CS21);
		ClearBit(TCCR2B, CS20);
}

volatile uint8_t contPulsosEmSup=0;

ISR(TIMER2_COMPA_vect){
	// Cuando se da la comparacion cambio el estado del pin solo si estoy en alto
	// Hay una variable global que me dice si estoy en alto o en bajo
	contPulsosEmSup++;
	if(contPulsosEmSup <= CANT_PULSOS_ALTO_EM_SUP) SetBit(PIN_EMI, EMI_NUMBER);
}

ISR(PCINT2_vect){
  if (IsBitSet(PIN_RA, RA_NUMBER)) LedAOn();
  else LedAOff();
  if (IsBitSet(PIN_RB, RB_NUMBER)) LedBOn();
  else LedBOff();
  if (IsBitSet(PIN_RC, RC_NUMBER)) LedCOn();
  else LedCOff();
  if (IsBitSet(PIN_RD, RD_NUMBER)) LedDOn();
  else LedDOff();
//  _delay_ms(250);
  SetBit(PCIFR, PCIF2);
}


