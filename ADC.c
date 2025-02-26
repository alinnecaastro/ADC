#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "pio_config.h"
#include "hardware/pwm.h"
#include "pico/bootrom.h"
#include "ws2812.pio.h"
#include "ssd1306.h"
#include "font.h"
#include "libs_principal/local_pwm.c"
#include "libs_principal/definicoes.h"
#include "libs_principal/debounce.c"
#include "libs_principal/numeros.c"

#include <time.h>
#include <stdlib.h>
#include "hardware/i2c.h"
#include "hardware/adc.h"

#define NUM_OBSTACULOS 3

int pos_x = WIDTH / 2;  // Posição inicial do personagem (centro)
int pos_y = HEIGHT - 10;  // Posição Y fixa (parte inferior da tela)
uint8_t border_thickness = 1;  // Espessura inicial da borda
uint8_t border_style = 0;           // Estilo da borda do display (0, 1, 2, ...)

int obstaculo_x[NUM_OBSTACULOS];
int obstaculo_y[NUM_OBSTACULOS];
int pontuacao[NUM_OBSTACULOS];  // Pontuação do jogador
bool game_active = true;  // Indica se o jogo está ativo

bool game_started = false;  // Variável para verificar se o jogo já começou
bool button_pressedd = false; // Variável para controlar o estado do botão

// Função para ler o valor do joystick
uint16_t read_joystick(uint pin) {
    adc_select_input(pin - 26);
    return adc_read();
}

//Função leitura do botao da joystick
void joystick_button_pressed() {
    static uint32_t last_press_time = 0;  // Armazena o tempo do último pressionamento
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
      
        last_press_time = current_time;  // Atualiza o tempo do último pressionamento
    }


// Função para mover o personagem com base no joystick
void mover_personagem(ssd1306_t *ssd) {
     // Leitura dos valores do joystick
     uint16_t x_value = read_joystick(JOYSTICK_X_PIN);
     uint16_t y_value = read_joystick(JOYSTICK_Y_PIN);
    
    // Cálculo da diferença em relação ao centro
    int16_t x_diff = CENTER_VALUE - x_value;
    int16_t y_diff = y_value - CENTER_VALUE;

    // Movimentação horizontal (para esquerda e para a direita)
    if (x_diff < -512) {  // Movimento para a esquerda
        pos_x -= 4;
    } else if (x_diff > 512) {  // Movimento para a direita
        pos_x += 4;
    }

    // Movimentação vertical (para cima e para baixo)
    if (y_diff < -512) {  // Movimento para cima
        pos_y -= 4;
    } else if (y_diff > 512) {  // Movimento para baixo
        pos_y += 4;
    }

    // Limitar o movimento do personagem dentro da tela
    if (pos_x < 1) pos_x = 1;
    if (pos_x > HEIGHT - SQUARE_SIZE) pos_x = HEIGHT - SQUARE_SIZE;
    if (pos_y < 1) pos_y = 1;
    if (pos_y > WIDTH - SQUARE_SIZE) pos_y = WIDTH - SQUARE_SIZE;

    // Apagar o quadrado anterior
    ssd1306_fill(ssd, false);
}

void inicializar_obstaculos() {
    for (int i = 0; i < NUM_OBSTACULOS; i++) {
        obstaculo_x[i] = rand() % (HEIGHT - 10);
        obstaculo_y[i] = 0;
        pontuacao[i] = 0;
    }
}

// Função para atualizar a posição do obstáculo
void atualizar_obstaculos() {
    for (int i = 0; i < NUM_OBSTACULOS; i++) {
        obstaculo_y[i] += 3;  // Move o obstáculo para baixo

        // Verifica se o obstáculo saiu da tela
        if (obstaculo_y[i] > WIDTH) {
            obstaculo_y[i] = 0;  // Reinicia o obstáculo no topo
            obstaculo_x[i] = rand() % (HEIGHT - 10);  // Nova posição X aleatória
            pontuacao[i]++;  // Aumenta a pontuação
        }
    }
}

// Função para verificar colisão
bool verificar_colisao() {
    for (int i = 0; i < NUM_OBSTACULOS; i++) {
        if (obstaculo_y[i] >= pos_y - 10 && obstaculo_y[i] <= pos_y + 10) {
            if (obstaculo_x[i] >= pos_x - 10 && obstaculo_x[i] <= pos_x + 10) {
                return true;  // Colisão detectada
            }
        }
    }
    return false;  // Sem colisão
}

