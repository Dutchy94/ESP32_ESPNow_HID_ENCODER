// --- Benötigte Bibliotheken einbinden ---
#include <WiFi.h>              // WLAN-Funktionen für den ESP32
#include <esp_now.h>           // ESP-NOW-Protokoll für Peer-to-Peer-Funk
#include "USB.h"               // USB-Funktionen des ESP32-S2/S3
#include "USBHIDKeyboard.h"    // HID-Tastatur-Emulation

// --- Tastatur-Objekt erstellen ---
USBHIDKeyboard Keyboard;


// --- Datenstruktur für empfangene Nachricht ---
typedef struct struct_message {
  int encoderWert;             // Z. B. aktueller Drehgeberwert
} struct_message;

struct_message empfangen;      // Objekt zur Speicherung empfangener Daten
bool neueDaten = false;        // Wird auf true gesetzt, sobald neue Daten empfangen wurden


// --- Callback-Funktion, wenn neue Daten per ESP-NOW empfangen werden ---
void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  memcpy(&empfangen, data, sizeof(empfangen));  // Daten in Struktur kopieren
  neueDaten = true;

  // Ausgabe zur Kontrolle
  Serial.print("Empfangen von: ");
  for (int i = 0; i < 6; i++) {
    if (i > 0) Serial.print(":");
    Serial.printf("%02X", info->src_addr[i]);
  }
  Serial.print(" → Wert: ");
  Serial.println(empfangen.encoderWert);
}


// --- Setup-Funktion: Wird einmal beim Start ausgeführt ---
void setup() {
  Serial.begin(115200);     // Serielle Schnittstelle starten

  USB.begin();              // USB-Funktion aktivieren (nur auf USB-fähigen ESP32-S2/S3!)
  Keyboard.begin();         // Tastatur-Emulation starten

  WiFi.mode(WIFI_STA);      // Station-Modus aktivieren (nicht als Access Point)
  WiFi.disconnect();        // Kein normales WLAN verbinden

  // ESP-Now starten
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init fehlgeschlagen");
    return;
  }

  // Empfangs-Callback registrieren
  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("Empfänger bereit...");
}


// --- Loop-Funktion: Wiederholt sich dauerhaft ---
void loop() {
  if (neueDaten) {
    neueDaten = false;   // Nur einmal pro empfangenem Datensatz verarbeiten

    // --- Tastatureingabe über USB ausgeben ---
    Keyboard.print("Messwert");           // Text senden
    Keyboard.press(KEY_LEFT_SHIFT);       // Simuliere Großschreibung
    Keyboard.press('.');                  // Punkt (z. B. als Trennung)
    delay(50);
    Keyboard.releaseAll();                // Alle Tasten loslassen
    Keyboard.print(" ");
    Keyboard.print(empfangen.encoderWert); // Empfangener Wert als Zahl
    delay(100);
    Keyboard.print("\r\n");               // Neue Zeile (= Enter-Taste)
  }

  delay(10); // Kleine Pause zur Stabilisierung
}

//Das mit der Tastatur könnte in der Praxis eine Lösung sein um zum Beispiel Messwerte in einem prozess zu erfassen,
//die Informationen müssen ja nicht über den Encoder kommen sondern könnten auch Beispielsweise Temperatur von Mehreren 
//Stationen sein die dem Empfänger die Werte schicken.
