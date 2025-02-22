#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"

#include "inc/ssd1306.h"
#include "joystick.h"
#include "display.h"
#include "button.h"
#include "buzzer.h"
#include "partida.h"

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

const uint BUTTON_PIN = 22;
extern const uint BUTTON1_PIN = 5;
extern const uint BUTTON2_PIN = 6;

const uint BUZZER_PIN = 21;


int main() {
    stdio_init_all();


    // Inicializa componentes
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    display_init();
    joystick_init();
    button_init(BUTTON_PIN);
    button_init(BUTTON1_PIN);
    button_init(BUTTON2_PIN);
    buzzer_init(BUZZER_PIN);

    struct render_area frame_area = {
        .start_column = 0,
        .end_column = ssd1306_width - 1,
        .start_page = 0,
        .end_page = ssd1306_n_pages - 1
    };
    calculate_render_area_buffer_length(&frame_area);

    uint8_t ssd[ssd1306_buffer_length];
    display_clear(ssd);

    int count = 0;
    bool counter_paused = false;
    int saved_count = 0;
    char temp[32];

    while (true) {
        uint adc_x_raw, adc_y_raw;
        read_joystick(&adc_x_raw, &adc_y_raw);
        const char* direction = get_direction(adc_x_raw, adc_y_raw);

        if (strcmp(direction, "Cima") == 0) {
            count++;
        } else if (strcmp(direction, "Baixo") == 0 && count > 0) {
            count--;
        }

        if (button_pressed(BUTTON_PIN)) {
            if (!counter_paused) {
                counter_paused = true;
                saved_count = count;
            } else {
                counter_paused = false;
                count = 0;
            }
            sleep_ms(200);
        }
        if (counter_paused && buttons_pressed(BUTTON1_PIN, BUTTON2_PIN)) {
            display_clear(ssd);
            snprintf(temp, sizeof(temp), "Max: %d", saved_count);
            ssd1306_draw_string(ssd, 5, 15, temp);
            ssd1306_draw_string(ssd, 5, 30, "Time a | Time b"); 
            render_on_display(ssd, &frame_area);
            sleep_ms(2000); 
            break; 
        }

        display_clear(ssd);
        display_update(ssd, count, counter_paused, saved_count);
        render_on_display(ssd, &frame_area);

        sleep_ms(100);
    }
    partida_loop(ssd, &frame_area, saved_count);

    return 0;
}