void draw_game_elements(ssd1306_t *disp) {
    ssd1306_fill(disp, false);  // Limpa a tela

    // Desenha o personagem (quadrado)
    ssd1306_rect(disp, pos_x, pos_y, SQUARE_SIZE, SQUARE_SIZE, true, true);

    // Desenha os obstáculos (quadrados)
    for (int i = 0; i < NUM_OBSTACULOS; i++) {
        ssd1306_rect(disp, obstaculo_x[i], obstaculo_y[i],5 ,5, true, true);
    }

    ssd1306_send_data(disp);  // Atualiza o display
}



// Função para definir a cor do LED RGB
void set_rgb_color(bool red, bool green, bool blue) {
    gpio_put(GPIO_PIN_RED, red);
    gpio_put(GPIO_PIN_GREEN, green);
    gpio_put(GPIO_PIN_BLUE, blue);
}

// Função principal do jogo
void game() {
     
    // Desliga todos os LEDs no início
    set_rgb_color(0, 0, 0);
     

    // Gera uma cor aleatória (0 = vermelho, 1 = verde, 2 = azul)
    int random_color = rand() % 3;

    // Acende o LED com a cor aleatória
    if (random_color == 0) {
        set_rgb_color(1, 0, 0); // Vermelho
    } else if (random_color == 1) {
        set_rgb_color(0, 1, 0); // Verde
    } else if (random_color == 2) {
        set_rgb_color(0, 0, 1); // Azul
    }

    // Aguarda um tempo aleatório antes de verificar o botão
uint32_t start_time = to_ms_since_boot(get_absolute_time());
uint32_t wait_time = 1000 + (rand() % 2000); // Entre 1 e 3 segundos

bool button_pressed = false;
bool correct_press = false;

// Loop para verificar o botão durante o tempo de espera
while (to_ms_since_boot(get_absolute_time()) - start_time < wait_time) {
    if (!gpio_get(BUTTON_PIN_A)) { // Botão pressionado
        button_pressed = true;
        if (random_color == 0) { // Se o LED vermelho estava aceso
            correct_press = true;
        }
        break; // Sai do loop quando o botão é pressionado
    }
    sleep_ms(10); // Pequeno delay para evitar leitura excessiva
}

// Verifica o resultado
if (button_pressed) {
    if (correct_press) {
        printf("Você venceu!\n");
    } else {
        gamer_over(); // Toca música de derrota
        printf("Você perdeu!\n");
    }
} else {
    if (random_color == 0) { // Se o LED vermelho estava aceso e o botão não foi pressionado
        gamer_over(); // Toca música de derrota
        printf("Você perdeu!\n");
    }
}

// Desliga todos os LEDs no final
set_rgb_color(0, 0, 0);
}



