#define MATRIX_LED_PIN 7 // PINO DA MATRIZ DE LEDS ws2818b
#define JOYSTICK_X_PIN 26  // Pino ADC conectado ao eixo Y do joystick
#define JOYSTICK_Y_PIN 27  // Pino ADC conectado ao eixo Y do joystick
#define BUTTON_PIN 22
#define LED_GREEN_PIN 11
#define LED_BLUE_PIN 12   // Pino PWM conectado ao LED Azul
#define LED_RED_PIN 13   // Pino PWM conectado ao LED Azul
#define CENTER_VALUE 2048
#define JOYSTICK_MAX 4095
#define DEADZONE 110
#define BUTTON_A_PIN  5


// Definições para o display
#define WIDTH 128
#define HEIGHT 64
#define SQUARE_SIZE 8
#define I2C_SDA_PIN 14   // Pino SDA do I2C
#define I2C_SCL_PIN 15     // Pino SCL do I2C
#define I2C_PORT i2c1
#define endereco 0x3C
// Definição da quantidade de LEDs e o pino de controle
#define LED_COUNT 25// Quantidade de LEDs na matriz
#define DEBOUNCE_DELAY 500 // Tempo de debounce em milissegundos
#define DEBOUNCE_DELAY_MS 50 // Tempo de debounce em milissegundos

#define BUTTON_PIN_B 6
#define BUTTON_PIN_A 5


#define SCREEN_HEIGHT 64

