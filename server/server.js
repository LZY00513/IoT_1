// server.js
const express = require('express');
const mqtt = require('mqtt');
const path = require('path');

const app = express();
const PORT = 3000;

// MQTT broker 
const MQTT_BROKER = 'mqtt://broker.hivemq.com';
const client = mqtt.connect(MQTT_BROKER);

// topics
const SET_TOPIC = 'home/light/set';
const STATUS_TOPIC = 'home/light/status';

let latestStatus = 'unknown';

client.on('connect', () => {
  console.log('Connected to MQTT broker');
  client.subscribe(STATUS_TOPIC, (err) => {
    if (!err) console.log('Subscribed to', STATUS_TOPIC);
  });
});

client.on('message', (topic, message) => {
  const msg = message.toString();
  console.log(`Received ${topic} -> ${msg}`);
  if (topic === STATUS_TOPIC) {
    latestStatus = msg;
  }
});

// serve static frontend
app.use(express.static(path.join(__dirname, '..', 'public')));

// API endpoints for control
app.get('/api/on', (req, res) => {
  client.publish(SET_TOPIC, 'on');
  res.json({ result: 'sent on' });
});

app.get('/api/off', (req, res) => {
  client.publish(SET_TOPIC, 'off');
  res.json({ result: 'sent off' });
});

app.get('/api/status', (req, res) => {
  res.json({ status: latestStatus });
});

app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
