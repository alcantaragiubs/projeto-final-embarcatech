#include "buzzer.h"

// Inicializa o buzzer
void iniciaBuzzer(uint buzzer_pin) {
    gpio_set_function(buzzer_pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(buzzer_pin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (BUZZER_FREQUENCY * 4096));
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(buzzer_pin, 0);
}

// Toca um bipe por uma duração especificada
void beep(uint buzzer_pin, uint duration_ms) {
    pwm_set_gpio_level(buzzer_pin, 2048); // Ativa o buzzer
    sleep_ms(duration_ms);
    pwm_set_gpio_level(buzzer_pin, 0); // Desativa o buzzer
    sleep_ms(100);  // Pequena pausa
}
