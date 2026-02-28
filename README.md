# 📍 ESP32 GPS Tracker with WiFi & Google Maps Integration

A real-time GPS tracking system built using **ESP32** and **NEO-6M GPS Module**.
This project connects to WiFi, reads GPS data via UART, detects satellite fix, and generates a clickable Google Maps link in the Serial Monitor.

Designed for IoT, Embedded Systems, and GPS-based tracking applications.

---

## 🚀 Features

* ✅ WiFi connection with LED status indicator
* ✅ GPS satellite fix detection
* ✅ NMEA `$GPGGA` parsing
* ✅ Latitude & Longitude conversion to Decimal Degrees
* ✅ Automatic Google Maps link generation
* ✅ Dual LED status system

---

## 🛠 Hardware Requirements

![Image](https://m.media-amazon.com/images/I/61MDW%2BU%2BrvL.jpg)

![Image](https://m.media-amazon.com/images/I/516HJgU86jL._AC_UF1000%2C1000_QL80_.jpg)

![Image](https://m.media-amazon.com/images/I/51eLYXtROlL.jpg)

![Image](https://www.electronics.com.bd/3776-large_default/5mm-rb-led-common-anode-3pin-tri-color-emitting-diodes-f5-rb-water-clear.jpg)

* ESP32 Development Board
* NEO-6M GPS Module
* 2x LEDs (Red & Green)
* 220Ω Resistors
* Breadboard
* Jumper Wires

---

## 🔌 Pin Configuration

### 📡 GPS → ESP32

| GPS Pin | ESP32 Pin |
| ------- | --------- |
| TX      | 16        |
| RX      | 17        |
| VCC     | 3.3V      |
| GND     | GND       |

### 💡 LED Connections

| LED                | ESP32 Pin |
| ------------------ | --------- |
| 🔴 WiFi Status LED | 18        |
| 🟢 GPS Fix LED     | 21        |

---

## ⚙️ Setup Instructions

### 1️⃣ Install Required Software

* Install **Arduino IDE**
* Install **ESP32 Board Package**
* Select Board → *ESP32 Dev Module*

### 2️⃣ Update WiFi Credentials

Modify this section in the code:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

### 3️⃣ Upload the Code

* Connect ESP32 via USB
* Select correct COM Port
* Click Upload

### 4️⃣ Open Serial Monitor

* Set Baud Rate → **115200**
* Wait for WiFi connection and GPS fix

---

## 🔴🟢 LED Status Explanation

| LED      | Status   | Meaning            |
| -------- | -------- | ------------------ |
| 🔴 Red   | Blinking | Connecting to WiFi |
| 🔴 Red   | ON       | WiFi Connected     |
| 🟢 Green | OFF      | No GPS Fix         |
| 🟢 Green | ON       | GPS Fix Successful |

---

## 📍 Example Serial Output

```
===== GPS FIX OK =====
Latitude: 22.701002
Longitude: 90.353451

Google Maps Link:
https://www.google.com/maps?q=22.701002,90.353451
======================
```

Open the printed link in a browser to view the location directly in Google Maps.

---

## 🧠 How It Works

1. ESP32 connects to WiFi.
2. GPS module sends NMEA sentences via UART2.
3. The program filters the `$GPGGA` sentence.
4. Checks if satellite count ≥ 4.
5. Converts raw NMEA coordinates (DDMM.MMMM) into Decimal Degrees.
6. Prints Latitude, Longitude, and Google Maps link.
7. Turns ON Green LED when GPS fix is valid.

---

## 📌 Technical Details

* UART Used: `HardwareSerial(2)`
* GPS Baud Rate: 9600
* Serial Monitor Baud Rate: 115200
* Minimum Satellites Required: 4
* Library Used: `WiFi.h`

---

## 🔮 Future Improvements

* 🌐 Firebase Live Tracking
* 📱 Mobile App Integration
* ☁️ Cloud Dashboard
* 🔋 Portable Battery Version
* 📡 GSM-Based Tracker Version

---

## 👨‍💻 Author

**Kashif Mustari**
CSE Student | Embedded Systems & IoT Enthusiast
Barishal, Bangladesh 🇧🇩
