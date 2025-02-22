#ifndef BUTTON_H
#define BUTTON_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"


void button_init(uint button_pin);
bool button_pressed(uint button_pin);
bool buttons_pressed(uint button1_pin, uint button2_pin);

#endif
