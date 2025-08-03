#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h> 

const int lightPinDetector = 2;
const int lightPin = 3;
const int DHTPin = 4;

const int humidityLedPin = 5;
const int temperatureLedPin = 6;

const int redPinLed = 9;
const int greenPinLed = 10;
const int bluePinLed = 11;

#define DHTTYPE DHT22
DHT dht(DHTPin, DHTTYPE);  

void PrintValues(bool hasNoLight, float humidity, float temperature);
void SetLedOnIfNoLight(bool hasNoLight);
void DisplayHumidityLevel(float humidity);
void DisplayTemperatureLevel(float temperature);

void setup() {
  Serial.begin(9600);

  dht.begin();
  
  pinMode(lightPinDetector, INPUT);
  pinMode(lightPin, OUTPUT);
  pinMode(redPinLed, OUTPUT);
  pinMode(greenPinLed, OUTPUT);
  pinMode(bluePinLed, OUTPUT);
  pinMode(humidityLedPin, OUTPUT);
  pinMode(temperatureLedPin, OUTPUT);
}

void loop() {
  bool hasNoLight = digitalRead(lightPinDetector);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  //Start procedures:
  PrintValues(hasNoLight, humidity, temperature);
  SetLedOnIfNoLight(hasNoLight);
  DisplayHumidityLevel(humidity);
  DisplayTemperatureLevel(temperature);
}

void PrintValues(bool hasNoLight, float humidity, float temperature){
  Serial.print("Light detected: ");
  Serial.println(!hasNoLight ? "Yes" : "No");
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.println("\n------------------------");
}

void SetLedOnIfNoLight(bool hasNoLight){
  if (hasNoLight)
  {
    digitalWrite(lightPin, HIGH);
  } else
  {
    digitalWrite(lightPin, LOW);
  }
}

void DisplayHumidityLevel(float humidity){

  int humidityValue = map(humidity, 0, 100, 0, 255);

  digitalWrite(humidityLedPin, HIGH);
  analogWrite(bluePinLed, humidityValue);
  
  delay(1000);
  
  analogWrite(bluePinLed, 0);
  digitalWrite(humidityLedPin, LOW);
}

void DisplayTemperatureLevel(float temperature){

  if (temperature < 10) temperature = 10;
  if (temperature > 40) temperature = 40;

  int pwmValue = map(temperature, 10, 40, 0, 255);
  pwmValue = constrain(pwmValue, 0, 255);

  int temperatureValue = 255 - pwmValue;

  digitalWrite(temperatureLedPin, HIGH);
  analogWrite(greenPinLed, temperatureValue);

  delay(1000);

  analogWrite(greenPinLed, 0);
  digitalWrite(temperatureLedPin, LOW);
}