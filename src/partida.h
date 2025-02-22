#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdint.h>
#include "ssd1306.h"  // Inclua esse cabeçalho para obter a definição de 'struct render_area' e 'ssd1306_buffer_length'


extern const uint BUTTON1_PIN;
extern const uint BUTTON2_PIN;


extern int pontosA;
extern int pontosB;
void partida_loop(uint8_t *ssd, struct render_area *frame_area, int saved_count);


#endif // PARTIDA_H
