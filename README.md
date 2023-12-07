# Projeto Final de IOT
Este arquivo descreve o passo a passo necessário para a instalaçaõ de um projeto IOT para o monitoramento de temperatura.

## Instalando o broker

O primeiro passo é a instalação do Broker MQTT que servirá de intermediário para a comunicação assíncrona.

Para instalar no Linux, em seu terminal, digite:
`sudo apt-get install mosquitto`

Para instalar o cliente, digite:
`sudo apt-get install mosquitto-clients`

Após isso inicie o seu broker digitando:
`mosquitto`

## Abaixando o projeto Web
navegue até a pasta que deseje iniciar seu projeto e digite:
`git clone "https://github.com/choviski/trabalho-iot.git"`

após isso, abra o arquivo ServidorWeb/server.js e edite a linha 10:
`const  mqttClient  =  mqtt.connect('mqtt://192.168.103.99');`
para o endereço IP do seu broker. E edite a linha 13:
`mqttClient.subscribe('/sensores/temperatura', (err) => {`
para o seu tópico.

## Abaixando o projeto do Esp
Abra o arquivo Conectando o MQTT/src/main.cpp e edite as credenciais da sua conexão MQTT e sua conexão Wi-fi:

`const char *SSID = "nome_rede";` para o nome da sua rede
`const char *PWD = "senha"` para sua senha
`const char *mqttServer = "192.168.0.9";` para o IP do seu Broker mqtt

Feito isso pode-se fazer o upload do código no ESP e executar `node server.js` na pasta do servidor web e acessar o dashboard da aplicação no endereço `localhost:3000`.
