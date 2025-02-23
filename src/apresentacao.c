#include "apresentacao.h"

void iniciaDisplay() {
    ssd1306_init();
}

void imprimir(uint8_t *ssd, int x, int y, const char *texto) {
    ssd1306_draw_string(ssd, x, y, texto);
}

void limpaDisplay(uint8_t *buffer) {
    memset(buffer, 0, ssd1306_buffer_length);
}