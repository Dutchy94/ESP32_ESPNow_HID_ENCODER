# 🎮 Kabelloser Drehgeber als HID-Eingabegerät mit ESP32 & ESP-NOW

In diesem Projekt wird ein Drehgeber („Rotary Encoder“) kabellos über ESP-NOW an einen zweiten ESP32 gesendet. Der zweite ESP gibt den empfangenen Wert als Tastatureingabe über USB an den PC weiter – ideal für DIY-Eingabegeräte, Mediacontroller, CAD-Shortcuts, usw.

---

## 📺 Video zum Projekt

➡️ **YouTube-Video ansehen:** [![Zum Video](https://img.youtube.com/vi/VIDEO_ID/maxresdefault.jpg)](https://youtu.be/7NnEgXOPL9s)

📌 **YouTube-Kanal:** [Mein Technik-Kanal](https://www.youtube.com/channel/UCBEnu0tEb6VZ2NwIN-1uIiw)

---

## 📦 Projektübersicht

**Sender (ESP32 #1):**
- Liest den Encoder-Wert aus
- Sendet bei Tasterdruck den Wert über ESP-NOW

**Empfänger (ESP32 #2):**
- Empfängt den Encoder-Wert
- Gibt diesen über USB als HID-Tastaturbefehl an den PC weiter

---

## 🔌 Verwendete Hardware

- **Drehgeber (Rotary Encoder) mit Tasterfunktion**
- **Mikrocontroller 1 (Sender):** [AZ-Delivery ESP32 Dev Kit C V4](https://www.amazon.de/dp/B0D4QZ9CKD?ref=ppx_yo2ov_dt_b_fed_asin_title)
- **Mikrocontroller 2 (Empfänger):** [ESP32-S3 Dev Board mit USB HID](https://www.amazon.de/dp/B0DBHHDZ88?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_1&th=1)

---

## 💻 Verwendete Bibliotheken

- `WiFi.h`
- `esp_now.h`
- `MyESP32Encoder` (eigene oder modifizierte Library zur Encoder-Auswertung)
- `USB.h` (nur für ESP32-S2/S3)
- `USBHIDKeyboard.h` (HID-Tastaturemulation)

---

## 🧰 Projektdateien

- `ScanMac.ino` – Zeigt die MAC-Adresse des ESP32
- `EncoderOnly.ino` – Testet Encoder mit serieller Ausgabe
- `Sender.ino` – Sendet den Encoder-Wert per ESP-NOW
- `EmpfaengerMitEingabe.ino` – Empfängt Daten und gibt sie als Tastatureingabe weiter

Jede Datei ist ausführlich kommentiert.

---

## 🎥 Aufnahmeequipment

- **Kamera:** Sony Alpha 6000  
- **Objektiv:** AF E 16-50mm 1:3,5-5,6 PZ OSS (SEL-P1650)

---

## 💡 Anwendungsbeispiele

- Kabelloser Lautstärkeregler
- Medien-Shortcut-Controller
- Scrollrad oder Eingabefeld für PC
- DIY-CAD-Kontroller

---

## 📫 Feedback & Support

Hat dir das Projekt gefallen? Lass gerne einen **Kommentar**, ein **Like** oder ein **Abo** auf YouTube da! Fragen oder Verbesserungsvorschläge gerne direkt unter dem Video oder per Issue hier auf GitHub.

---

Viel Spaß beim Nachbauen!

**🛠️ Made with Leidenschaft für Soft- und Hardware.**

