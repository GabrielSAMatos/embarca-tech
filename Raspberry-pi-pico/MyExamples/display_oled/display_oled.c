#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <string.h>
#include <ctype.h>
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"

#define BTN_A 5
#define BTN_B 6
#define JOYSTICK_Y 27
#define JOYSTICK_BTN 22
#define ADC_CHANNEL_0 0

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

static volatile int o2 = 10;
static volatile float ph = 7.2;
static volatile uint joystick_Y_value;
static volatile uint cont_encerrar = 0;

bool aerador_ON = false;
bool produtos_pH_ON = false;
bool escrever_OLED = false;

int gcvt(); //Declarando antes da main pra parar de dar o erro: implicit declaration of function

void setup(){
    stdio_init_all();
    adc_init();
    adc_gpio_init(JOYSTICK_Y);

    gpio_init(JOYSTICK_BTN);
    gpio_set_dir(JOYSTICK_BTN, GPIO_IN);
    gpio_pull_up(JOYSTICK_BTN);

    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);

    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);

    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    ssd1306_init();
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

void ajustando_O2(){ // enquanto o o2 estiver abaixo de 10 e o aerador estiver ligado, aumentara o o2
    if(aerador_ON && o2 <= 10){
        o2 += 1;
    }
}

void ajustando_ph(){ // diminui ou aumenta o ph, corrigindo-o
    if(produtos_pH_ON){
        if(ph < 7.0){
            ph += 0.1;
        } else if(ph > 8.0){
            ph -= 0.1;
        }
    }
}

bool ajustar_O2(struct repeating_timer *t){ //Ao apertar o botao A e caso o valor esteja abaixo de 6, liga o aerador
    if(!aerador_ON){
        if((!gpio_get(BTN_A) && o2 <= 5) || o2 <= 1){
            printf("\n");
            if(o2 <= 1){
                printf("Nível de O2 critico, sistema de segurança ativado.\n");
            }
            aerador_ON = true;
            escrever_OLED = true;
            printf("* LIGANDO AERADORES *\n");
        }
    }else if(aerador_ON){
        if((!gpio_get(BTN_B) && o2 > 2) || o2 >= 10){
            printf("\n");
            printf("* DESLIGANDO AERADORES *\n");
            aerador_ON = false;
        }
    }
    return 1;
}

bool ajustar_pH(struct repeating_timer *t){ //Ao movimentar o anagolico corrige o nivel ph, tanto aumentando quanto diminuindo
    if (produtos_pH_ON && (ph > 7.0 && ph < 8.0)) {
        printf("\n");
        printf("> Produtos fizeram efeito, pH OK *\n");
        produtos_pH_ON = false;
    } else if (!produtos_pH_ON) {
        if (joystick_Y_value == 4 && ph >= 8.6) { // caso os valores de pH estejam altos é necessário colocar o joystick pra cima
            printf("\n");
            printf("* Adicionando produtos para diminuir o pH *\n"); 
            produtos_pH_ON = true;
            escrever_OLED = true;
        } else if (joystick_Y_value == 0 && ph <= 6.4) { // caso os valores de pH estejam baixos é necessário colocar o joystick pra baixo
            printf("\n");
            printf("* Adicionando produtos para aumentar o pH *\n");
            produtos_pH_ON = true;
            escrever_OLED = true;
        } else if (ph <= 5.0 || ph >= 9.5) {
            printf("\n");
            printf("pH crítico, sistema de segurança ativado.\n");
            produtos_pH_ON = true;
            escrever_OLED = true;
        }
        
    }

    return 1;
}

bool parametros(struct repeating_timer *t){ //Simula sensores de o2 e ph, mostrando seus respectivos valores
    if(!aerador_ON){
        o2 = o2 - 1 + rand() % 2;
    }
    if(!produtos_pH_ON){
       bool aumenta =  1;//rand() % 2;
       if(aumenta){
        ph = ph + 0.4;  
       } else{
        ph = ph - 0.4;
       }
    }

    ajustando_O2();
    ajustando_ph();

    printf("\n\n\n");
    printf("==============================\n");
    printf("Valor de O2: %d.              \n", o2);
    printf("Valor de pH: %.1f.            \n", ph);
    printf("------------------------------\n");
    niveis_de_O2(o2);
    niveis_de_pH(ph);
    printf("==============================\n");
    cont_encerrar++;
    escrever_OLED = true;

    return 1;
}


