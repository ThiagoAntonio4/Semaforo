#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h" 

#define LED_VERMELHO 13
#define LED_AMARELO 12
#define LED_VERDE 11

int ledAtual = LED_VERMELHO;

void init_gpios(){
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
}

bool repeating_timer_callback(struct repeating_timer *t){
    for(int i = LED_VERMELHO; i >= LED_VERDE; i--){
        if(i == ledAtual){
            gpio_put(i, 1);
        }
        else{
            gpio_put(i, 0);
        }
    }
    ledAtual--;
    if(ledAtual < LED_VERDE){
        ledAtual = LED_VERMELHO;
    }
    return true;
}

int main()
{
    int tempoProximo = 3;
    stdio_init_all();
    init_gpios();
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);    

    while (true) {
        tempoProximo == 1 ? printf("Tempo para próxima mudança de sinal: %d segundo\n", tempoProximo) : printf("Tempo para próxima mudança de sinal: %d segundos\n", tempoProximo);
        tempoProximo--;
        if(tempoProximo < 1){
            tempoProximo = 3;
        }
        sleep_ms(1000);
    }
}
