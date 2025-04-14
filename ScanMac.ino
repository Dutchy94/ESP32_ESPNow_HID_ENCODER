// --- Benötigte Bibliotheken für WLAN-Funktionen einbinden ---
#include <WiFi.h>        // Standard-WiFi-Funktionen für ESP32
#include <esp_wifi.h>    // Direkter Zugriff auf interne WiFi-Funktionen (z. B. MAC-Adresse auslesen)


// --- Setup-Funktion: wird beim Start einmal ausgeführt ---
void setup() {
  Serial.begin(115200);   // Serielle Schnittstelle starten mit 115200 Baud (für Seriellen Monitor)

  WiFi.mode(WIFI_STA);    // ESP32 in den Station-Modus versetzen (Client-Modus)
  // → Wichtig: Nur so bekommt man die MAC-Adresse der Station-Schnittstelle

  uint8_t mac[6];         // Array zum Speichern der MAC-Adresse (6 Bytes)

  esp_wifi_get_mac(WIFI_IF_STA, mac);  // MAC-Adresse der WLAN-Station-Schnittstelle holen
  // → Hinweis: Diese Funktion ist ab ESP-IDF v3.x Standard (robuster als ältere Methoden)

  // Ausgabe der MAC-Adresse über den seriellen Monitor:
  Serial.print("MAC: ");
  for (int i = 0; i < 6; i++) {
    if (i > 0) Serial.print(":");        // Doppelpunkte zwischen den Bytes
    Serial.printf("%02X", mac[i]);       // Jedes Byte als zweistellige Hex-Zahl formatieren (z. B. A4, 1F, etc.)
  }
  Serial.println();                      // Zeilenumbruch am Ende
}


// --- Loop-Funktion: bleibt leer, da keine weitere Logik nötig ist ---
void loop() {}
