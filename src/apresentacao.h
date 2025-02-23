#ifndef APRESENTACAO_H
#define APRESENTACAO_H

#include <stdint.h>
#include "pico/stdlib.h"
#include "inc/ssd1306.h"

void iniciaDisplay();
void imprimir(uint8_t *ssd, int x, int y, const char *texto);
void limpaDisplay(uint8_t *buffer);


#endif // APRESENTACAO_H