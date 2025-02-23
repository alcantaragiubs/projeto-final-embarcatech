#include "configuracao.h"

// Definição dos pinos
const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

const uint BOTAO_PIN = 22;
const uint BOTAO1_PIN = 5;
const uint BOTAO2_PIN = 6;

const uint BUZZER_PIN = 21;

void configuracaoa(struct render_area *frame_area, uint8_t *ssd) {
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    iniciaDisplay();
    iniciaJoystick();
    iniciaBotao(BOTAO_PIN);
    iniciaBotao(BOTAO1_PIN);
    iniciaBotao(BOTAO2_PIN);
    iniciaBuzzer(BUZZER_PIN);

    frame_area->start_column = 0;
    frame_area->end_column = ssd1306_width - 1;
    frame_area->start_page = 0;
    frame_area->end_page = ssd1306_n_pages - 1;
    calculate_render_area_buffer_length(frame_area);

    limpaDisplay(ssd);
}
