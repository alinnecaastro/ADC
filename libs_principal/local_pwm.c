
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include "definicoes.h"



// Funcao auxiliar para utilização do buzzer de forma modular
void set_pwm_pin(uint pin, uint freq, uint duty_c) {
		gpio_set_function(pin, GPIO_FUNC_PWM);
		uint slice_num = pwm_gpio_to_slice_num(pin);
    		pwm_config config = pwm_get_default_config();
		float div = (float)clock_get_hz(clk_sys) / (freq * 10000);
		pwm_config_set_clkdiv(&config, div);
		pwm_config_set_wrap(&config, 10000); 
		pwm_init(slice_num, &config, true); 
		pwm_set_gpio_level(pin, duty_c); 
	};

// Musica simples buzzer - Arthur A L Trindade
void gamer_over() {
    const uint16_t frequencias[] = { 392,523,494,440,349,330,262,247,220,196,175,165,147}; // Notas: SOL, FA, MI, etc.
    const uint16_t duty[]={300, 300, 400, 400, 300, 300, 400, 400, 300, 300, 300,300, 300, 300,600};     // Ciclo de trabalho em ms
    const uint16_t duracoes[] ={200, 200, 250, 250, 200, 200, 250, 250, 200, 200, 200,200, 200, 500 };     // Durações em ms
    
    const uint16_t notas = sizeof(frequencias) / sizeof(frequencias[0]);    // Durações das notas em ms
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);

    for (uint16_t i = 0; i < notas; i++) {
        set_pwm_pin(BUZZER_PIN, frequencias[i], duty[i]);
        sleep_ms(duracoes[i]);
        pwm_set_enabled(slice_num, false);
        sleep_ms(50); // Pausa entre as notas
    }

    pwm_set_enabled(slice_num, false);

}