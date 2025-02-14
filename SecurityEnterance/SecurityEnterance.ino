#include <Servo.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <NewPing.h>
#include <Adafruit_MLX90614.h>

#define ir1   A0
#define ir2   A1
#define sPin   3
#define buzzer 4

#define echoPin 6
#define trigPin 5

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
NewPing sonar(trigPin, echoPin, 100);
Servo servo;

byte event, oldEvent;
int gateCount;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(buzzer, OUTPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  servo.attach(sPin);
  gateClose();

  if (!mlx.begin()) Serial.println("Error MLX sensor!");
}

void loop() {
  int distance = sonar.ping_cm();

  if (event == 0) {
    lcd.setCursor(0, 0);
    lcd.print(" SMART ENTRANCE ");
    lcd.setCursor(3, 1);
    lcd.print((String)"COUNTER: " + gateCount);
    Serial.println(distance);

    if (distance > 5 && distance < 25) event = 1;
  }
  else if (event == 1) {
    lcd.setCursor(0, 1);
    lcd.print("HUMAN DETECTED");

    long sMs = millis();
    while (digitalRead(ir1)) {
      if (millis() - sMs > 10000) {
        event = 0;
        break;
      }
    }
    if (!digitalRead(ir1)) event = 2;
  }
  else if (event == 2) {
    lcd.setCursor(0, 1);
    lcd.print("CHECKING TEMP");
    delay(1500);
    clearLine(1);
    float tempF = mlx.readObjectTempF();
    beep(200);
    lcd.setCursor(0, 1);
    lcd.print((String)"TEMP: " + tempF + (char)223 + "F");
    delay(1500);

    if (tempF < 100) event = 3;
    else event = 4;
  }
  else if (event == 3) {
    lcd.setCursor(0, 1);
    lcd.print("YOUR ARE ALLOWED");
    gateOpen();

    long sMs = millis();
    while (digitalRead(ir2)) {
      if (millis() - sMs > 10000) {
        gateCount--;
        break;
      }
    }
    delay(500);
    gateClose();
    gateCount++;
    event = 0;
  }
  else if (event == 4) {
    lcd.setCursor(0, 1);
    lcd.print("YOU ARE DENIED!");
    beep(2000);
    event = 0;
  }

  if (event != oldEvent) {
    oldEvent = event;
    clearLine(1);
  }

  delay(100);
}

void gateOpen() {
  for (byte i = 1; i < 100; i++) {
    servo.write(i);
    delay(10);
  }
}

void gateClose() {
  for (byte i = 100; i > 1; i--) {
    servo.write(i);
    delay(10);
  }
}

void beep(int d) {
  digitalWrite(buzzer, 1);
  delay(d);
  digitalWrite(buzzer, 0);
}

void clearLine(byte l) {
  lcd.setCursor(0, l);
  for (byte i = 0; i < 16; i++) lcd.print(" ");
}
