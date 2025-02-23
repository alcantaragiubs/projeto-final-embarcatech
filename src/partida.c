#include "pico/stdlib.h"
#include "display.h"
#include "botao.h"
#include "ssd1306.h"
#include <stdio.h>
#include "partida.h"
#include "apresentacao.h"

int pontosA = 0;
int pontosB = 0;

void iniciaPartida(int *saved_count, uint8_t *ssd, struct render_area *frame_area) {
    int count = 0;
    bool counter_paused = false;
    char temp[32];
    while (true) {
        uint adc_x_raw, adc_y_raw;
        leJoystick(&adc_x_raw, &adc_y_raw);
        const char* direction = getDirecao(adc_x_raw, adc_y_raw);

        if (strcmp(direction, "Cima") == 0) {
            count++;
        } else if (strcmp(direction, "Baixo") == 0 && count > 0) {
            count--;
        }

        if (pressionaBotao(BOTAO_PIN)) {
            if (!counter_paused) {
                counter_paused = true;
                *saved_count = count;
            } else {
                counter_paused = false;
                count = 0;
            }
            sleep_ms(200);
        }
        if (counter_paused && pressionaBotao(BOTAO1_PIN) && pressionaBotao(BOTAO2_PIN)) {
            limpaDisplay(ssd);
            beep(BUZZER_PIN, 1000);
            snprintf(temp, sizeof(temp), "Max: %d", *saved_count);
            ssd1306_draw_string(ssd, 5, 15, temp);
            ssd1306_draw_string(ssd, 5, 30, "Time a | Time b"); 
            render_on_display(ssd, frame_area);
            break; 
        }
        limpaDisplay(ssd);
        display_update(ssd, count, counter_paused, *saved_count);
        render_on_display(ssd, frame_area);

        sleep_ms(100);
    }
    
}

void update_team_points() {
    if (pressionaBotao(BOTAO1_PIN)) {
        pontosA++;
        sleep_ms(200);
    }
    if (pressionaBotao(BOTAO2_PIN)) {
        pontosB++;
        sleep_ms(200); 
    }
}

void joga(uint8_t *ssd, struct render_area *frame_area, int *saved_count) {
    while (pontosA < *saved_count && pontosB < *saved_count) {
        update_team_points();

        char pontos_str[32];
        snprintf(pontos_str, sizeof(pontos_str), "A: %d  B: %d", pontosA, pontosB);

        imprimir(ssd, 5, 45, pontos_str);
        render_on_display(ssd, frame_area);

        sleep_ms(100);
    }

    limpaDisplay(ssd);
    beep(BUZZER_PIN, 1000);
    imprimir(ssd, 5, 15, "Fim de jogo");
    if(pontosA == *saved_count) {
        imprimir(ssd, 5, 30, "Vitoria: Time A");
    }
    else{
        imprimir(ssd, 5, 30, "Vitoria: Time B");
    }
    render_on_display(ssd, frame_area);
}
