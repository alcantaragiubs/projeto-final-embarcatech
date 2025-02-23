#include "pico/stdlib.h"
#include "botao.h"
#include "ssd1306.h"
#include <stdio.h>
#include "partida.h"
#include "apresentacao.h"

int pontosA = 0;
int pontosB = 0;

void atualizaDisplay(uint8_t *buffer, int count, bool counter_paused, int saved_count) { //configura partida
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
                counter_paused = false; //botar os count em portugues
                count = 0;
            }
            sleep_ms(200);
        }
        if (counter_paused && pressionaBotao(BOTAO1_PIN) && pressionaBotao(BOTAO2_PIN)) {
            limpaDisplay(ssd);
            beep(BUZZER_PIN, 1000);
            snprintf(temp, sizeof(temp), "Max: %d", *saved_count);
            imprimir(ssd, 5, 15, temp);
            imprimir(ssd, 5, 30, "Time a | Time b"); 
            render_on_display(ssd, frame_area);
            break; 
        }
        limpaDisplay(ssd);
        atualizaDisplay(ssd, count, counter_paused, *saved_count);
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
    imprimir(ssd, 5, 45, "Aperte reset");
    render_on_display(ssd, frame_area);
}
