#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

const uint YELLOW_PIN = 12;
const uint GREEN_PIN = 11;
const uint RED_PIN = 13;
const uint TIME_DELAY = 3000;

uint ESTADO_ATUAL = 0;

bool repeating_time_callback(struct repeating_timer *t){
    if (ESTADO_ATUAL == 0){
        gpio_put(RED_PIN, false);
        gpio_put(GREEN_PIN, true);
        ESTADO_ATUAL = 1;
    } else if (ESTADO_ATUAL == 1){
        gpio_put(GREEN_PIN, false);
        gpio_put(YELLOW_PIN, true);
        ESTADO_ATUAL = 2;
    } else {
        gpio_put(YELLOW_PIN, false);
        gpio_put(RED_PIN, true);
        ESTADO_ATUAL = 0;
    }
}

int main()
{
    stdio_init_all(); // Inicializar stdio
    // Inicializações dos Pinos:
    gpio_init(GREEN_PIN);
    gpio_init(YELLOW_PIN);
    gpio_init(RED_PIN);
    // Definição dos pinos como saída:
    gpio_set_dir(GREEN_PIN, true);
    gpio_set_dir(YELLOW_PIN, true);
    gpio_set_dir(RED_PIN, true);
    // Inicia o semáforo vermelho
    gpio_put(RED_PIN, true);
    gpio_put(YELLOW_PIN, false);
    gpio_put(GREEN_PIN, false);

    struct repeating_timer timer;
    add_repeating_timer_ms(TIME_DELAY, repeating_time_callback, NULL, &timer);

    while (true) {
        if (ESTADO_ATUAL == 0){
            printf("Semáforo no vermelho, aguarde!\n");
        } else if (ESTADO_ATUAL == 1){
            printf("Semáforo no verde, pode avançar!\n");
        } else{
            printf("Semáforo no amarelo, atenção e reduza!\n");
        }
        sleep_ms(1000);
    }
}
