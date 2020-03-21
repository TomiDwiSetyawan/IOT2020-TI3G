#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 16
#define RST_PIN 0
#define lampu 2

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN);

const int ledPin =  LED_BUILTIN;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();

  lcd.begin();
  lcd.backlight();

  pinMode(ledPin, OUTPUT);
  pinMode(lampu, OUTPUT);
}

void loop() {  
  lcd.setCursor (0, 0);
  lcd.print("  #######  Welcome ! #######");
  lcd.scrollDisplayRight();
  delay(60);  
  lcd.setCursor (0, 1);
  lcd.print("####### Scan Your Card #######");
  lcd.scrollDisplayRight();
  delay(60);

  Serial.println("Waiting card...");
  digitalWrite(ledPin, HIGH);
  digitalWrite(ledPin, LOW);

  if (!mfrc522.PICC_IsNewCardPresent())
  {
    delay(50);
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial())
  {
    delay(50);
    return;
  }

  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();
}


void dump_byte_array(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++)
  {
  }
  if (buffer[0] == 0xF2 &&
      buffer[1] == 0xD9 &&
      buffer[2] == 0x7D &&
      buffer[3] == 0x33) {
    Serial.println("Sukses");
    digitalWrite(ledPin, LOW);
    digitalWrite(lampu, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Akses Diterima! ");
    lcd.setCursor(0, 1);
    lcd.print(" Silahkan Masuk ");
    delay(1500);
  } else {
    Serial.println("Gagal");
    lcd.setCursor(0, 0);
    digitalWrite(lampu, LOW);

    lcd.clear();
    lcd.print(" Akses Ditolak! ");
    lcd.setCursor(0, 1);
    lcd.print(" Dilarang Masuk ");
    delay(1500);
  }

}
