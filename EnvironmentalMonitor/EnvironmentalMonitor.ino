const int digitalLightPin = 2;

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  
  pinMode(digitalLightPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  bool hasNotLight = digitalRead(digitalLightPin);
  bool hasLight = !hasNotLight;

  Serial.print("light detected: ");
  Serial.print(hasLight);
  Serial.println("");

  if

  delay(1000);
}
