# IoT Aquarium Manager
Trabalho de IoT que consiste em gerenciar um aquário.

## App
- Linguagem: JavaScript
- Função: Faz conexão com servidor MQTT, coleta dados do servidor, faz tratamento e realiza a inserção no banco de dados.

#### Bibliotecas
- [Tedious](https://tediousjs.github.io/tedious/) - Faz a conexão com o SQL server.
- [Dotenv](https://www.npmjs.com/package/dotenv) - Ferramenta utilizada para orquestrar as variáveis ambiente de um projeto.
- [Moment](https://momentjs.com/) - Analisar, validar, manipular, e exibir datas e horas em JavaScript.
- [Mqtt](https://www.npmjs.com/package/mqtt) - Faz conexão com servidor MQTT.

## BD
- SGBD: SQL Server
#### Scripts
- Criação das tabelas
- Insert experimentais
- Principais consultas

## ESP32s

#### Principais funções:

- Coletar temperatura do sensor e enviar para servidor MQTT.
- Alimentar aquário desejado remotamente.

#### Bibliotecas
- Arduino.h
- Wifi.h
- PubSubClient.h
- WifiClient.h
- Servo.h
