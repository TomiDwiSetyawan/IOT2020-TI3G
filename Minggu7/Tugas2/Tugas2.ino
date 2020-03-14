#define sensorLDR A0
#include <dht.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int nilaiSensor;
int lampu = D0;
int sensorSuhu = D4;
int temperature;
int humidity;
dht DHT;
int ledState = LOW;
const int ledPin =  LED_BUILTIN;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(lampu, OUTPUT);
  lcd.begin();
  lcd.backlight();
  pinMode(ledPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  DHT.read11(sensorSuhu);
  temperature = (int)round(DHT.temperature);
  humidity = DHT.humidity;  
  nilaiSensor = analogRead(sensorLDR);

  lcd.setCursor(0, 0);
  lcd.print("");

  lcd.setCursor(0, 1);
  lcd.print("             ");

  lcd.setCursor(0, 0);
  lcd.print("Suhu C : ");
  lcd.print(temperature);
  lcd.print(" C ");
  lcd.setCursor(0, 1);
  
  lcd.print("Cahaya : ");
  lcd.print(nilaiSensor);  

  if (nilaiSensor > 400 && temperature < 30) {
//    Serial.print("Suhu Dingin !");
//    Serial.println(" ");
    digitalWrite(lampu, HIGH);
    delay(1000);
    digitalWrite(lampu, LOW);
    delay(1000);
  } else if (nilaiSensor < 400 && temperature >= 30){
//    Serial.print("Suhu Panas !");
//    Serial.println(" ");
    digitalWrite(ledPin, LOW);
    digitalWrite(lampu, HIGH);
  }

  delay(2000);
}
