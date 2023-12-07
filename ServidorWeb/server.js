const express = require('express');
const http = require('http');
const socketIO = require('socket.io');
const mqtt = require('mqtt');

const app = express();
const server = http.createServer(app);
const io = socketIO(server);

const mqttClient = mqtt.connect('mqtt://192.168.103.99');

mqttClient.on('connect', () => {
  mqttClient.subscribe('/sensores/temperatura', (err) => {
    if (!err) {
    }
  });
});

mqttClient.on('message', (topic, message) => {
  console.log('Mensagem recebida:', message.toString());
  io.emit('mqttMessage', message.toString());
});

app.get('/', (req, res) => {
  res.sendFile(__dirname + '/index.html');
});

const PORT = process.env.PORT || 3000;
server.listen(PORT, () => {
  console.log(`Servidor web rodando na porta ${PORT}`);
});