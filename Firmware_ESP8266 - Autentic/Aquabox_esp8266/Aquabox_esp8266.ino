#include <ESP8266WiFi.h> // Importa a Biblioteca ESP8266WiFi
#include <PubSubClient.h> // Importa a Biblioteca PubSubClient

// WIFI
const char* SSID = "MOB-ANDREZA"; // SSID da Rede. Substitua aqui seu SSID de WiFi
const char* PASSWORD = "mob3857950"; // Senha da Rede. Substitua aqui sua senha de WiFi

// MQTT
const char* BROKER_MQTT = "m11.cloudmqtt.com"; // IP/URL DO BROKER MQTT
int BROKER_PORT = 10860; // Porta do Broker MQTT
const char* BROKER_USER = "hpredaum";
const char* BROKER_PASS = "mZMw2G6XpTVE";  


#define ID_MQTT  "-29.1838681/-54.8528838" //id mqtt definido como as coordenada geográficas para garantir unicidade

WiFiClient espClient; // Cria o objeto espClient

PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient

// Prototypes das funções utilizadas no decorrer do Firmware
void readData();
void initSerial();
void initWiFi();
void initMQTT();

void setup() {
  initSerial();
  initWiFi();
  initMQTT();
}
// Função para iniciar a comunicação serial
void initSerial() {
  Serial.begin(9600);
}
// Função para iniciar a Conexão com a rede WiFi
void initWiFi() {
  WiFi.begin(SSID, PASSWORD); // Conecta na Rede Wireless
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
}
// Funcão para se conectar ao Broker MQTT
void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT); // Informa o broker e porta utilizados
}

// Função para se reconectar ao Broker MQTT caso cair a comunicação
void reconnectMQTT() {
  while (!MQTT.connected()) {
    if (MQTT.connect(ID_MQTT,BROKER_USER,BROKER_PASS)) { //Aqui coloco (ID_MQTT, usuário, senha) do servidor 
    } else {
      delay(2000);
    }
  }
}

// Função para se reconectar a rede WiFi caso caia a comunicação com a rede
void recconectWiFi() {
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
}
void readData() {
  if (Serial.available()) {
    String temp = "";
    while (Serial.available()) {
      char c = (char)Serial.read();
      if (c != '\n') {
        temp += c;
      }
      delay(10);
    }
   
    String payload = temp;
    //String payload = "1000000000000000200000000000000030000000000000000000"; Teste

    char payloadChar[payload.length()];
    payload.toCharArray(payloadChar, payload.length() + 1); // Converte a String para Char Array
    // Publica no tópico Teste todas as informações contidas na variável payload.
    MQTT.publish("Aquabox", payloadChar);
  }
}

void loop() {
  if (!MQTT.connected()) {
    reconnectMQTT(); // Caso o ESP se desconecte do Broker, ele tenta se reconectar ao Broker
  }
  recconectWiFi(); // Caso o ESP perca conexão com a rede WiFi, ele tenta se reconetar a rede.
  readData();
  MQTT.loop();
}
