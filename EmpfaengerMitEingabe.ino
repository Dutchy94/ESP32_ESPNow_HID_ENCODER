#include <WiFi.h>
#include <esp_now.h>
#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

typedef struct struct_message {
  int encoderWert;
} struct_message;

struct_message empfangen;
bool neueDaten = false;

void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  memcpy(&empfangen, data, sizeof(empfangen));
  neueDaten = true;

  Serial.print("Empfangen von: ");
  for (int i = 0; i < 6; i++) {
    if (i > 0) Serial.print(":");
    Serial.printf("%02X", info->src_addr[i]);
  }
  Serial.print(" → Wert: ");
  Serial.println(empfangen.encoderWert);
}

void setup() {
  Serial.begin(115200);
  USB.begin();
  Keyboard.begin();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init fehlgeschlagen");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("Empfänger bereit...");
}

void loop() {
  if (neueDaten) {
    neueDaten = false;

    // Messwert per HID senden
    Keyboard.print("Messwert");
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('.');
    delay(50);
    Keyboard.releaseAll();
    Keyboard.print(" ");
    Keyboard.print(empfangen.encoderWert);
    delay(100);
    Keyboard.print("\r\n");  //Entspricht enter Taste
  }

  delay(10); // kurz schlafen
}
