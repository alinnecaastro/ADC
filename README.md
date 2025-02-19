## Conversro Análogico em Digital

## Introdução
O objetivo deste projeto é explorar as funcionalidades do RP2040, um microcontrolador baseado na arquitetura ARM Cortex-M0+, através do uso do conversor analógico-digital (ADC), controle de LEDs RGB via PWM e interação com um display SSD1306 utilizando o protocolo I2C. O projeto visa controlar a intensidade luminosa dos LEDs RGB com base nos valores de um joystick e, ao mesmo tempo, exibir graficamente a posição do joystick em um display OLED.

## Estrutura do Projeto  
- **build/** → Diretório de compilação gerado pelo CMake.   
- **debounce.c** → Arquivo que importa a interrupção e o debounce do codigo 
- **definicoes.h** → Arquivo que importa as variaveis dos botoes, matriz,delay,led... 
- **pwm_led.c** → Arquivo para importar os PWM dos leds 
- **CMakeLists.txt** → Configuração do CMake para compilação.  
- **ADC.c** → Código principal do projeto.  
- **font.h** → Biblioteca da criação das letras minuscula
- **pio_config.h** → Configuração do PIO para LEDs NeoPixel.  
- **pico_sdk_import.cmake** → Importação do SDK do Raspberry Pi Pico.  
- **README.md** → Documentação do projeto.  
- **ssd1306.c / ssd1306.h** → Bibliotecas para controle do Display ssd1306  
- **ws2812.pio / ws2812.pio.h** → Código PIO para controle dos LEDs WS2812.  


## Descrição Geral

Este projeto utiliza o microcontrolador RP2040 da placa BitDogLab para controlar a intensidade de dois LEDs RGB com base nos valores analógicos de um joystick. O PWM é usado para ajustar suavemente o brilho dos LEDs, com o LED Azul controlado pelo eixo Y e o LED Vermelho pelo eixo X. A posição do joystick é representada no display SSD1306, exibindo um quadrado que se move conforme os eixos do joystick.

Além disso, o projeto implementa interrupções para os botões do joystick e o botão A. O botão do joystick alterna o estado de um LED verde e modifica a borda do display, enquanto o botão A ativa ou desativa os LEDs PWM. O sistema também conta com debouncing para garantir a precisão dos acionamentos dos botões.

O projeto integra PWM, ADC, I2C e interrupções para fornecer um controle interativo dos LEDs e uma visualização em tempo real da posição do joystick no display OLED.
 

## Video do funcionamento do projeto
https://drive.google.com/file/d/1intQzf6gTPsj8ewaYyqj7BhsSrvsklRY/view?usp=sharing


## Funcionalidades do Projeto
- Leitura do Joystick e Controle dos LEDs
Os eixos X e Y do joystick fornecem valores analógicos que são lidos via ADC. Esses valores são utilizados para ajustar o brilho dos LEDs RGB por meio do controle de ciclo de trabalho (duty cycle) do PWM.

- LED Azul (eixo Y): Quando o joystick é movido para cima (valores menores no eixo Y), o LED azul tem seu brilho aumentado. Quando o joystick é movido para baixo (valores maiores no eixo Y), o brilho também aumenta, até o valor máximo.
- LED Vermelho (eixo X): Da mesma forma, o LED vermelho tem seu brilho ajustado com base nos valores do eixo X.
Movimento do Quadrado no Display SSD1306
A posição do quadrado de 8x8 pixels no display SSD1306 é ajustada de acordo com os valores do joystick. À medida que o joystick é movido, o quadrado se desloca na tela, refletindo a posição dos eixos X e Y.

# Interrupções de Botões
- Botão do Joystick: Ao ser pressionado, alterna o estado de um LED verde e altera o estilo da borda do display SSD1306.
- Botão A: Ativa ou desativa a modulação de PWM para os LEDs, permitindo que os LEDs deixem de ser controlados por PWM se desejado.
# Tratamento de Debounce
O debounce foi implementado para garantir que o sistema não registre múltiplos pressionamentos de botão em sequência, causado por variações no sinal dos botões. Para isso, foi aplicado um atraso de tempo após o acionamento de qualquer botão, garantindo que o sistema ignore pressões muito rápidas.

## Requisitos do Projeto
° Uso de interrupções: Todas as funcionalidades relacionadas aos botões devem ser implementadas
utilizando rotinas de interrupção (IRQ);
° Debouncing: É obrigatório implementar o tratamento do bouncing dos botões via software;
° Controle de LEDs: O projeto deve incluir o uso de LEDs comuns e LEDs WS2812, demonstrando o
domínio de diferentes tipos de controle;
° Uso do Display ssd1306;
° Comunicação via UART

## Conclusão
Este projeto teve como foco explorar as funcionalidades do RP2040, utilizando o ADC para capturar os valores do joystick, controlando a intensidade dos LEDs RGB via PWM e exibindo graficamente a posição do joystick em um display SSD1306. A implementação de interrupções para os botões e o tratamento de debounce são fundamentais para garantir uma experiência de usuário precisa e sem falhas. O código demonstra o funcionamento completo do sistema, desde a captura dos sinais analógicos até a manipulação visual e de hardware dos componentes.