# 🏠 Home Automation System

A smart embedded system project to control lights and a fan using an **ATmega328P** microcontroller, simulated via **PICSimLab** and operated remotely using the **Blynk mobile app** through the **W5500 Ethernet module**.

---

## 👨‍💻 Developed By

**Anand Kumar**  
**Reg. No.**: 23163135006  
**College**: Government Engineering College, Vaishali – 844115  
**Internship Organization**: RCPL

---

## 🎯 Project Goal

To develop a **Home Automation System** capable of:

- Controlling Room, Hall, and Garden lights
- Operating a fan remotely
- Simulating all components in a virtual embedded environment

---

## 🔧 Tools & Technologies Used

| Tool              | Purpose                               |
|-------------------|----------------------------------------|
| Arduino IDE       | Code writing and uploading             |
| PICSimLab         | Simulation of ATmega328P hardware      |
| Blynk Console     | Mobile-based remote control            |
| W5500 Ethernet    | Enables internet communication         |

---

## 🧩 Components Used

- **Microcontroller**: ATmega328P
- **LEDs**: 
  - Room Light: LED 1 & 2 (Red)
  - Hall Light: LED 3 & 4 (Blue)
  - Garden Light: LED 5 & 6 (Green)
  - Fan Indicator: LED 8
- **Fan (Simulated)**: Controlled by Blynk
- **W5500 Ethernet Module**: LAN-based internet access

---

## 📱 Blynk Mobile Dashboard

- **App Interface**: 4 Button Widgets
- **Virtual Pins**:
  - V1: Room Light  
  - V2: Hall Light  
  - V3: Garden Light  
  - V4: Fan
- **Mode**: Switch

---

## 💡 Working

| Switch         | Output                                     |
|----------------|--------------------------------------------|
| V0 ON          | Room Light (LED 1 & 2) glows (Red)         |
| V1 ON          | Hall Light (LED 3 & 4) glows (Blue)        |
| V2 ON          | Garden Light (LED 5 & 6) glows (Green)     |
| V3 ON          | Fan & fan indicator (LED 8) turns ON       |

---

## 🎥 Project Demo Video

📺 **Watch project demo**  

👉 [Click to Watch](https://youtu.be/RK3TXceNyIk)

---

## 🚀 Future Scope

- Add Wi-Fi-based connectivity using ESP8266
- Expand control to appliances like AC, TV, etc.
- Add sensors (temperature, motion) for automation
- Create real-time notifications via Blynk

---

## 🙏 Acknowledgment

Project completed under **RCPL Internship Program** as part of the **Embedded Systems & IoT** training.

---

