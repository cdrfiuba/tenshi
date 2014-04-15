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

    apagarMotores();
}

void motoresAvanzar() {
    ClearBit(PORT_MI_IN1, MI_IN1_NUMBER);
    SetBit(PORT_MI_IN2, MI_IN2_NUMBER);

    ClearBit(PORT_MD_IN1, MD_IN1_NUMBER);
    SetBit(PORT_MD_IN2, MD_IN2_NUMBER);
}

void motoresGirarIzquierda() {
    ClearBit(PORT_MI_IN1, MI_IN1_NUMBER);
    SetBit(PORT_MI_IN2, MI_IN2_NUMBER);

    ClearBit(PORT_MD_IN1, MD_IN1_NUMBER);
    SetBit(PORT_MD_IN2, MD_IN2_NUMBER);
}

void motoresGirarDerecha() {
    ClearBit(PORT_MI_IN1, MI_IN1_NUMBER);
    SetBit(PORT_MI_IN2, MI_IN2_NUMBER);

    ClearBit(PORT_MD_IN1, MD_IN1_NUMBER);
    SetBit(PORT_MD_IN2, MD_IN2_NUMBER);
}

void motoresRetroceder() {
    SetBit(PORT_MI_IN1, MI_IN2_NUMBER);
    ClearBit(PORT_MI_IN2, MI_IN1_NUMBER);

    SetBit(PORT_MD_IN1, MD_IN2_NUMBER);
    ClearBit(PORT_MD_IN2, MD_IN1_NUMBER);
}

void configurarMotorPolleras() {
    SetBit(DDR_SERVO,SERVO_NUMBER);
    ClearBit(PORT_SERVO,SERVO_NUMBER);
}
