#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "pio_config.h"
#include "hardware/pwm.h"
#include "pico/bootrom.h"
#include "ws2812.pio.h"
#include "libs/definicoes.h"//arquivos para variaveis globais
#include "libs/debounce.c"//arquivos para debounce
#include "libs/pwm_led.c"//arquivos para debounce
#include <stdlib.h>
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "font.h"
#include "pico/bootrom.h"
#include "hardware/adc.h"

uint8_t border_thickness = 1;  // Espessura inicial da borda

// Variáveis de estado
bool led_green_state = false;       // Estado do LED Verde
bool pwm_leds_enabled = true;       // Estado dos LEDs PWM (Vermelho e Azul)
uint8_t border_style = 0;           // Estilo da borda do display (0, 1, 2, ...)

// Função para ler o valor do joystick
uint16_t read_joystick(uint pin) {
    adc_select_input(pin - 26);
    return adc_read();
}

//Função leitura do botao da joystick
void joystick_button_pressed() {
    static uint32_t last_press_time = 0;  // Armazena o tempo do último pressionamento
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    // Debounce: ignora pressionamentos muito rápidos
    if (current_time - last_press_time > 200) {  // 200 ms de debounce
        led_green_state = !led_green_state;      // Alterna o estado do LED Verde
        gpio_put(LED_GREEN_PIN, led_green_state); // Atualiza o estado do LED
        
        // Alterna a espessura da borda entre 1 e 5
        if (border_thickness == 5) {
            border_thickness = 1;  // Se a espessura for 5, altera para 1
        } else {
            border_thickness = 5;  // Se a espessura for 1, altera para 5
        }
      
        last_press_time = current_time;  // Atualiza o tempo do último pressionamento
    }
}

// Função para ativar/desativar os LEDs PWM
void button_a_pressed() {
    static uint32_t last_press_time = 0;  // Armazena o tempo do último pressionamento
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    // Debounce: ignora pressionamentos muito rápidos
    if (current_time - last_press_time > 200) {  // 200 ms de debounce
        pwm_leds_enabled = !pwm_leds_enabled;   // Alterna o estado dos LEDs PWM
        last_press_time = current_time;  // Atualiza o tempo do último pressionamento
    }
}

//Função para desenhar a borda
void draw_border(ssd1306_t *disp, uint8_t thickness) {
    for (uint8_t i = 0; i < thickness; i++) {
        ssd1306_rect(disp, i, i, WIDTH - 2*i, HEIGHT - 2*i, true, false);  // Desenha a borda
    }
    ssd1306_send_data(disp);  // Atualiza o display
}

// Função para desenhar um quadrado no display
void draw_square(ssd1306_t *disp, int x, int y) {
    ssd1306_rect(disp, x, y, SQUARE_SIZE, SQUARE_SIZE, true,true); // Desenha o quadrado
    ssd1306_send_data(disp); // Atualiza o display
}

