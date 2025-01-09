#include <stdio.h>
#include "pico/stdlib.h"

#define LED_R_PIN 13
#define LED_G_PIN 11
#define LED_B_PIN 12
#define BTN_A 5


void set(){
    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);

    gpio_init(LED_G_PIN);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);

    gpio_init(LED_B_PIN);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);

    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);
}

void trafficLight(){
    while (true){
        gpio_put(LED_G_PIN, 1); 
        sleep_ms(3000);
        gpio_put(LED_R_PIN, 1); 
        sleep_ms(1000);
        gpio_put(LED_G_PIN, 0); 
        sleep_ms(2000);
        gpio_put(LED_R_PIN, 0); 

    }
}

int main(){
    set();
    while (true){
        if(!gpio_get(BTN_A)){
            trafficLight();
        }
    }
}