#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define BTN_A 5
#define BTN_B 6
#define JOYSTICK_Y 27
#define ADC_CHANNEL_0 0

static volatile int o2 = 10;
static volatile float ph = 7.2;
static volatile uint joystick_Y_value;

bool aerador_ON = false;
bool produtos_pH_ON = false;

void setup(){
    stdio_init_all();
    adc_init();
    adc_gpio_init(JOYSTICK_Y);

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

bool aerador_ligado(struct repeating_timer *t){ // enquanto o o2 estiver abaixo de 10 e o aerador estiver ligado, aumentara o o2
    if(aerador_ON && o2 < 10){
        o2 += 1;
    }
    return 1;
}

bool ligar_aerador(struct repeating_timer *t){ //Ao apertar o botao A e caso o valor esteja abaixo de 6, liga o aerador
    if(!aerador_ON){
        if((!gpio_get(BTN_A) && o2 <= 5) || o2 < 1){
            printf("\n");
            if(o2 <= 1){
                printf("Nível de O2 critico, sistema de segurança ativado.\n");
            }
            aerador_ON = true;
            printf("=== LIGANDO AERADORES ===\n");
        }
    }else if(aerador_ON){
        if(!gpio_get(BTN_B) || o2 >= 10){
            printf("\n");
            printf("=== DESLIGANDO AERADORES ===\n");
            aerador_ON = false;
        }
    }
    return 1;
}

bool ajustando_ph(struct repeating_timer *t){ // diminui ou aumenta o ph, corrigindo-o
    if(produtos_pH_ON){
        if(ph < 7.0){
            ph += 0.1;
        } else if(ph > 8.0){
            ph -= 0.1;
        }
    }
    return 1;
}

bool ajustar_ph(struct repeating_timer *t){ //Ao movimentar o anagolico corrige o nivel ph, tanto aumentando quanto diminuindo
    if (produtos_pH_ON && (ph > 7.0 && ph < 8.0)) {
        printf("\n");
        printf("=== Produtos fizeram efeito, pH estabilizado ===\n");
        produtos_pH_ON = false;
    } else if (!produtos_pH_ON) {
        if (joystick_Y_value == 4 && ph >= 8.6) { // caso os valores de pH estejam altos é necessário colocar o joystick pra cima
            printf("\n");
            printf("=== Adicionando produtos para diminuir o pH ===\n"); 
            produtos_pH_ON = true;
        } else if (joystick_Y_value == 0 && ph <= 6.4) { // caso os valores de pH estejam baixos é necessário colocar o joystick pra baixo
            printf("\n");
            printf("=== Adicionando produtos para aumentar o pH ===\n");
            produtos_pH_ON = true;
        } else if (ph <= 5.0 || ph >= 9.5) {
            printf("\n");
            printf("Nível de pH crítico, sistema de segurança ativado.\n");
            produtos_pH_ON = true;
        }
    }
    return 1;
}

bool parametros(struct repeating_timer *t){ //Simula sensores de o2 e ph, mostrando seus respectivos valores
    if(!aerador_ON){
        o2 = o2 - 1 + rand() % 2;
    }
    if(!produtos_pH_ON){
       bool aumenta =  0;//rand() % 2;
       if(aumenta){
        ph = ph + 0.4;  
       } else{
        ph = ph - 0.4;
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
    setup();
    const int tempo = 1000; // tempo para gerar os dados e mostrar os mesmos

    struct repeating_timer timer_parametros;
    add_repeating_timer_ms(tempo, parametros, NULL, &timer_parametros);

    struct repeating_timer timer_ligar_aerador;
    add_repeating_timer_ms(100, ligar_aerador, NULL, &timer_ligar_aerador);

    struct repeating_timer timer_aerador_ligado;
    add_repeating_timer_ms(tempo, aerador_ligado, NULL, &timer_aerador_ligado);

    struct repeating_timer timer_ajustar_ph;
    add_repeating_timer_ms(200, ajustar_ph, NULL, &timer_ajustar_ph);

    struct repeating_timer timer_ajustando_ph;
    add_repeating_timer_ms(tempo, ajustando_ph, NULL, &timer_ajustando_ph);

    while (true){
        adc_select_input(ADC_CHANNEL_0);
        joystick_Y_value = adc_read() / 1000;
        //tight_loop_contents();
    }
}
