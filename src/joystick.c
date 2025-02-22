#include "joystick.h"
#include "hardware/adc.h"

void joystick_init() {
    adc_init();
    adc_gpio_init(26); // Eixo Y
    adc_gpio_init(27); // Eixo X
}

void read_joystick(uint *adc_x_raw, uint *adc_y_raw) {
    adc_select_input(0);
    *adc_y_raw = adc_read();
    adc_select_input(1);
    *adc_x_raw = adc_read();
}

const char* get_direction(uint adc_x_raw, uint adc_y_raw) {
    const uint center_threshold = 200;
    const uint min_threshold = 1000;
    const uint max_threshold = 3000;

    if (adc_x_raw < min_threshold) return "Esquerda";
    if (adc_x_raw > max_threshold) return "Direita";
    if (adc_y_raw < min_threshold) return "Baixo";
    if (adc_y_raw > max_threshold) return "Cima";
    
    return "Centro";
}
