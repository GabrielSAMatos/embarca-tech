//biblioteca de entrada e saida
#include <stdio.h>
//biblioteca guarda-chuva, possui varias bibliotecas para acessar pinos I/O, temporizadores etc
#include "pico/stdlib.h"

//define que sera usado o pino GP12
const uint led_pin_blue = 12;

int main(){
    uint a = 0;

    //os dois configuram o pino GP12 como uma saida
    gpio_init(led_pin_blue);
    gpio_set_dir(led_pin_blue, GPIO_OUT);
    //faz a configuracao basica de entrada e saida
    stdio_init_all();
    
    while(true){
        gpio_put(led_pin_blue, true);
        sleep_ms(1800);
        gpio_put(led_pin_blue, false);
        sleep_ms(200);
        a++;
        printf("%d\r\n", a);
        if(a == 5){
            break;
        }
    }
    printf("digita ai o a: ");
    scanf("%d", &a);
    printf("its over baby\n");
    printf("toma aqui o a: %d", a);

}