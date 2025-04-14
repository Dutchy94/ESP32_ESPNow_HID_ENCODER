// --- Pinbelegung für den Drehgeber (Encoder) definieren ---
#define PIN_ENCODER_A 18   // Signal A des Drehgebers an GPIO18
#define PIN_ENCODER_B 19   // Signal B des Drehgebers an GPIO19
#define PIN_BUTTON    5    // Encoder-Taster an GPIO5

// --- Benötigte Bibliothek einbinden ---
// Achtung: 'MyESP32Encoder' ist eine eigene Encoder-Library (In diesem Repo...)
#include <MyESP32Encoder.h>

// --- Encoder-Objekt erstellen ---
// Initialisiert den Encoder mit den definierten Pins für A, B und Taster
MyESP32Encoder encoder(PIN_ENCODER_A, PIN_ENCODER_B, PIN_BUTTON);

// --- Variable zur Speicherung der letzten Encoder-Position ---
long lastPosition = 0;


// --- Funktion zur Ausgabe des Encoderwertes, nur wenn sich der Wert geändert hat ---
int printValueOnChange(int EncValue){
  long newPosition = encoder.getValue();  // Aktuellen Wert vom Encoder holen
  
  // Nur wenn sich der Wert geändert hat, wird er ausgegeben
  if (newPosition != EncValue) 
  {
    Serial.print("Encoder Wert: ");
    Serial.println(newPosition);
    return newPosition;  // Neuer Wert wird zurückgegeben und gespeichert
  }
  return EncValue; // Kein Update nötig, alter Wert bleibt erhalten
}


// --- Setup-Funktion: wird einmal beim Start ausgeführt ---
void setup() {
  Serial.begin(115200);    // Serielle Ausgabe starten mit 115200 Baud
  encoder.begin();         // Encoder initialisieren
  delay(2000);             // Kurze Startverzögerung (z. B. für seriellen Monitor, optional könnte wahrscheinlich auch ohne.)
  Serial.println("Controller gestartet...");
}


// --- Loop-Funktion: wird wiederholt ausgeführt --- 
void loop() {
  
  // Prüfen ob der Encoder-Taster gedrückt wurde
  if (encoder.wasButtonPressed()) {
    Serial.println("Button gedrückt!");
    // → In der Praxis: Bei uns zum Senden der Werte.
  }

  // Encoder-Wert prüfen und ggf. ausgeben
  lastPosition = printValueOnChange(lastPosition);


}
