#ifndef DISPLAY_H
#define DISPLAY_H

#include "pico/stdlib.h"
#include "inc/ssd1306.h"

void iniciaDisplay();
void limpaDisplay(uint8_t *buffer);
void display_update(uint8_t *buffer, int count, bool counter_paused, int saved_count);

#endif
