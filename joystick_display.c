#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;
const uint BUTTON_PIN = 22; // Defina o pino GPIO onde o botão do joystick está conectado


// Função para determinar a direção do joystick
const char* get_direction(uint adc_x_raw, uint adc_y_raw) {
    // Defina os limites para considerar o joystick como "centrado"
    const uint center_threshold = 200; // Ajuste conforme necessário
    const uint min_threshold = 1000;  // Ajuste conforme necessário
    const uint max_threshold = 3000;  // Ajuste conforme necessário

    if (adc_x_raw < min_threshold) {
        return "Esquerda";
    } else if (adc_x_raw > max_threshold) {
        return "Direita";
    } else if (adc_y_raw < min_threshold) {
        return "Baixo";
    } else if (adc_y_raw > max_threshold) {
        return "Cima";
    } else {
        return "Centro";
    }
}

int main() {
    stdio_init_all();

    // Inicialização do I2C
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicialização do display OLED
    ssd1306_init();

    // Área de renderização
    struct render_area frame_area = {
        start_column: 0,
        end_column: ssd1306_width - 1,
        start_page: 0,
        end_page: ssd1306_n_pages - 1
    };
    calculate_render_area_buffer_length(&frame_area);

    // Buffer para o display
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);

    // Inicialização do ADC para o joystick
    adc_init();
    adc_gpio_init(26); // Eixo Y
    adc_gpio_init(27); // Eixo X

    // Configuração do pino do botão
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN); // Habilita o resistor de pull-up interno

    int count = 0;
    bool counter_paused = false; // Variável para controlar se o contador está pausado
    int saved_count = 0; // Variável para salvar o valor do contador

    while (true) {
        // Ler valores do joystick
        adc_select_input(0);
        uint adc_y_raw = adc_read();
        adc_select_input(1);
        uint adc_x_raw = adc_read();

        // Determinar a direção do joystick
        const char* direction = get_direction(adc_x_raw, adc_y_raw);

        // Limpar o display
        memset(ssd, 0, ssd1306_buffer_length);
        
        // Atualizar o contador com base na direção
        if (strcmp(direction, "Cima") == 0) {
            count++; // Incrementa o contador se a direção for "Cima"
        } else if (strcmp(direction, "Baixo") == 0 && count != 0) {
            count--; // Decrementa o contador se a direção for "Baixo"
        }
        char *text[] = {
            "Pontos para",
            "ganhar o jogo:"};
    
        int y = 0;
        for (uint i = 0; i < count_of(text); i++)
        {
            ssd1306_draw_string(ssd, 5, y, text[i]);
            y += 15;
        }
        bool button_state = gpio_get(BUTTON_PIN);
        if (button_state == 0) { // Botão pressionado (nível lógico baixo)
            if (!counter_paused) {
                // Pausar o contador e salvar o valor
                counter_paused = true;
                saved_count = count;
                // printf("Contador pausado! Valor salvo: %d\n", saved_count);
            } else {
                // Se já estiver pausado, reiniciar o contador
                counter_paused = false;
                count = 0; // Ou reiniciar com outro valor, se necessário
                // printf("Contador reiniciado!\n");
            }

            // Debounce: aguardar um pouco para evitar leituras múltiplas
            sleep_ms(200); // Ajuste o tempo conforme necessário
        }
         // Exibir o valor do contador no display
         char temp[10]; // Buffer temporário para formatar o número
         if (counter_paused) {
             snprintf(temp, sizeof(temp), "Ganhar:%d", saved_count); // Exibe o valor salvo
         } else {
             snprintf(temp, sizeof(temp), "%d", count); // Exibe o valor atual
         }
         ssd1306_draw_string(ssd, 5, y + 1, temp); // Exibe o valor no display
        // Renderizar no display
        render_on_display(ssd, &frame_area);

        sleep_ms(100);
    }

    return 0;
}