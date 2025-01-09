#include <stdio.h>
#include "pico/stdlib.h"

#define LED_R_PIN 13
#define LED_G_PIN 11
#define LED_B_PIN 12
#define BTN_A 5

int cont;

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

void isPressed(int btn){
    while (true){
        if(gpio_get(btn)){
            break;
        }   
    }  
}

void turnOn(int color) {
    gpio_put(LED_R_PIN, 0);
    gpio_put(LED_G_PIN, 0);
    gpio_put(LED_B_PIN, 0);
    switch (color)
    {
    case LED_R_PIN:
        gpio_put(LED_R_PIN, 1); 
        break;
    case LED_G_PIN:
        gpio_put(LED_G_PIN, 1); 
        break;
    case LED_B_PIN:
        gpio_put(LED_B_PIN, 1); 
        break;
    case 1:
        gpio_put(LED_R_PIN, 1); 
        gpio_put(LED_G_PIN, 1); 
        gpio_put(LED_B_PIN, 1); 
        break;;
    default:
        break;
    }
}

void ifcont(){
    if(cont == 0){
        turnOn(1);
    } else if(cont <= 3){
        turnOn(LED_R_PIN);
    } else if(cont <= 6){
        turnOn(LED_G_PIN);
    } else {
        turnOn(LED_B_PIN);
    }
}

void increase(){
    while (true)
    {
        printf("%d", cont);
        ifcont();
        sleep_ms(1000);
        turnOn(0);
        sleep_ms(1000);
        if(cont == 9){
            cont = 0;
            continue;
        }
        cont++;
    }
}

int main(){
    set();
    stdio_init_all();

    while (true){
        if(!gpio_get(BTN_A)){
            isPressed(BTN_A);
            increase();
        }
    }
}