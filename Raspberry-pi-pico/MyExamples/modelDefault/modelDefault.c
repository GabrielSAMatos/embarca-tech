#include <stdio.h>
#include "pico/stdlib.h"


#define LED_R_PIN 13
#define LED_G_PIN 11
#define LED_B_PIN 12
#define BTN_A 5
#define BTN_B 6
#define BTN_JOYSTICK 22
#define Buzzer_A 10
#define Buzzer_B 21


void set(){
    stdio_init_all();
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

    gpio_init(BTN_JOYSTICK);
    gpio_set_dir(BTN_JOYSTICK, GPIO_IN);
    gpio_pull_up(BTN_JOYSTICK);

    
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

int main(){
    set();
    
}