#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/adc.h"

#define BTN_A 5
#define BTN_B 6

uint volatile joystick_Y;
uint volatile joystick_X;

static volatile int o2 = 10;
static volatile float ph = 7.2;

bool aerador_ON = false;
bool produtos_pH_ON = false;
absolute_time_t turn_off_time;

void set(){
    stdio_init_all();
    adc_init();

    adc_gpio_init(26);
    adc_gpio_init(27);

    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);

    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);
}

void niveis_de_O2(int o2){ // monitora o nivel de o2
    if(!aerador_ON){
        if(o2 > 5){
            printf("O2 - Nível ideal.\n");
        }else if(o2 > 2 && o2 <= 5){
            printf("O2 - Nível abaixo do ideal. \n");
        }else{
            printf("O2 - Nível crítico. \n");
        }
    }else {
        printf("O2 - Aerador ligado\n", o2);
    }
}

void niveis_de_pH(float ph){ // monitora o nivel de pH
    if(!produtos_pH_ON){
        if(ph >= 6.5 && ph <= 8.5){
            printf("ph - Nível ideal.\n");
        }else if((ph >= 6.0 && ph < 6.5) || (ph > 8.5 && ph <= 9.0)){
            printf("pH - Nível não está ideal. \n");
        }else{
            printf("ph - Nível crítico. \n");
        }
    }else{
        printf("pH - Produtos fazendo efeito.\n", ph);
    }
}

bool aerador_ligado(struct repeating_timer *t){ // enquanto o o2 estiver abaixo do ideal e o aerador estiver ligado, aumentara o o2
    if(aerador_ON && o2 < 10){
        o2 += 1;
    }
    return 1;
}

bool ligar_aerador(struct repeating_timer *t){ //liga o aerador caso o o2 esteja menos igual a 5 e desliga qnd o mesmo chega a 10
    if(((!gpio_get(BTN_A) && !aerador_ON && o2 <= 5) || (o2 < 1) && !aerador_ON)){
        printf("\n");
        if(o2 < 1){
            printf("Nível de O2 critico, sistema de segurança ativado.\n");
        }
        aerador_ON = true;
        printf("=== LIGANDO AERADORES ===\n");
    }

    if((aerador_ON && o2 >= 10) || (!gpio_get(BTN_B) && aerador_ON)){
        printf("\n");
        printf("=== DESLIGANDO AERADORES ===\n");
        aerador_ON = false;
    }
}

bool ajustar_ph(struct repeating_timer *t) {
    if (produtos_pH_ON && (ph > 7.1 && ph < 7.3)) {
        printf("\n");
        printf("=== Produtos fizeram efeito, pH estabilizado ===\n");
        produtos_pH_ON = false;
    }

    if (!produtos_pH_ON) {
        if ((joystick_Y == 4 && ph <= 6.4 || ph >= 8.6) || (ph <= 5.0 || ph >= 9.5)) {
                printf("\n");
                if (ph <= 5.0 || ph >= 9.5){
                    printf("Nível de pH crítico, sistema de segurança ativado.\n");
                }
                printf("=== Adicionando Produtos do pH ===\n");
                produtos_pH_ON = true;
        }
    }

    return true;
}

bool ajustando_ph(struct repeating_timer *t){ // enquanto o o2 estiver abaixo do ideal e o aerador estiver ligado, aumentara o o2
    if(produtos_pH_ON){
        if(ph < 7.2){
            ph += 0.1;
        } else if(ph > 7.2){
            ph -= 0.1;
        }
    }
    return 1;
}

bool parametros(struct repeating_timer *t){ //gera os valores de o2, os diminuindo ou se mantendo iguais
    if(!aerador_ON){
        o2 = o2 - 1 + rand() % 2;
        if(o2 > 10){
            o2 = 10;
        }else if(o2 < 0){
            o2 = 0;
        }  
    }

    if(!produtos_pH_ON){
       bool aumenta = rand() % 2;
       if(aumenta){
        ph = ph + 0.8;  
       } else{
        ph = ph - 0.8;
       }
    }
    
    printf("\n");
    printf("=====================\n");
    printf("Valor de O2: %d.\n", o2);
    printf("Valor de pH: %.1f.\n", ph);
    printf("~~~~~~~~~~~~~~~~~~~~~\n");
    niveis_de_O2(o2);
    niveis_de_pH(ph);

    return 1;
}

int main(){
    set();
    struct repeating_timer timer_parametros;
    add_repeating_timer_ms(2000, parametros, NULL, &timer_parametros);

    struct repeating_timer timer_ligar_aerador;
    add_repeating_timer_ms(100, ligar_aerador, NULL, &timer_ligar_aerador);

    struct repeating_timer timer_aerador_ligado;
    add_repeating_timer_ms(2000, aerador_ligado, NULL, &timer_aerador_ligado);

    struct repeating_timer timer_ajustar_ph;
    add_repeating_timer_ms(100, ajustar_ph, NULL, &timer_ajustar_ph);

    struct repeating_timer timer_ajustando_ph;
    add_repeating_timer_ms(2000, ajustando_ph, NULL, &timer_ajustando_ph);

    while (true){
        adc_select_input(0);
        joystick_Y = adc_read() / 1000;
        adc_select_input(1);
        joystick_X = adc_read() / 1000;
        //tight_loop_contents();
    }
}