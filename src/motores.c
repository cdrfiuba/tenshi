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

#define MotorDerechoAvanzar()           {ClearBit(PORT_MD_IN1, MD_IN1_NUMBER);   SetBit(PORT_MD_IN2, MD_IN2_NUMBER);}
#define MotorIzquierdoAvanzar()         {ClearBit(PORT_MI_IN1, MI_IN1_NUMBER);   SetBit(PORT_MI_IN2, MI_IN2_NUMBER);}
#define MotorDerechoFrenarTrabado()     {  SetBit(PORT_MD_IN1, MD_IN1_NUMBER);   SetBit(PORT_MD_IN2, MD_IN2_NUMBER);}
#define MotorIzquierdoFrenarTrabado()   {  SetBit(PORT_MI_IN1, MI_IN1_NUMBER);   SetBit(PORT_MI_IN2, MI_IN2_NUMBER);}
#define MotorDerechoFrenarLibre()       {ClearBit(PORT_MD_IN1, MD_IN1_NUMBER); ClearBit(PORT_MD_IN2, MD_IN2_NUMBER);}
#define MotorIzquierdoFrenarLibre()     {ClearBit(PORT_MI_IN1, MI_IN1_NUMBER); ClearBit(PORT_MI_IN2, MI_IN2_NUMBER);}
#define MotorDerechoRetroceder()        {  SetBit(PORT_MD_IN1, MD_IN1_NUMBER); ClearBit(PORT_MD_IN2, MD_IN2_NUMBER);}
#define MotorIzquierdoRetroceder()      {  SetBit(PORT_MI_IN1, MI_IN1_NUMBER); ClearBit(PORT_MI_IN2, MI_IN2_NUMBER);}

inline void motoresAvanzar() {
    MotorDerechoAvanzar();
    MotorIzquierdoAvanzar();
}
inline void motoresRetroceder() {
    MotorDerechoRetroceder();
    MotorIzquierdoRetroceder();
}

inline void motoresGirarQuietoDerecha() {
    MotorDerechoRetroceder();
    MotorIzquierdoAvanzar();    
}
inline void motoresGirarQuietoIzquierda() {
    MotorDerechoAvanzar();
    MotorIzquierdoRetroceder();
}

inline void motoresAvanzarYGirarDerecha() {
    MotorDerechoFrenarLibre();
    MotorIzquierdoAvanzar();
}
inline void motoresAvanzarYGirarIzquierda() {
    MotorDerechoAvanzar();
    MotorIzquierdoFrenarLibre();
}

inline void motoresRetrocederYGirarDerecha() {
    MotorDerechoFrenarLibre();
    MotorIzquierdoRetroceder();
}
inline void motoresRetrocederYGirarIzquierda() {
    MotorDerechoRetroceder();
    MotorIzquierdoFrenarLibre();
}


void configurarMotorPolleras() {
    SetBit(DDR_SERVO,SERVO_NUMBER);
    ClearBit(PORT_SERVO,SERVO_NUMBER);
}
