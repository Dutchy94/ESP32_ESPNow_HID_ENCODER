#define PIN_ENCODER_A 18
#define PIN_ENCODER_B 19
#define PIN_BUTTON    5


#include <MyESP32Encoder.h>

//Encoder Deklaration
MyESP32Encoder encoder(PIN_ENCODER_A,PIN_ENCODER_B,PIN_BUTTON);
//Positionsvariable
long lastPosition = 0;

int printValueOnChange(int EncValue){
  long newPosition = encoder.getValue();
  
  if (newPosition != EncValue) 
  {
    Serial.print("Encoder Wert: ");
    Serial.println(newPosition);
    return newPosition;
  }
  return EncValue;
}

void setup() {
  Serial.begin(115200);

  encoder.begin();
  delay(2000);
  Serial.println("Controller gestartet...");
}

void loop() {
  
  if (encoder.wasButtonPressed()) {
    Serial.println("Button gedrückt!");
  }
  lastPosition= printValueOnChange(lastPosition);

  //delay(100);
}
