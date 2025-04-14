#include <WiFi.h>
#include <esp_wifi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  uint8_t mac[6];
  esp_wifi_get_mac(WIFI_IF_STA, mac);  // <- neue Methode in v3.x

  Serial.print("MAC: ");
  for (int i = 0; i < 6; i++) {
    if (i > 0) Serial.print(":");
    Serial.printf("%02X", mac[i]);
  }
  Serial.println();
}

void loop() {}
