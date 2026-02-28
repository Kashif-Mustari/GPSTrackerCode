#include <WiFi.h>

// ================= WIFI CONFIG =================
const char* ssid = "KASHIF_HOME_NET";
const char* password = "123456789";

// ================= GPS UART CONFIG =================
HardwareSerial gpsSerial(2);   // Using UART2

#define RX2_PIN 16
#define TX2_PIN 17

// ================= LED CONFIG =================
#define NETWORK_LED 18   // 🔴 Red LED (WiFi)
#define GPS_LED 21      // 🟢 Green LED (GPS Fix)

// ================= VARIABLES =================
String nmeaLine = "";
double latitude = 0;
double longitude = 0;
bool gpsFix = false;

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  pinMode(NETWORK_LED, OUTPUT);
  pinMode(GPS_LED, OUTPUT);

  digitalWrite(NETWORK_LED, LOW);
  digitalWrite(GPS_LED, LOW);

  gpsSerial.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN);

  connectWiFi();
}

// ================= LOOP =================
void loop() {
  readGPS();
}

// ================= WIFI CONNECT FUNCTION =================
void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(NETWORK_LED, !digitalRead(NETWORK_LED)); // Blink while connecting
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  digitalWrite(NETWORK_LED, HIGH);
}

// ================= GPS READ FUNCTION =================
void readGPS() {
  while (gpsSerial.available()) {
    char c = gpsSerial.read();

    if (c == '\n') {
      processNMEA(nmeaLine);
      nmeaLine = "";
    } else {
      nmeaLine += c;
    }
  }
}

// ================= NMEA PROCESS FUNCTION =================
void processNMEA(String data) {

  if (data.startsWith("$GPGGA")) {

    String parts[15];
    int index = 0;
    int start = 0;

    for (int i = 0; i < data.length(); i++) {
      if (data[i] == ',' || data[i] == '*') {
        parts[index++] = data.substring(start, i);
        start = i + 1;
      }
    }

    if (index > 7) {

      int satellites = parts[7].toInt();

      if (satellites >= 4) {

        latitude = convertToDecimal(parts[2]);
        longitude = convertToDecimal(parts[4]);

        if (latitude != 0 && longitude != 0) {

          gpsFix = true;
          digitalWrite(GPS_LED, HIGH);

          Serial.println("\n===== GPS FIX OK =====");
          Serial.print("Latitude: ");
          Serial.println(latitude, 6);
          Serial.print("Longitude: ");
          Serial.println(longitude, 6);

          // 👉 Google Maps Link Print
          printGoogleMapsLink();

          Serial.println("======================\n");
        }
      } else {
        gpsFix = false;
        digitalWrite(GPS_LED, LOW);
      }
    }
  }
}

// ================= GOOGLE MAPS LINK FUNCTION =================
void printGoogleMapsLink() {

  Serial.println("Google Maps Link:");
  Serial.print("https://www.google.com/maps?q=");
  Serial.print(latitude, 6);
  Serial.print(",");
  Serial.println(longitude, 6);
}

// ================= CONVERT NMEA TO DECIMAL =================
double convertToDecimal(String raw) {
  if (raw == "") return 0;

  double val = raw.toDouble();
  int degrees = int(val / 100);
  double minutes = val - (degrees * 100);

  return degrees + (minutes / 60.0);
}