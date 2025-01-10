#include <stdio.h>
#include "pico/stdlib.h"

#define LED_R_PIN 13
#define LED_G_PIN 11
#define LED_B_PIN 12
#define BTN_A 5
#define BTN_B 6

char password[] = "AABA";
char try[] = "****";

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

void isPressed(int btn){
    while (true)
    {
        if(gpio_get(btn)){
            break;
        }
        if (!gpio_get(BTN_A) && !gpio_get(BTN_B)){
            turnOn(1);           
            break;
        }   
    }  
}

void wrong(){
    for (int i = 0; i < 3; i++){
        turnOn(LED_R_PIN);
        sleep_ms(200);
        turnOn(0);
        sleep_ms(200);
    }
}

void right(){
        turnOn(LED_G_PIN);
        sleep_ms(200);
        turnOn(0);
}

void correct(){
    for (int i = 0; i < 7; i++){
        turnOn(1);
        sleep_ms(200);
        turnOn(0);
        sleep_ms(200);
    }    
}

void checkPassword(){
    int i = 0;
    while (true){
        sleep_ms(50);
        if(!gpio_get(BTN_A)){
            turnOn(LED_G_PIN);
            isPressed(BTN_A);
            turnOn(0);
            try[i] = 'A';
            i++;
        } else if(!gpio_get(BTN_B)){
            turnOn(LED_B_PIN);
            isPressed(BTN_B);
            turnOn(0);
            try[i] = 'B';
            i++;
        }

        if(password[0] == try[0] && password[1] == try[1] && password[2] == try[2] && password[3] == try[3]){
            sleep_ms(300);
            turnOn(1);
            sleep_ms(1000);
            turnOn(0);
            try[3] = '*';
            break;
        }
        if(i > 3){
            sleep_ms(300);
            i = 0;
            turnOn(LED_R_PIN);
            sleep_ms(1000);
            turnOn(0);
        } 
    }
}

int main(){
    set();   
    while(true){
        if(!gpio_get(BTN_A)){
            gpio_put(LED_G_PIN, 1);
            gpio_put(LED_B_PIN, 1);
            sleep_ms(500);
            isPressed(BTN_A);
            turnOn(0);
            sleep_ms(50);
            checkPassword();
        }
    }
}