int main() {
    // Inicialização do stdio
    stdio_init_all();
   
    
    // Inicialização do ADC
    adc_init();
    adc_gpio_init(JOYSTICK_X_PIN);  // Configura o pino do eixo X
    adc_gpio_init(JOYSTICK_Y_PIN);  // Configura o pino do eixo Y

    // Inicialização do PWM para o LED Vermelho
    gpio_set_function(LED_RED_PIN, GPIO_FUNC_PWM);
    uint slice_num_red = pwm_gpio_to_slice_num(LED_RED_PIN);
    uint channel_red = pwm_gpio_to_channel(LED_RED_PIN);
    pwm_set_wrap(slice_num_red, 255);  // Define o intervalo do PWM para 8 bits (0-255)
    pwm_set_enabled(slice_num_red, true);
    pwm_set_chan_level(slice_num_red, channel_red, 0);

    // Inicialização do PWM para o LED Azul
    gpio_set_function(LED_BLUE_PIN, GPIO_FUNC_PWM);
    uint slice_num_blue = pwm_gpio_to_slice_num(LED_BLUE_PIN);
    uint channel_blue = pwm_gpio_to_channel(LED_BLUE_PIN);
    pwm_set_wrap(slice_num_blue, 255);  // Define o intervalo do PWM para 8 bits (0-255)
    pwm_set_chan_level(slice_num_blue, channel_blue, 0); 
    pwm_set_enabled(slice_num_blue, true);

    // Inicialização do display SSD1306
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    // Inicialização do pino do botão do joystick
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);  // Habilita o resistor de pull-up interno

    ssd1306_t ssd;
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_fill(&ssd, false); // Limpa o display inicialmente
    ssd1306_send_data(&ssd);

    // Desenha a borda com a espessura atual
    draw_border(&ssd, border_thickness);

    // Inicialização do pino do botão A
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);  // Habilita o resistor de pull-up interno
    gpio_set_irq_enabled_with_callback(BUTTON_PIN_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);   

    // Inicialização do pino do LED Verde
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_put(LED_GREEN_PIN, led_green_state);  // Inicializa o LED Verde como apagado

    gpio_set_irq_enabled_with_callback(LED_GREEN_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);   

    // Posição inicial do quadrado
    int square_y = (WIDTH - SQUARE_SIZE)/2;
    int square_x = (HEIGHT - SQUARE_SIZE)/2;

    while (true) {
        // Leitura dos valores do joystick
         uint16_t x_value = read_joystick(JOYSTICK_X_PIN);
         uint16_t y_value = read_joystick(JOYSTICK_Y_PIN);
        
        // Cálculo da diferença em relação ao centro
        int16_t x_diff = CENTER_VALUE - x_value;
        int16_t y_diff = y_value - CENTER_VALUE;

       // Mapeia o valor do eixo  para o brilho do LED Vermelho
        uint8_t brightness_red = 0;
        if (y_value < (CENTER_VALUE - DEADZONE)) {
        brightness_red = (CENTER_VALUE - DEADZONE - y_value) / 8;
        } else if (y_value > (CENTER_VALUE + DEADZONE)) {
        brightness_red = (y_value - (CENTER_VALUE + DEADZONE)) / 8;
        }

        // Mapeia o valor do eixo X para o brilho do LED Azul
        uint8_t brightness_blue = 0;
        if (x_value < (CENTER_VALUE - DEADZONE)) {
        brightness_blue = (CENTER_VALUE - DEADZONE - x_value) / 8;
        } else if (x_value > (CENTER_VALUE + DEADZONE)) {
        brightness_blue = (x_value - (CENTER_VALUE + DEADZONE)) / 8;
        }

        // Define o ciclo de trabalho do PWM para controlar o brilho dos LEDs
        if (pwm_leds_enabled) {
            pwm_set_gpio_level(LED_RED_PIN, brightness_red);   // LED Vermelho
            pwm_set_gpio_level(LED_BLUE_PIN, brightness_blue); // LED Azul
        } else {
            pwm_set_gpio_level(LED_RED_PIN, 0);  // Desliga o LED Vermelho
            pwm_set_gpio_level(LED_BLUE_PIN, 0); // Desliga o LED Azul
        }

        // Verifica se o botão do joystick foi pressionado
        if (!gpio_get(BUTTON_PIN)) {  // Botão pressionado (nível baixo, pois está com pull-up)
            joystick_button_pressed(); // Chama a função para alternar o LED Verde e a borda do display
        }

        // Verifica se o botão A foi pressionado
        if (!gpio_get(BUTTON_A_PIN)) {  // Botão pressionado (nível baixo, pois está com pull-up)
            button_a_pressed();         // Chama a função para ativar/desativar os LEDs PWM
        }

         // Movimentação do quadrado no display com base no joystick
         if (x_diff < -512) {
            square_x -= 4;  // Movendo para a esquerda
        } else if (x_diff > 512) {
            square_x += 4;  // Movendo para a direita
        }

        if (y_diff < -512) {
            square_y -= 4;  // Movendo para cima
        } else if (y_diff > 512) {
            square_y += 4;  // Movendo para baixo
        }
        
        // Limites para o quadrado não sair do display
        if (square_x < 1) square_x = 1;
        if (square_x > HEIGHT - SQUARE_SIZE) square_x = HEIGHT- SQUARE_SIZE;
        if (square_y < 1) square_y = 1;
        if (square_y > WIDTH - SQUARE_SIZE) square_y = WIDTH  - SQUARE_SIZE;
        // Apagar o quadrado anterior
        ssd1306_fill(&ssd, false);  // Limpa a tela

        
        // Desenha a borda com a espessura atual
        draw_border(&ssd, border_thickness);

        // Desenha o quadrado na nova posição
        draw_square(&ssd, square_x, square_y);

        // Pequeno delay para evitar atualizações muito rápidas
        sleep_ms(20);
        }

        return 0;
        }