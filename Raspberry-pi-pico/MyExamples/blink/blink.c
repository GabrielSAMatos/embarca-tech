//biblioteca de entrada e saida
#include <stdio.h>
//biblioteca guarda-chuva, possui varias bibliotecas para acessar pinos I/O, temporizadores etc
#include "pico/stdlib.h"

//define que sera usado o pino GP12
const uint led_pin_red = 12;

int main(){
    uint a = 0;

    //os dois configuram o pino GP12 como uma saida
    gpio_init(led_pin_red);
    gpio_set_dir(led_pin_red, GPIO_OUT);
    //faz a configuracao basica de entrada e saida
    stdio_init_all();
    
    while(true){
        gpio_put(led_pin_red, true);
        sleep_ms(1800);
        gpio_put(led_pin_red, false);
        sleep_ms(200);

        printf("%d\r\n", a);
        a++;
    }
}