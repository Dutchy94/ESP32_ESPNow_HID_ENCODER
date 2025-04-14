// --- Notwendige Bibliotheken einbinden ---
#include <WiFi.h>             // WLAN-Funktionen für den ESP32
#include <esp_now.h>          // ESP-NOW Protokoll für Peer-to-Peer-Kommunikation
#include <MyESP32Encoder.h>   // Eigene oder externe Library zur Encoder-Auswertung

// --- MAC-Adresse des Empfängers (ESP32 HID) eintragen ---
// Diese muss exakt stimmen – sie identifiziert das Zielgerät
// Beispiel-Adresse vom USB-HID-ESP32:
uint8_t receiverMac[] = {0xCC, 0xBA, 0x97, 0x0A, 0x36, 0x4C};

// --- Encoder-Pins definieren ---
#define PIN_ENCODER_A 18
#define PIN_ENCODER_B 19
#define PIN_BUTTON    5

// --- Datenstruktur für die zu sendende Nachricht ---
// Hier kann man später beliebig erweitern (z. B. Tasterstatus, Richtung etc.)
typedef struct struct_message {
  int encoderWert;
} struct_message;

// --- Instanz der Struktur für die Datenübertragung ---
struct_message daten;

// --- Encoder-Objekt erstellen ---
MyESP32Encoder encoder(PIN_ENCODER_A, PIN_ENCODER_B, PIN_BUTTON);

// --- Callback-Funktion nach dem Senden ---
// Wird automatisch aufgerufen, wenn der ESP32 etwas gesendet hat
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Sendestatus: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "OK" : "Fehlgeschlagen");
}


// --- Setup-Funktion: wird beim Start einmal ausgeführt ---
void setup() {
  Serial.begin(115200);      // Serielle Schnittstelle starten

  WiFi.mode(WIFI_STA);       // Station-Modus aktivieren
  WiFi.disconnect();         // WLAN-Verbindung trennen (nicht benötigt für ESP-Now)

  encoder.begin();           // Encoder initialisieren

  // --- ESP-NOW Initialisierung ---
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init fehlgeschlagen");
    return;
  }

  esp_now_register_send_cb(OnDataSent);  // Callback registrieren

  // --- Peer (Empfänger) definieren ---
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMac, 6); // Ziel-MAC kopieren
  peerInfo.channel = 0;     // Kanal 0 = automatisch (muss auf beiden Geräten gleich sein)
  peerInfo.encrypt = false; // Verschlüsselung aus

  // --- Peer hinzufügen ---
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Peer hinzufügen fehlgeschlagen");
    return;
  }

  Serial.println("Sender bereit...");
}


// --- Loop-Funktion: läuft dauerhaft ---
// Sobald der Encoder-Taster gedrückt wurde, wird der aktuelle Wert gesendet
void loop() {
  if (encoder.wasButtonPressed()) {
    daten.encoderWert = encoder.getValue();  // Aktuellen Wert auslesen
    Serial.print("Sende Wert: ");
    Serial.println(daten.encoderWert);

    // Daten an den definierten Empfänger senden
    esp_now_send(receiverMac, (uint8_t *)&daten, sizeof(daten));
  }

  delay(10); // Optional zur Entlastung der CPU, schadet bei unserem Falls nicht auch wenn ESP Now wirklich schnell ist. Siehe vergleichsvideos mit WiFi auf Youtube.
}
