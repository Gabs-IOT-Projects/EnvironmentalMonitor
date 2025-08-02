#include <Arduino.h>

const int lightPinDetector = 2;
const int lightPin = 3;

void setup() {
  Serial.begin(9600);
  
  pinMode(lightPinDetector, INPUT);
  pinMode(lightPin, OUTPUT);
}

void loop() {
  bool hasNoLight = digitalRead(lightPinDetector);

  Serial.print("light detected: ");
  Serial.print(!hasNoLight);
  Serial.println("");

  if (hasNoLight)
  {
    digitalWrite(lightPin, HIGH);
  } else
  {
    digitalWrite(lightPin, LOW);
  }

  delay(100);
}
