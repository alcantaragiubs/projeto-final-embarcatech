#include <stdio.h>
#include "pico/stdlib.h"
#include "configuracao.h"  
#include "partida.h"

int main() {
    stdio_init_all();

    uint8_t ssd[ssd1306_buffer_length];
    limpaDisplay(ssd);
    struct render_area frame_area;
    int saved_count = 0;
    configuracaoa(&frame_area, ssd);
    
    iniciaPartida(&saved_count, ssd, &frame_area);

    joga(ssd, &frame_area, &saved_count);

    return 0;
}