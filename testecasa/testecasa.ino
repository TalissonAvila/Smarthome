#include <WiFi.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <DHT.h>

#define servidor_mqtt           "urlmqtt" //URL do servidor MQTT
#define servidor_mqtt_porta     "00000" //Porta do servidor
#define servidor_mqtt_usuario   "user"  //Usuário
#define servidor_mqtt_senha     "password"  //Senha
#define mqtt_topico_sub         "topic" //Tópico
//Dados da rede Wifi
char NomeDoWiFi[] = "ssid";
char SenhaDoWiFi[] = "password";


#define D0 14 //Define a porta 14 como D0
#define D1 13 //Define a porta 13 como D1
#define D2 12 //Define a porta 12 como D2
#define D3 2  //Define a porta 02 como D3
//definindo a porta 4 pro sensor
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int umidade = 0;
int temperatura = 0;
int ultimoEnvioMQTT = 0;

//Variáveis de controle do cliente MQTT e do WiFi
WiFiClient espClient;
PubSubClient client(espClient);
WiFiManager wifiManager;

void setup() {
  //Prepara o pino D0 para funcinar como saída
  pinMode(D0, OUTPUT);
  digitalWrite(D0, HIGH);
  //Prepara o pino D1 para funcinar como saída
  pinMode(D1, OUTPUT);
  digitalWrite(D1, HIGH);
  //Prepara o pino D2 para funcinar como saída
  pinMode(D2, OUTPUT);
  digitalWrite(D2, HIGH);
  //Prepara o pino D3 para funcinar como saída
  pinMode(D3, OUTPUT);
  digitalWrite(D3, HIGH);

  //Inicia a comunicação serial
  Serial.begin(115200);
  dht.begin();
  wifiParameter();
  conectaWifi();
}

void loop() {
  //Testa conexão com o servidor MQTT e caso falhe, tata reconectar
  if (!client.connected())
  {
    reconectar();
  }
  if ((millis() - ultimoEnvioMQTT > 2000)){
    enviaDHT();
    ultimoEnvioMQTT = millis();
  }
  client.loop();
}



