#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define BUZZER_FREQUENCY 2000  // Defina a frequência do buzzer

void buzzer_init(uint buzzer_pin);
void beep(uint buzzer_pin, uint duration_ms);

#endif
