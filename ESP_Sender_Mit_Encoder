#include <WiFi.h>
#include <esp_now.h>
#include <MyESP32Encoder.h>

// MAC-Adresse des Empfängers:

//HID USB ESP32: CC:BA:97:0A:36:4C
uint8_t receiverMac[] = {0xCC, 0xBA, 0x97, 0x0A, 0x36, 0x4C};

// Encoder-Pins
#define PIN_ENCODER_A 18
#define PIN_ENCODER_B 19
#define PIN_BUTTON    5

typedef struct struct_message {
  int encoderWert;
} struct_message;

struct_message daten;

MyESP32Encoder encoder(PIN_ENCODER_A, PIN_ENCODER_B, PIN_BUTTON);

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Sendestatus: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "OK" : "Fehlgeschlagen");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  encoder.begin();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init fehlgeschlagen");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMac, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Peer hinzufügen fehlgeschlagen");
    return;
  }

  Serial.println("Sender bereit...");
}

void loop() {
  if (encoder.wasButtonPressed()) {
    daten.encoderWert = encoder.getValue();
    Serial.print("Sende Wert: ");
    Serial.println(daten.encoderWert);
    esp_now_send(receiverMac, (uint8_t *)&daten, sizeof(daten));
  }

  delay(10); // optional
}
