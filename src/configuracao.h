#ifndef CONFIGURACAO_H
#define CONFIGURACAO_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"

#include "inc/ssd1306.h"
#include "joystick.h"
#include "display.h"
#include "botao.h"
#include "buzzer.h"
#include "partida.h"

// Definição dos pinos
extern const uint I2C_SDA;
extern const uint I2C_SCL;
extern const uint BOTAO_PIN;
extern const uint BOTAO1_PIN;
extern const uint BOTAO2_PIN;
extern const uint BUZZER_PIN;

// Declaração da função de setup
void configuracaoa(struct render_area *frame_area, uint8_t *ssd);

#endif // CONFIGURACAO_H
