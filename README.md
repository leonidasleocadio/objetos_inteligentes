# objetos_inteligentes

Controle e monitoramento inteligente de dispensadores de resíduos em ambientes públicos, fechados e com alto fluxo de pessoas utilizando Iot.

Este trabalho tem como objetivo principal criar um protótipo, utilizando um microcontrolador NodeMCU (ESP8266), sensores, atuadores e conexão com a Internet através do protocolo de comunicação MQTT, que possa ter uma aplicação prática na administração e monitoramento dos dispensadores de resíduos (lixeiras) localizados em ambientes públicos, fechados e com grande fluxo de pessoas.

Através do uso de um sensor ultrassônico que identifca o volume de resíduos ocupados na lixeira, os LEDS com as cores verde e vermelho acenderão ou pagarão de acordo com o volume preenchido do recipiente.

Para um recipiente totalmente cheio, o LED Vermelho é aceso e o verde apagado e para um recipiente vazio, o LED Vermelho apaga e o LED Verde acende.

Todos os atuadores e sensores estão conectados a uma placa NodeMCU(ESP8266).
