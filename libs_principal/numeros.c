
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

        void numero_a(){
            const uint led_sequence[] = {24,23,22,21,20,15,14,5,4,13,12,11,10,9,0,19};
        const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
        
        
        // Acende os LEDs na sequência definida
        for (int i = 0; i < led_count; i++) {
                // Caso contrário, acende com cor vermelha
                npSetLED(led_sequence[i], 100, 0, 0);
            }
             // Envia as mudanças para os LEDs
    npWrite();
        }
            void numero_b(){
                const uint led_sequence[] = {24,15,14,13,12,11,10,9,0,1,2,3,4,5};
            const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
            
            
            // Acende os LEDs na sequência definida
            for (int i = 0; i < led_count; i++) {
                    // Caso contrário, acende com cor vermelha
                    npSetLED(led_sequence[i], 100, 0, 0);
                }
                 // Envia as mudanças para os LEDs
    npWrite();
            }
                void numero_c(){
                    const uint led_sequence[] = {20,21,22,23,24,15,14,5,4,3,2,1,0};
                const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
                
                
                // Acende os LEDs na sequência definida
                for (int i = 0; i < led_count; i++) {
                        // Caso contrário, acende com cor vermelha
                        npSetLED(led_sequence[i], 100, 0, 0);
                    }
                     // Envia as mudanças para os LEDs
    npWrite();
                }

                    void numero_d(){
                        const uint led_sequence[] = {20,19,10,9,0,1,2,3,4,5,14,13,12,11};
                    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
                    
                    
                    // Acende os LEDs na sequência definida
                    for (int i = 0; i < led_count; i++) {
                            // Caso contrário, acende com cor vermelha
                            npSetLED(led_sequence[i], 100, 0, 0);
                        }
                         // Envia as mudanças para os LEDs
    npWrite();
                    }

                        void numero_e(){
                            const uint led_sequence[] = {12,24,23,22,21,20,19,10,11,13,13,14,15,1,0,2,3,4,5};
                        const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
                        
                        
                        // Acende os LEDs na sequência definida
                        for (int i = 0; i < led_count; i++) {
                                // Caso contrário, acende com cor vermelha
                                npSetLED(led_sequence[i], 100, 0, 0);
                        } // Envia as mudanças para os LEDs
    npWrite();}

                        void numero_f(){
                            const uint led_sequence[] = {24,23,22,21,20,15,14,13,12,11,10,5,4};
                        const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
                        
                        
                        // Acende os LEDs na sequência definida
                        for (int i = 0; i < led_count; i++) {
                                // Caso contrário, acende com cor vermelha
                                npSetLED(led_sequence[i], 100, 0, 0);
                        } // Envia as mudanças para os LEDs
    npWrite();}

                        void numero_g(){
                            const uint led_sequence[] = {24,23,22,21,20,15,16,17,18,19,10,9,0,1,2,7};
                        const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
                        
                        
                        // Acende os LEDs na sequência definida
                        for (int i = 0; i < led_count; i++) {
                                // Caso contrário, acende com cor vermelha
                                npSetLED(led_sequence[i], 100, 0, 0);
                        } // Envia as mudanças para os LEDs
    npWrite();}

                        void numero_h(){
                            const uint led_sequence[] = {24,15,14,5,4,6,7,8,9,0};
                        const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
                        
                        
                        // Acende os LEDs na sequência definida
                        for (int i = 0; i < led_count; i++) {
                                // Caso contrário, acende com cor vermelha
                                npSetLED(led_sequence[i], 100, 0, 0);
                        } // Envia as mudanças para os LEDs
    npWrite();}

                        void numero_i(){
                            const uint led_sequence[] = {12,7,2,22};
                        const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
                        
                        
                        // Acende os LEDs na sequência definida
                        for (int i = 0; i < led_count; i++) {
                                // Caso contrário, acende com cor vermelha
                                npSetLED(led_sequence[i], 100, 0, 0);
                        } // Envia as mudanças para os LEDs
    npWrite();}

                        void numero_j(){
                        const uint led_sequence[] = {24,23,22,21,20,18,11,8,1,2,3,6};
                        const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
                        
                        
                        // Acende os LEDs na sequência definida
                        for (int i = 0; i < led_count; i++) {
                                // Caso contrário, acende com cor vermelha
                                npSetLED(led_sequence[i], 100, 0, 0);
                        } // Envia as mudanças para os LEDs
    npWrite();}

                        void numero_k(){
                            const uint led_sequence[] = {23,16,13,6,3,17,21,7,1};
                            const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
                            
                            
                            // Acende os LEDs na sequência definida
                            for (int i = 0; i < led_count; i++) {
                                    // Caso contrário, acende com cor vermelha
                                    npSetLED(led_sequence[i], 100, 0, 0);
                            } // Envia as mudanças para os LEDs
    npWrite();}

                            void numero_l(){
                                const uint led_sequence[] = {24,15,14,5,4,3,2,1,0};
                                const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
                                
                                
                                // Acende os LEDs na sequência definida
                                for (int i = 0; i < led_count; i++) {
                                        // Caso contrário, acende com cor vermelha
                                        npSetLED(led_sequence[i], 100, 0, 0);
                                } // Envia as mudanças para os LEDs
    npWrite();}

    void numero_m(){
        const uint led_sequence[] = {24,15,14,5,4,16,12,18,20,19,10,9,0};
        const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
        
        
        // Acende os LEDs na sequência definida
        for (int i = 0; i < led_count; i++) {
                // Caso contrário, acende com cor vermelha
                npSetLED(led_sequence[i], 100, 0, 0);
        } // Envia as mudanças para os LEDs
npWrite();}

