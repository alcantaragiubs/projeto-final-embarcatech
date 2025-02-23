#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "pico/stdlib.h"

void iniciaJoystick();
const char* getDirecao(uint adc_x_raw, uint adc_y_raw);
void leJoystick(uint *adc_x_raw, uint *adc_y_raw);

#endif
