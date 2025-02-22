#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "pico/stdlib.h"

void joystick_init();
const char* get_direction(uint adc_x_raw, uint adc_y_raw);
void read_joystick(uint *adc_x_raw, uint *adc_y_raw);

#endif