void numero_n(){
    const uint led_sequence[] = {24,15,14,5,4,16,12,8,0,9,10,19,20};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
    
    
    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 100, 0, 0);
    } // Envia as mudanças para os LEDs
npWrite();}

void numero_o(){
    const uint led_sequence[] = {24,23,22,21,20,19,10,9,0,1,2,3,4,5,14,15};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
    
    
    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 100, 0, 0);
    } // Envia as mudanças para os LEDs
npWrite();}

void numero_p(){
    const uint led_sequence[] = {24,23,22,21,20,19,10,11,12,13,14,15,5,4};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
    
    
    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 100, 0, 0);
    } // Envia as mudanças para os LEDs
npWrite();}

void numero_q(){
    const uint led_sequence[] = {24,23,22,21,20,19,18,17,16,15,10,9,0,8,7};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
    
    
    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 100, 0, 0);
    } // Envia as mudanças para os LEDs
npWrite();}

void numero_r(){
    const uint led_sequence[] = {24,23,22,21,20,19,10,11,12,13,14,15,5,4,7,0};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
    
    
    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 100, 0, 0);
    } // Envia as mudanças para os LEDs
npWrite();}

void numero_s(){
    const uint led_sequence[] = {24,23,22,21,20,15,14,13,12,11,10,9,4,3,2,1,0};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
    
    
    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 100, 0, 0);
    } // Envia as mudanças para os LEDs
npWrite();}

void numero_t(){
    const uint led_sequence[] = {24,23,22,21,20,17,12,7,2};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
    
    
    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 100, 0, 0);
    } // Envia as mudanças para os LEDs
npWrite();}

void numero_u(){
    const uint led_sequence[] = {24,15,14,5,4,3,2,1,0,9,10,19,20};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
    
    
    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 100, 0, 0);
    } // Envia as mudanças para os LEDs
npWrite();}

void numero_v(){
    const uint led_sequence[] = {24,15,14,6,2,8,10,19,20};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
    
    
    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 100, 0, 0);
    } // Envia as mudanças para os LEDs
npWrite();}

void numero_w(){
    const uint led_sequence[] = {24,15,14,5,4,3,7,1,0,9,10,19,20};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
    
    
    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 100, 0, 0);
    } // Envia as mudanças para os LEDs
npWrite();}

void numero_x(){
    const uint led_sequence[] = {24,16,12,8,0,4,6,12,18,20};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
    
    
    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 100, 0, 0);
    } // Envia as mudanças para os LEDs
npWrite();}

void numero_y(){
    const uint led_sequence[] = {24,15,16,17,18,19,20,10,9,0,1,2,7,11};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
    
    
    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 100, 0, 0);
    } // Envia as mudanças para os LEDs
npWrite();}

void numero_z(){
    const uint led_sequence[] = {24,23,22,21,20,18,12,6,4,3,2,1,0};
    const uint led_count = sizeof(led_sequence) / sizeof(led_sequence[0]);
    
    
    // Acende os LEDs na sequência definida
    for (int i = 0; i < led_count; i++) {
            // Caso contrário, acende com cor vermelha
            npSetLED(led_sequence[i], 100, 0, 0);
    } // Envia as mudanças para os LEDs
npWrite();}


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

void mostrar_letra(uint8_t numero){
    npClear();
    switch (numero) {
        case 0: numero_a(); break;
        case 1: numero_b(); break;
        case 2: numero_c(); break;
        case 3: numero_d(); break;
        case 4: numero_e(); break;
        case 5: numero_f(); break;
        case 6: numero_g(); break;
        case 7: numero_h(); break;
        case 8: numero_i(); break;
        case 9: numero_j(); break;
        case 10: numero_k(); break;
        case 11: numero_l(); break;
        case 12: numero_m(); break;
        case 13: numero_n(); break;
        case 14: numero_o(); break;
        case 15: numero_p(); break;
        case 16: numero_q(); break;
        case 17: numero_r(); break;
        case 18: numero_s(); break;
        case 19: numero_t(); break;
        case 20: numero_u(); break;
        case 21: numero_v(); break;
        case 22: numero_w(); break;
        case 23: numero_x(); break;
        case 24: numero_y(); break;
        case 25: numero_z(); break;
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