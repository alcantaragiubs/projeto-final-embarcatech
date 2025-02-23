#ifndef BOTAO_H
#define BOTAO_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"


void iniciaBotao(uint pinBotao);
bool pressionaBotao(uint pinBotao);

#endif
