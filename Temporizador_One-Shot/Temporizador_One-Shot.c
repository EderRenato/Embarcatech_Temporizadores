#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

const uint RED_PIN = 13;
const uint GREEN_PIN = 11;
const uint BLUE_PIN = 12;
const uint BUTTON_PIN = 5;

const uint TIME_DELAY = 3000;

volatile bool sequence_active = false;

int64_t desliga_vermelho_callback(alarm_id_t id, void *user_data);
int64_t desliga_azul_callback(alarm_id_t id, void *user_data);
int64_t desliga_todos_callback(alarm_id_t id, void *user_data);



bool botao_pressionado(){
    if (!gpio_get(BUTTON_PIN)){
        sleep_ms(50);
        if (!gpio_get(BUTTON_PIN)){
            return true;
        }
    }
    return false;
}

int main()
{
    stdio_init_all();
    // Inicializações dos Pinos:
    gpio_init(GREEN_PIN);
    gpio_init(BLUE_PIN);
    gpio_init(RED_PIN);
    // Definição dos pinos como saída:
    gpio_set_dir(GREEN_PIN, GPIO_OUT);
    gpio_set_dir(BLUE_PIN, GPIO_OUT);
    gpio_set_dir(RED_PIN, GPIO_OUT);
    // Inicializa o botão como entrada com pull-up ativado
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    while (true) {
        if (!sequence_active && botao_pressionado()){
            sequence_active = true;

            gpio_put(GREEN_PIN, true);
            gpio_put(BLUE_PIN, true);
            gpio_put(RED_PIN, true);

            add_alarm_in_ms(TIME_DELAY, desliga_vermelho_callback, NULL, false);
        }
        sleep_ms(100);
    }
    return 0;
}

int64_t desliga_vermelho_callback(alarm_id_t id, void *user_data){
    gpio_put(RED_PIN, false); // Desliga o vermelho
    add_alarm_in_ms(TIME_DELAY, desliga_azul_callback, NULL, false);
    return 0;
}

int64_t desliga_azul_callback(alarm_id_t id, void *user_data){
    gpio_put(BLUE_PIN, false); //Desliga o azul
    add_alarm_in_ms(TIME_DELAY, desliga_todos_callback, NULL, false);
    return 0;
}

int64_t desliga_todos_callback(alarm_id_t id, void *user_data){
    gpio_put(GREEN_PIN, false); //desliga o verde
    sequence_active = false; // Permite novo uso do botão
    return 0;
}