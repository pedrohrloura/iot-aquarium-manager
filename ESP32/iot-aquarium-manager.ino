#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WifiClient.h>
#include <Servo.h>

/* Declarando os pinos */
int red = 14;
int yellow = 27;
int blue = 26;
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
const char * inTopic = "update me";
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
      client.subscribe(inTopic);
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

float temperatura()
{
  float temperature = analogRead(termistor); //VARIÁVEL DO TIPO INTEIRO QUE RECEBE O VALOR DE TEMPERATURA CALCULADO PELA BIBLIOTECA
  temperature /= 100;
  return temperature;
}

void ledOn(int led)
{
  digitalWrite(led, 1);
}
void ledOff(int led)
{
  digitalWrite(led, 0);
}
void command()
{
  switch (comando)
  {
  case '0':
    ledOn(red);
    break;
  case '1':
    ledOff(red);
    break;
  case '2':
    ledOn(yellow);
    break;
  case '3':
    ledOff(yellow);
    break;
  case '4':
    ledOn(blue);
    break;
  case '5':
    ledOff(blue);
    break;
  case '6':
    darAlimento();
    break;
  default:
    break;
  }
  comando = '-';
}
void setup()
{
  Serial.begin(115200);
  setupWifi();
  client.setServer(broker, 1883); //1883 porta
  client.setCallback(callback);

  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(blue, OUTPUT);
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
  if (currentTime - lastTime > 10000)
  {
    Serial.print(temperatura());
    snprintf(messages, 75, "%f", temperatura());
    client.publish(tempTopic, messages);
    lastTime = millis();
  }
  command();
}