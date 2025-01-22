#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_R_PIN 13
#define LED_B_PIN 12
#define BTN_A 5
#define BTN_B 6

static volatile int o2 = 10;
bool led_ON = false;
bool aerador_ON = false;
absolute_time_t turn_off_time;

void set(){
    stdio_init_all();
    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);

    gpio_init(LED_B_PIN);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);

    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);

    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);
}

void niveis_de_O2(int o2){ // monitora o nivel de o2
    if(o2 > 5){
        printf("Valor de O2: %d.\n", o2);
    }else if(o2 > 2 && o2 <= 5){
        printf("Niveis de O2 abaixo do ideal, recomendado ligar os aeradores: %d. \n", o2);
    }else{
        printf("Niveis criticos de O2, ligar imediamante os aeradores: %d. \n", o2);
    }
}

bool aerador_ligado(struct repeating_timer *t){ // enquanto o o2 estiver abaixo do ideal e o aerador estiver ligado, aumentara o o2
    if(aerador_ON && o2 < 10){
        o2 += 1;
        printf("Aerador ligado, valor de O2: %d.\n", o2);
    }
    return 1;
}

bool ligar_aerador(struct repeating_timer *t){ //liga o aerador caso o o2 esteja menos igual a 5 e desliga qnd o mesmo chega a 10
    if(((!gpio_get(BTN_A) && !aerador_ON && o2 <= 5) || (o2 < 1) && !aerador_ON)){
        if(o2 < 1){
            printf("Nível muito critico, sistema de segurança ativado.\n");
        }

        aerador_ON = true;
        gpio_put(LED_B_PIN, 1);
        printf("=== LIGANDO AERADORES ===\n");
    }

    if((aerador_ON && o2 >= 10) || (!gpio_get(BTN_B) && aerador_ON)){
        printf("=== DESLIGANDO AERADORES ===\n");
        gpio_put(LED_B_PIN, 0);
        aerador_ON = false;
    }
}

bool valor_O2(struct repeating_timer *t){ //gera os valores de o2, os diminuindo ou se mantendo iguais
    if(!aerador_ON){
        o2 = o2 - 1 + rand() % 2;
        if(o2 > 10){
            o2 = 10;
        }else if(o2 < 0){
            o2 = 0;
        }
        niveis_de_O2(o2);
    }

    return 1;
}

int main(){
    set();
    struct repeating_timer timer;
    add_repeating_timer_ms(2000, valor_O2, NULL, &timer);

    struct repeating_timer timer_ligar_aerador;
    add_repeating_timer_ms(100, ligar_aerador, NULL, &timer_ligar_aerador);

    struct repeating_timer timer_aerador_ligado;
    add_repeating_timer_ms(2000, aerador_ligado, NULL, &timer_aerador_ligado);

    while (true){
        tight_loop_contents();
    }
}