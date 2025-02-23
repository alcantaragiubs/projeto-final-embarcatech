#include "display.h"
#include <string.h>
#include <stdio.h>
#include "apresentacao.h"

void iniciaDisplay() {
    ssd1306_init();
}

void limpaDisplay(uint8_t *buffer) {
    memset(buffer, 0, ssd1306_buffer_length);
}

void display_update(uint8_t *buffer, int count, bool counter_paused, int saved_count) {
    const char *text[] = {"Pontos para", "ganhar o jogo:"};
    int y = 0;
    for (uint i = 0; i < 2; i++) {
        imprimir(buffer, 5, y, text[i]);
        y += 15;
    }

    char temp[10];
    if (counter_paused) {
        snprintf(temp, sizeof(temp), "Ganhar:%d", saved_count);
        imprimir(buffer, 5, y + 1, temp);

        // Mensagem para iniciar o jogo
        const char *start_text[] = {"Aperte A e B", "para iniciar"};
        for (uint i = 0; i < 2; i++) {
            imprimir(buffer, 5, y + 10 + (i * 15), start_text[i]);
        }
    } else {
        snprintf(temp, sizeof(temp), "%d", count);
        imprimir(buffer, 5, y + 1, temp);
    }
}