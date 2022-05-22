// ===================
// Incluir bibliotecas
// ===================
#include <HCSR04.h>
#include <ESP8266WiFi.h> //inclui suporte ao NodeMCU
#include <PubSubClient.h> //inclui suporte ao MQTT no HiveMQ Cloud


HCSR04 hc(D7, D8); //initialisation class HCSR04 (trig pin , echo pin)

int ledPinVd = D0; // porta para o LED Verde
int ledPinVe = D1; // porta para o LED Vermelho


// =======================
// Definicoes e constantes
// =======================

// Configuracoes da rede WiFi
const char* ssid = "Rede Bolinha"; //SSID da rede WiFi
const char* password = "bolinha2204"; //senha da rede WiFi

const char* mqtt_server = "broker.mqtt-dashboard.com"; //URL do broker MQTT
const int mqtt_server_port = 1883; //porta do broker MQTT

// Variaveis globais e objetos
#define MSG_BUFFER_SIZE (500) //define MSG_BUFFER_SIZE como 500
WiFiClient client; //cria o objeto client
PubSubClient mqtt_client(client); //cria o objeto mqtt_client
long lastMsg = 0;

String clientID = "ESP8266Client-"; //identificacao do cliente

String topicoPrefixo = "MACK20009240"; //para o prefixo do topico, utilizar MACK seguido do TIA
String topicoTodos = topicoPrefixo + "/#"; //para retornar todos os topicos
String topico_0 = topicoPrefixo + "/hello"; //topico para teste
String mensagem_0 = "NodeMCU Connected"; //mensagem para o topico 0
String topico_1 = topicoPrefixo + "/sensor1"; //topico para o sensor 1
String mensagem_1 = ""; //mensagem para o topico 1
String topico_2 = topicoPrefixo + "/atuador1"; //topico para o atuador 1
String mensagem_2 = ""; //mensagem para o topico 3
String topico_3 = topicoPrefixo + "/atuador2"; //topico para o atuador 2
String mensagem_3 = ""; //mensagem para o topico 3
String mensagemTemp = ""; //armazena temporariamente as mensagens recebidas via MQTT



// ==============================
// Funcoes definidas pelo usuario
// ==============================

// Funcao para configurar a conexao WiFi
void setup_wifi() {
  //WiFi.mode(WIFI_STA); //ativa o modo de estacao
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

// Funcao para receber mensagens
void callback(char* topic, byte* payload, unsigned int length) {
  mensagemTemp = "";
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    mensagemTemp += (char)payload[i];
  }

  if (String(topic) == topico_2) {
    mensagem_2 = mensagemTemp;
  }

  if (String(topic) == topico_3) {
    mensagem_3 = mensagemTemp;   
  }

  Serial.println();

  // Switch on the LED if the first character is present
  if ((char)payload[0] != NULL) {
    digitalWrite(LED_BUILTIN, LOW); // Turn the LED on
    // Note that LOW is the voltage level but actually the LED is on;
    // this is because it is active low on the ESP-01
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off by making the voltage HIGH
  } else {
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off by making the voltage HIGH
  }
}

// Funcao para conectar no broker MQTT
void reconnect() {
  // Loop until we’re reconnected
  while (!mqtt_client.connected()) {
    Serial.print("Attempting MQTT connection…");

	// Create a random client ID
    randomSeed(micros()); //inicializa a semente do gerador de numeros aleatorios
    clientID += String(random(0xffff), HEX);

	// Attempt to connect
    if (mqtt_client.connect(clientID.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      mqtt_client.publish(topico_0.c_str(), mensagem_0.c_str());
      // ... and resubscribe
      mqtt_client.subscribe(topicoTodos.c_str());
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}	

// =======
// setup()
// =======

void setup() {
  pinMode(ledPinVd, OUTPUT); //PINO VERDE
  pinMode(ledPinVe, OUTPUT); // PINO VERMELHO
  Serial.begin(9600); //inicializa a saida serial
  setup_wifi();

  mqtt_client.setServer(mqtt_server, mqtt_server_port); //configura a conexao com o broker MQTT
  mqtt_client.setCallback(callback); //configura o recebimento de mensagens
}

// ======
// loop()
// ======

void loop() {
  if (!mqtt_client.connected()) {
    reconnect();
  }
  mqtt_client.loop(); //processa as mensagens e mantem a conexao com o broker MQTT

  int distancia = hc.dist(); // definindo a variavel distancia

  // setando o status da mensagem de acordo com a distancia medida pelo sensor ultrassonico
  if (distancia < 10) {
    mensagem_1 = "Cheio";
  } 
  
  else 
    mensagem_1 = "Com Espaço";
  
 
  //Publica mensagem
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    mqtt_client.publish(topico_1.c_str(), mensagem_1.c_str());
  }
  
  //Subscreve mensagem
  //A subscricao eh realizada na funcao reconnect(),
  //e o recebimento das mensagens na funcao callback().
  //Para filtrar as mensagens dos topicos, verificar a funcao callback().

  //Controla os LEDS em 
  if (mensagem_2.toInt() == 1) {
     digitalWrite(ledPinVd, 0);
        } 
  else      
     digitalWrite(ledPinVd, 1);


  if (mensagem_2.toInt() == 0) {
     digitalWrite(ledPinVe, 0);    
    }  
  else      
    digitalWrite(ledPinVe, 1);
}
