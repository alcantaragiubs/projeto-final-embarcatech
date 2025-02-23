#include "botao.h"

void iniciaBotao(uint pinBotao) {
    gpio_init(pinBotao);
    gpio_set_dir(pinBotao, GPIO_IN);
    gpio_pull_up(pinBotao);
}

bool pressionaBotao(uint pinBotao) {
    return gpio_get(pinBotao) == 0;
}


