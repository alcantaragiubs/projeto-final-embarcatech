#include "apresentacao.h"

void imprimir(uint8_t *ssd, int x, int y, const char *texto) {
    ssd1306_draw_string(ssd, x, y, texto);
}
