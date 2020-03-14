#define sensorLDR A0
int nilaiSensor;
int led = D0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  nilaiSensor = analogRead(sensorLDR);
  Serial.print("Nilai Sensor: ");
  Serial.println(nilaiSensor);
  delay(3000);
  if(nilaiSensor > 400){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }
}
