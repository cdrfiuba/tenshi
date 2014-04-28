#include "motores.h"

void configurarMotores() {
    //Configuramos como salidas los pines de PWM
    SetBit(DDR_MI_EN, MI_EN_NUMBER);
    SetBit(DDR_MD_EN, MD_EN_NUMBER);

    //Configuramos como salidas los pines "In's" del puente H
    SetBit(DDR_MI_IN1, MI_IN1_NUMBER);
    SetBit(DDR_MI_IN2, MI_IN2_NUMBER);
    SetBit(DDR_MD_IN1, MD_IN1_NUMBER);
    SetBit(DDR_MD_IN2, MD_IN2_NUMBER);

    ApagarMotores();
}

#define MotorDerechoAvanzar()           {ClearBit(PORT_MD_IN1, MD_IN1_NUMBER); SetBit(PORT_MD_IN2, MD_IN2_NUMBER);}
#define MotorIzquierdoAvanzar()         {ClearBit(PORT_MI_IN1, MI_IN1_NUMBER); SetBit(PORT_MI_IN2, MI_IN2_NUMBER);}
#define MotorDerechoFrenarTrabado()     {SetBit(PORT_MD_IN1, MD_IN1_NUMBER); SetBit(PORT_MD_IN2, MD_IN2_NUMBER);}
#define MotorIzquierdoFrenarTrabado()   {SetBit(PORT_MI_IN1, MI_IN1_NUMBER); SetBit(PORT_MI_IN2, MI_IN2_NUMBER);}
#define MotorDerechoFrenarLibre()       {ClearBit(PORT_MD_IN1, MD_IN1_NUMBER); ClearBit(PORT_MD_IN2, MD_IN2_NUMBER);}
#define MotorIzquierdoFrenarLibre()     {ClearBit(PORT_MI_IN1, MI_IN1_NUMBER); ClearBit(PORT_MI_IN2, MI_IN2_NUMBER);}
#define MotorDerechoRetroceder()        {SetBit(PORT_MD_IN1, MD_IN1_NUMBER); ClearBit(PORT_MD_IN2, MD_IN2_NUMBER);}
#define MotorIzquierdoRetroceder()      {SetBit(PORT_MI_IN1, MI_IN1_NUMBER); ClearBit(PORT_MI_IN2, MI_IN2_NUMBER);}

void motoresAvanzar(void) {
    MotorDerechoAvanzar();
    MotorIzquierdoAvanzar();
}

void motoresRetroceder(void) {
    MotorDerechoRetroceder();
    MotorIzquierdoRetroceder();
}

void motoresGirarQuietoDerecha(void) {
    MotorDerechoRetroceder();
    MotorIzquierdoAvanzar();    
}

void motoresGirarQuietoIzquierda(void) {
    MotorDerechoAvanzar();
    MotorIzquierdoRetroceder();
}

void motoresGirarDerecha(void) {
    MotorDerechoFrenarLibre();
    MotorIzquierdoAvanzar();
}

void motoresGirarIzquierda(void) {
    MotorDerechoAvanzar();
    MotorIzquierdoFrenarLibre();
}


void configurarMotorPolleras() {
    SetBit(DDR_SERVO,SERVO_NUMBER);
    ClearBit(PORT_SERVO,SERVO_NUMBER);
}
