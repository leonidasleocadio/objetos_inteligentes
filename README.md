# objetos_inteligentes

Controle e monitoramento inteligente de dispensadores de resíduos em ambientes públicos, fechados e com alto fluxo de pessoas utilizando Iot.

Este trabalho tem como objetivo principal criar um protótipo, utilizando um microcontrolador Arduino, sensores, atuadores e conexão com a Internet através de um cabo USB, que possa ter uma aplicação prática na administração, controle e monitoramento dos dispensadores de resíduos (lixeiras) localizados em ambientes públicos, fechados e com grande fluxo de pessoas.

Através do uso de um sensor ultrassônico que identifca o volume de resíduos ocupados na lixeira, LEDS de diferentes cores são acesos indicando o status em que a lixeira encontra-se preenchida.

Lixeira preenchida até 70% acenderá o LED Verde, lixeira ocupada de 70 a 85 %, acenderá o LED Amarelo e lixeira com ocupação acima de 85%, acenderá o LED Vermelho.

É utilizado um potenciomêtro que funcionará como dispositivo de acionamento para movimentar o servomotor, que irá girar 180 graus e trocará a lixeira.

Todos estes atuadores e sensores estão conectadoa a uma placa Arduino UNO.