//Função principal
int main() {
    stdio_init_all();
    srand(time(NULL)); 
    npInit(MATRIX_LED_PIN);

    // Inicialização do ADC
    adc_init();
    adc_gpio_init(JOYSTICK_X_PIN);  // Configura o pino do eixo X
    adc_gpio_init(JOYSTICK_Y_PIN);  // Configura o pino do eixo Y

  // Inicializa e Configura o LED Vermelho 
  gpio_init(GPIO_PIN_RED);
  gpio_set_dir(GPIO_PIN_RED, GPIO_OUT);
  // Inicializa e Configura o LED Vermelho 
  gpio_init(GPIO_PIN_GREEN);
  gpio_set_dir(GPIO_PIN_GREEN, GPIO_OUT);
  // Inicializa e Configura o LED Vermelho 
  gpio_init(GPIO_PIN_BLUE);
  gpio_set_dir(GPIO_PIN_BLUE, GPIO_OUT);
  set_rgb_color(0, 0, 0);

  // Inicializa e Configura o Botão A e PUll-Up
  gpio_init(BUTTON_PIN_A);
  gpio_set_dir(BUTTON_PIN_A, GPIO_IN);
  gpio_pull_up(BUTTON_PIN_A);
  gpio_set_irq_enabled_with_callback(BUTTON_PIN_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);//    // Configura as interrupções para ambos os botões, usando a mesma callback.
  
  // Inicializa e Configura o Botão B e PUll-Up
  gpio_init(BUTTON_PIN_B);
  gpio_set_dir(BUTTON_PIN_B, GPIO_IN);
  gpio_pull_up(BUTTON_PIN_B);
  gpio_set_irq_enabled(BUTTON_PIN_B, GPIO_IRQ_EDGE_FALL, true); // Borda de descida apenas

  //Inicializa o buzzer
  
  gpio_init(BUZZER_PIN);
  gpio_set_dir(BUZZER_PIN, GPIO_OUT);
  gpio_put(BUZZER_PIN, 0);
   
    // Inicialização do pino do botão do joystick
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);  // Habilita o resistor de pull-up interno
   
      // Inicaliza a comunicação I2C em um microcontrolador em 400kHz
      i2c_init(I2C_PORT, 400 * 1000);
      gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);//Configura o pino para funcionar como um pino I2C
      gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);// Configura o pino para funcionar como o pino de relogio I2C, sincronizar a comunicação entre os dispositivos.
      gpio_pull_up(I2C_SDA_PIN);
      gpio_pull_up(I2C_SCL_PIN);

        // Inicializa o display SSD1306
      ssd1306_t ssd;//Declara uma variavel do tipo ssd1306_t, representa o display.
      ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
      ssd1306_config(&ssd);
      ssd1306_fill(&ssd, false);
      ssd1306_send_data(&ssd);
      bool game_active = false; // Estado do jogo (inicia desligado)
      bool last_button_b_state = gpio_get(BUTTON_PIN_B); // Estado anterior do botão B
  
     
        // Posição inicial do quadrado
        int square_y = (WIDTH - SQUARE_SIZE)/2;
        int square_x = (HEIGHT - SQUARE_SIZE)/2;
        inicializar_obstaculos();
        printf("Sistema iniciado...\n");
        npClear();
    
        // Loop principal
    while (1) {
   // Verifica se o botão B foi pressionado (com debouncing simples)
   bool current_button_b_state = gpio_get(BUTTON_PIN_B);
   if (current_button_b_state != last_button_b_state) {
       sleep_ms(50); // Debouncing
       if (!current_button_b_state) { // Botão B pressionado
           game_active = !game_active; // Alterna o estado do jogo
           printf("Jogo %s\n", game_active ? "ligado" : "desligado");
       }
       last_button_b_state = current_button_b_state;
   }

   // Se o jogo estiver ativo, executa a função game()
   if (game_active) {
       game();
       sleep_ms(1000); // Espera um pouco antes de começar o próximo jogo
   } else {
       // Desliga todos os LEDs quando o jogo está inativo
       set_rgb_color(0, 0, 0);
       sleep_ms(100); // Pequeno delay para evitar uso excessivo da CPU
   }

    // Leitura de caracteres via UART
        //Parametro (0) significa que nao ha tempo limite
        int c = getchar_timeout_us(0); // Lê um caractere do Serial Monitor
        if (c != PICO_ERROR_TIMEOUT) { //Verifica se a leitura nao ocorreu erro.
            // Limpa o display antes de exibir o novo caractere
            ssd1306_fill(&ssd, false);
            // Exibe o caractere no display SSD1306
            ssd1306_draw_char(&ssd, c, 20, 30);
            ssd1306_send_data(&ssd);
            printf("Caractere lido: %c\n", c);
            // Verifica se o caractere é um número (0-9)
            sleep_ms(1000);
            if (c >= '0' && c <= '9') {
                int number = c - '0'; // Converte o caractere para um número
                mostrar_numero(number); // Exibe o símbolo correspondente na matriz WS2812
            }
            else 
            if (c >= 'a' && c <= 'z') {
                int number = c - 'a' ; // Converte o caractere para um número
                mostrar_letra(number);
            }else
            if(c == '#'){
                npClear();
                npWrite(NULL,0);
            }
        }
        // Verifica se o botão do joystick foi pressionado
        if (!gpio_get(BUTTON_PIN)) {  // Botão pressionado (nível baixo, pois está com pull-up)
            if (!button_pressedd) {  // Se o botão não foi pressionado ainda
                button_pressedd = true;  // Marca o botão como pressionado
                game_started = true;  // Inicia o jogo
            }
        } else {
            button_pressedd = false;  // Se o botão não está pressionado, reseta o estado
        }

        // Lógica do jogo
        if (game_started) {
            mover_personagem(&ssd);
            atualizar_obstaculos();
            draw_game_elements(&ssd);

            // Verifica colisão
            if (verificar_colisao()) {
                game_started = false;  // Encerra o jogo
                ssd1306_fill(&ssd, false);  // Limpa a tela
                ssd1306_send_data(&ssd);
            }

            sleep_ms(50);  // Ajusta a velocidade do jogo
        }
    }
    }
   
