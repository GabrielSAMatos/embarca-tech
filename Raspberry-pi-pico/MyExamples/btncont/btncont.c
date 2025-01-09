#include <stdio.h>
#include "pico/stdlib.h"

#define LED_R_PIN 13
#define LED_G_PIN 11
#define LED_B_PIN 12
#define BTN_A 5
#define BTN_B 6

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

    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);
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

void order(int cont){
    if(cont <= 5){
        turnOn(LED_R_PIN);
    } else if(cont > 5 && cont <= 10) {
        turnOn(LED_G_PIN);
    } else if(cont > 10){
        turnOn(LED_B_PIN);
    } 
}

void isPressed(int btn){
    while (true)
    {
        if(gpio_get(btn)){
            break;
        }
        if (!gpio_get(BTN_A) && !gpio_get(BTN_B)){
            turnOn(1);
            cont = 0;
        }   
    }
    
}

int main(){
    set();
    cont = 0;
    while(true){
        sleep_ms(50);
        if (!gpio_get(BTN_A) && !gpio_get(BTN_B)){
            turnOn(1);
            cont = 0;
        }
        else if (!gpio_get(BTN_A)){
            cont++;
            order(cont);
            isPressed(BTN_A);
        }
        else if (!gpio_get(BTN_B)){
            cont--;
            order(cont);
            isPressed(BTN_B);

            if(cont < 0){
                cont = 0;
            }           
        }
        else{
            turnOn(0);
        }
    }
}