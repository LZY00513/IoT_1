

#  ESP8266-Based IoT Device Control System

A small-scale **IoT prototype** demonstrating **two-way communication** between an ESP8266 device and a Node.js cloud service using the **MQTT protocol**.
This project simulates a smart light that can be remotely controlled via a web dashboard, with the device reporting its real-time state back to the cloud.

---

##  Overview

**System Architecture:**

```
[Web Dashboard] ⇄ [Node.js Server] ⇄ [MQTT Broker] ⇄ [ESP8266 Device]
```

* **Device (ESP8266 / Arduino C++)**
  Connects to Wi-Fi, subscribes to `home/zhengyi/light/set`, and publishes status updates to `home/zhengyi/light/status`.

* **Cloud Service (Node.js + MQTT.js + Express)**
  Provides RESTful APIs for turning the device on/off and subscribes to device status updates.

* **Frontend (HTML / JS)**
  Simple web dashboard to send commands and display the current light state in real time.

---

##  Tech Stack

* **Hardware:** ESP8266 (NodeMCU)
* **Languages:** C++ (Arduino), JavaScript
* **Frameworks & Libraries:** Express.js, MQTT.js
* **Protocols:** MQTT, HTTP
* **Tools:** Arduino IDE, Node.js, VS Code
* **Broker:** [HiveMQ Public Broker](https://www.hivemq.com/demos/websocket-client/) (`broker.hivemq.com:1883`)

---

##  File Structure

```
ESP8266-IoT-Device-Control/
├── device/
│   └── device.ino          # ESP8266 firmware (Arduino)
├── server/
│   ├── server.js           # Node.js MQTT + REST server
│   └── package.json
├── public/
│   └── index.html          # Web dashboard
├── .gitignore
├── README.md
└── LICENSE
```

---

##  Getting Started

### 1️ Clone Repository

```bash
git clone https://github.com/<your_username>/ESP8266-IoT-Device-Control.git
cd ESP8266-IoT-Device-Control
```

---

### 2️ Setup Node.js Server

```bash
cd server
npm install
node server.js
```

You should see:

```
Server running on http://localhost:3000
Connected to MQTT broker
```

---

### 3️ Flash ESP8266 Device

1. Open **device/device.ino** in Arduino IDE
2. Replace:

   ```cpp
   const char* WIFI_SSID = "YOUR_WIFI";
   const char* WIFI_PASS = "YOUR_PASSWORD";
   ```
3. Select board: **NodeMCU 1.0 (ESP-12E Module)**
4. Upload sketch to your device
5. Open **Serial Monitor** at **115200 baud** to see connection logs

---

### 4️ Run the Web Dashboard

Visit [http://localhost:3000](http://localhost:3000)
You should see buttons to **Turn ON / Turn OFF** and the current device status.

When clicking “ON”, the LED on your ESP8266 should light up, and the serial monitor will show:

```
Received command: on
LED turned ON
```

---

##  MQTT Topics

| Topic                       | Direction      | Description                        |
| --------------------------- | -------------- | ---------------------------------- |
| `home/zhengyi/light/set`    | Cloud → Device | Control command (`on` / `off`)     |
| `home/zhengyi/light/status` | Device → Cloud | Device state report (`on` / `off`) |

>  You can replace `zhengyi` with your name or unique prefix to avoid topic collisions on public brokers.

---

##  Demo Screenshots (Add Later)

| Component      | Example                          |
| -------------- | -------------------------------- |
|  Device      | ![device-photo](docs/device.jpg) |
|  Dashboard   | ![dashboard](docs/dashboard.png) |
|  Serial Log | ![serial-log](docs/serial.png)   |

---

##  Learning Outcome

* Gained hands-on experience in **IoT device-to-cloud communication** using MQTT
* Learned to bridge **hardware control** and **web-based APIs** with Node.js
* Understood the core architecture of modern **smart home systems**
* Built foundational knowledge for **Matter protocol interoperability**

---

##  Resume Description (for reference)

**ESP8266-Based IoT Device Control System**
*Personal Project, Nov 2025*
Tech Stack: ESP8266 (Arduino C++), Node.js, Express, MQTT.js, HTML

* Developed a two-way communication prototype between a smart device and cloud service via MQTT protocol.
* Implemented RESTful APIs for control and real-time status reporting.
* Designed a simple web dashboard for remote interaction and monitoring.
* Demonstrated end-to-end IoT integration consistent with smart home connectivity principles.

---

##  Author

**Zhengyi (Alex) Li**
Master of Computer Science, The University of Sydney
📧 [lizhengyi238@gmail.com](mailto:lizhengyi238@gmail.com)
🌐 [github.com/LZY00513](https://github.com/LZY00513)

---

## License

MIT License © 2025 Lamore

---

### Optional Footer

> This repository is part of a learning project exploring IoT communication principles and serves as a foundational step toward Matter protocol interoperability.
