// partida.c

#include "pico/stdlib.h"
#include "display.h"
#include "button.h"
#include "ssd1306.h"
#include <stdio.h>
#include "button.h"
#include "partida.h"
int pontosA = 0;
int pontosB = 0;

void update_team_points() {
    if (button_pressed(BUTTON1_PIN)) {
        pontosA++;
        sleep_ms(200);  // Delay para debouncing
    }
    if (button_pressed(BUTTON2_PIN)) {
        pontosB++;
        sleep_ms(200); 
    }
}

void partida_loop(uint8_t *ssd, struct render_area *frame_area, int saved_count) {
    pontosA = 0;
    pontosB = 0;

    while (pontosA < saved_count && pontosB < saved_count) {
        update_team_points();

        char pontos_str[32];
        snprintf(pontos_str, sizeof(pontos_str), "A: %d  B: %d", pontosA, pontosB);

        ssd1306_draw_string(ssd, 5, 45, pontos_str);
        render_on_display(ssd, frame_area);

        sleep_ms(100);
    }

    display_clear(ssd);
    ssd1306_draw_string(ssd, 5, 15, "Fim de jogo");
    if(pontosA == saved_count) {
        ssd1306_draw_string(ssd, 5, 30, "Vitoria: Time A");
    }
    else{
        ssd1306_draw_string(ssd, 5, 30, "Vitoria: Time B");
    }
    render_on_display(ssd, frame_area);
}
