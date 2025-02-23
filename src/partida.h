#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdint.h>
#include "ssd1306.h"

#ifdef __cplusplus
extern "C" {
#endif

// Declaramos os pinos, que estão definidos em main.c
extern const uint BOTAO_PIN;
extern const uint BOTAO1_PIN;
extern const uint BOTAO2_PIN;
extern const uint BUZZER_PIN;

// Função que contém toda a lógica da partida
void atualizaDisplay(uint8_t *buffer, int count, bool counter_paused, int saved_count);
void iniciaPartida(int *saved_count, uint8_t *ssd, struct render_area *frame_area);
void joga(uint8_t *ssd, struct render_area *frame_area, int *saved_count);

#ifdef __cplusplus
}
#endif

#endif // PARTIDA_H