int main(){
    setup();
    const int tempo = 3000; // tempo para gerar os dados e mostrar os mesmos
    const int ciclos = 20; //quantidade de dados para serem gerados

    struct repeating_timer timer_parametros;
    add_repeating_timer_ms(tempo, parametros, NULL, &timer_parametros);

    struct repeating_timer timer_ajustar_O2;
    add_repeating_timer_ms(100, ajustar_O2, NULL, &timer_ajustar_O2);

    struct repeating_timer timer_ajustar_pH;
    add_repeating_timer_ms(200, ajustar_pH, NULL, &timer_ajustar_pH);

// ============= INICIO DA AREA DO OLED =============
    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);

    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);

    char *text_oled[] = {"","","","","","","",""};
    char o2_str[] = "";
    char ph_str[] = "";
    char o2_content[10] = "O2-";
    char ph_content[10] = "PH-";
    text_oled[0] = "   PARAMETROS";
    text_oled[6] = "AERADORES OFF";
    text_oled[7] = "PRODUTOS PH OFF";

    
    sprintf(o2_str, "%d", o2);
    strncpy(&o2_content[3], o2_str, 2); //Concatenando, tudo certo
    //memcpy(o2_content + strlen(o2_content), o2_str, strlen(o2_str) + 2); //outro modo de fazer a mesma coisa
    //strcat(o2_content, o2_str); // A concatenacao é feita mas buga o oled
    text_oled[3] = o2_content;

    //snprintf(ph_str, sizeof(ph_str), "%.1f", ph);
    gcvt(ph, 2, ph_str);
    strncpy(&ph_content[3], ph_str, 3);
    text_oled[4] = ph_content;

    int y = 0;
    for (uint i = 0; i < count_of(text_oled); i++)
    {
        ssd1306_draw_string(ssd, 0, y, text_oled[i]);
        y += 8;
    }
    render_on_display(ssd, &frame_area);
// ============= FIM DA AREA DO OLED =============


    while (true){
        if(cont_encerrar >= ciclos || (!gpio_get(BTN_A) && !gpio_get(BTN_B))){
            printf("    =================\n");
            printf("      FIM DO CICLO\n");
            printf("        ME POE NA \n");
            printf("     RESIDENCIA IFCE\n");
            printf("    =================\n");
            
            memset(ssd, 0, ssd1306_buffer_length);
            render_on_display(ssd, &frame_area);
            break;
        }

        if(escrever_OLED){ //limpa o oled e escreve no mesmo

            memset(ssd, 0, ssd1306_buffer_length);
            render_on_display(ssd, &frame_area);

            sprintf(o2_str, "%d", o2);
            strncpy(&o2_content[3], o2_str, 2); 
            text_oled[3] = o2_content;

            gcvt(ph, 4, ph_str);
            strncpy(&ph_content[3], ph_str, 3);
            text_oled[4] = ph_content;

            text_oled[6] = "AERADORES OFF";
            text_oled[7] = "PRODUTOS PH OFF";

            if(aerador_ON){
                text_oled[6] = "AERADORES ON ";
            }
            if(produtos_pH_ON){
                text_oled[7] = "PRODUTOS PH ON ";
            }

            y = 0;
            for (uint i = 0; i < count_of(text_oled); i++)
            {
                ssd1306_draw_string(ssd, 0, y, text_oled[i]);
                y += 8;
            }
            render_on_display(ssd, &frame_area);

            escrever_OLED = false; 
        }

        adc_select_input(ADC_CHANNEL_0);
        joystick_Y_value = adc_read() / 1000;
    }
}

