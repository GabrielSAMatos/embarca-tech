//biblioteca de entrada e saida
#include <stdio.h>
//biblioteca guarda-chuva, possui varias bibliotecas para acessar pinos I/O, temporizadores etc
#include "pico/stdlib.h"

//define o valor das cores que irao ser usadas no led
// 11 verde, 12 azul, 13 vermelho
#define LED_R_PIN 13
#define LED_G_PIN 11
#define LED_B_PIN 12


void blink(int color){
    gpio_put(color, true);
    sleep_ms(1000);
    gpio_put(color, false);
    sleep_ms(1000);
}

int main(){
    gpio_init(LED_R_PIN); //Inicializa o LED
    gpio_set_dir(LED_R_PIN, GPIO_OUT); //Define a direcao do LED como saida
    gpio_init(LED_G_PIN);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);
    gpio_init(LED_B_PIN);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);
    
    //faz a configuracao basica de entrada e saida
    stdio_init_all();
    
    while(true){
        blink(LED_R_PIN);
        blink(LED_G_PIN);
        blink(LED_B_PIN);

        // da pra brincar com as cores, ativando mais de uma ao mesmo tempo, no caso as 3 seria a cor branca
        // gpio_put(LED_R_PIN, true);
        // gpio_put(LED_G_PIN, true);
        // gpio_put(LED_B_PIN, true);
    }
}