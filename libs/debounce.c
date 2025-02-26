#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "definicoes.h"

// Variáveis globais
volatile bool flag_button_a = false;//Sinalizam pressionamento dos botoes
volatile bool flag_button_joy = false;//Sinalizam pressionamento dos botoes
volatile uint64_t ultimo_botao_a = 0; //Armazenam o ultimo tempo de pressionamento para debounce
volatile uint64_t ultimo_botao_joy = 0; //Armazenam o ultimo tempo de pressionamento para debounce
int contador = 0; // Contador de 0 a 9


// --- INTERRUPÇÃO E DEBOUNCE --- //
void gpio_callback(uint gpio, uint32_t events) {
    uint64_t agora = time_us_64() / 1000; // Converte para ms

//Verifica se o tempo desde a ultima ativação é maior que o intervalo de debounce_delay_ms
    if (gpio == BUTTON_PIN_A && (agora - ultimo_botao_a) > DEBOUNCE_DELAY_MS) {
        flag_button_a = true;//flag para sinalizar pressionamento do botão a
        ultimo_botao_a = agora; //Atualiza o ultimo tmpo registrado do botao A com tempo atual
    }
    //Verifica o tempo desde a ultima ativação é maio que o intervalo de debounce_delay_ms

    else if (gpio == LED_GREEN_PIN && (agora - ultimo_botao_joy) > DEBOUNCE_DELAY_MS) {
        flag_button_joy = true;//flag para sinalizar pressionamento do botão b
        ultimo_botao_joy = agora; //Atualiza o ultimo tmpo registrado do botao A com tempo atual
    }
    }
