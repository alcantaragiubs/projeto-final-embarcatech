#include "button.h"

void button_init(uint button_pin) {
    gpio_init(button_pin);
    gpio_set_dir(button_pin, GPIO_IN);
    gpio_pull_up(button_pin);
}

bool button_pressed(uint button_pin) {
    return gpio_get(button_pin) == 0;
}

bool buttons_pressed(uint button1_pin, uint button2_pin) {
    return (gpio_get(button1_pin) == 0 && gpio_get(button2_pin) == 0);
}

