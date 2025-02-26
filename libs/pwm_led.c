#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "definicoes.h"

// Função para configurar o PWM
void setup_pwm(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(slice_num, JOYSTICK_MAX);
    pwm_set_enabled(slice_num, true);
}

// Função para definir o duty cycle do PWM
void set_pwm_duty(uint pin, uint16_t duty) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint channel = pwm_gpio_to_channel(pin);
    pwm_set_chan_level(slice_num, channel, duty);
}
