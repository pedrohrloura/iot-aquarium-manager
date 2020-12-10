#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WifiClient.h>
#include <Servo.h>
/* Declarando os pinos */
int termistor = 4;
Servo servo;

char comando;

/* Dados da rede wifi e broker/topicos */
const char * ssid = "update me";
const char * pass = "update me";
const char * brokerUser = "update me";
const char * brokerPass = "update me";
const char * broker = "update me";
const char * tempTopic = "update me";
const char * foodTopic= "update me";
/**/


WiFiClient espClient;
PubSubClient client(espClient);
long currentTime, lastTime; // var para cálculo do tempo
char messages[50];          //Mensagem de saida

void setupWifi()
{
  delay(100);
  Serial.print("\nConnecting to");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print("-");
  }

  Serial.print("\nConnected to");
  Serial.println(ssid);
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("\nConnecting to");
    Serial.println(broker);
    if (client.connect("ID", brokerUser, brokerPass))
    {
      Serial.print("\nConnected to");
      Serial.println(broker);
      client.subscribe(foodTopic);
    }
    else
    {
      Serial.println("\nTrying connect again");
      delay(5000);
    }
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Received messages: ");
  Serial.println(topic);
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
    comando = (char)payload[i];
  }
  Serial.println();
}
void darAlimento()
{
  for (int pos = 0; pos < 180; pos++)
  {
    servo.write(pos);
    delay(20);
  }
  delay(2000);
  for (int pos = 180; pos > 0; pos--)
  {
    servo.write(pos);
    delay(20);
  }
}

int temperatura()
{
  int temperature = analogRead(termistor); //VARIÁVEL DO TIPO INTEIRO QUE RECEBE O VALOR DE TEMPERATURA CALCULADO PELA BIBLIOTECA
  temperature /= 100;
  return temperature;
}

void command()
{
  if(comando == '0' || comando == '1'|| comando == '2'|| comando == '3'|| comando == '4')
  {
    darAlimento();
  }
  comando = '-';
}
void setup()
{
  Serial.begin(115200);
  setupWifi();
  client.setServer(broker, 1883); //1883 porta
  client.setCallback(callback);

  servo.attach(25); //Pino do servo
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  currentTime = millis();

  /* Publicando a cada 10 segundos */
  if (currentTime - lastTime > 30000)
  {
    Serial.print(temperatura());
    snprintf(messages, 75, " {\"temp\": \"%d\", \"codAquario\": 0}", temperatura());
    client.publish(tempTopic, messages);
    lastTime = millis();
  }
  command();
}