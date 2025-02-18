
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "definicoes.h"

//Variaveis globais
volatile uint64_t ultimo_registro = 0; //Armazena o ultimo momento em que o LED foi ligado/desligado
volatile bool led_state = false; //Controla o estado do LED atual

void numero_0(){
    const uint led_sequence[] = {24,23,22,21,20,15,10,5,0,1,2,3,4,9,14,19};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);

    for (int i = 0; i < led_count; i++) {
        npSetLED(led_sequence[i], 100, 0, 0);
    }
    npWrite();
}
void numero_1(){
    const uint led_sequence[] = {13, 17, 21, 18, 11, 8, 1};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 0, 0, 100);
        }
    // Envia as mudanças para os LEDs
    npWrite();

}
void numero_2(){
    
    // Define as posições dos LEDs que formarão o quadrado
    const uint led_sequence[] = {24,23,22,21,20,19,10,11,12,13,14,5,4,3,2,1,0};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);

    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 0, 100, 0);
        }
    

    // Envia as mudanças para os LEDs
    npWrite();
}
void numero_3(){
    
    // Define as posições dos LEDs que formarão o quadrado
    const uint led_sequence[] = {24,23,22,21,20,19,10,11,12,13,14,9,4,3,2,1,0};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);

    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 100, 0, 0);
        }
    

    // Envia as mudanças para os LEDs
    npWrite();
}
void numero_4(){
    const uint led_sequence[] = {23,21,16,18,13,11,12,8,1};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);

    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i],0, 0, 100);
        }
    // Envia as mudanças para os LEDs
    npWrite();
}
void numero_5(){
    const uint led_sequence[] = {24,23,22,21,20,15,14,13,12,11,10,9,4,3,2,1,0};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);

    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 0, 100, 0);
        }
    

    // Envia as mudanças para os LEDs
    npWrite();
}
void numero_6(){
        const uint led_sequence[] = {24,23,22,21,20,15,14,13,12,11,10,9,0,1,2,3,4,5};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);

    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 100, 0, 0);
        }
    

    // Envia as mudanças para os LEDs
    npWrite();
}
void numero_7(){
        const uint led_sequence[] = {24,23,22,21,20,19,10,11,12,13,14,9,0};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);

    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 0, 0, 100);
        }
    

    // Envia as mudanças para os LEDs
    npWrite();
}
void numero_8(){
    const uint led_sequence[] = {24,23,22,21,20,15,14,13,12,11,10,9,5,4,3,2,1,0,19};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);

    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 0, 100, 0);
        }
    

    // Envia as mudanças para os LEDs
    npWrite();
}
void numero_9(){
        const uint led_sequence[] = {24,23,22,21,20,19,10,11,12,13,14,15,9,0,1,2,3,4};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);


    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 100, 0, 0);
        }
    

    // Envia as mudanças para os LEDs
    npWrite();
}

// Função chamada quando o botão é pressionado
void mostrar_numero(uint8_t numero) {
    npClear(); // Limpa a matriz antes de mostrar o número
    switch (numero) {
        case 0: numero_0(); break;
        case 1: numero_1(); break;
        case 2: numero_2(); break;
        case 3: numero_3(); break;
        case 4: numero_4(); break;
        case 5: numero_5(); break;
        case 6: numero_6(); break;
        case 7: numero_7(); break;
        case 8: numero_8(); break;
        case 9: numero_9(); break;
    }
    npWrite(); // Atualiza os LEDs
}
// Função chama o led vermelho
void led_vermelho() {
    uint64_t agora = time_us_64(); //Armazena o tempo atual desde a inicialização
    if (agora - ultimo_registro >= 100000) { // 100 ms em μs
        led_state = !led_state;//Alterna o estado do LED a cada 100ms
        gpio_put(GPIO_PIN_RED, led_state); //Altera o estado fisico do pino GPIO
        ultimo_registro = agora;//Atualiza o ultimo registro com o tempo atual, reiniciando a contagem
    }
}