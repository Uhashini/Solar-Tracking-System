#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo sg90;

int initial_position = 90;
int LDR1 = A0;
int LDR2 = A1;
int tempSensorPin = A2;
int servopin = 9;

int nightModeThreshold = 200;
int maxLightDifference = 200;
bool isNightModeActive = false;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  sg90.attach(servopin);
  sg90.write(initial_position);

  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  int R1 = analogRead(LDR1);
  int R2 = analogRead(LDR2);
  float temperature = readTemperature();

  int diff = R1 - R2;

  if (isNightMode(R1, R2)) {
    activateNightMode();
  } else {
    deactivateNightMode();
    controlServo(diff);
  }

  if (!isNightModeActive) {
    displayInfo(diff, temperature);
  }

  plotData(R1, R2, temperature, initial_position);

  delay(500);
}

// ---------------------- FUNCTIONS ------------------------

float readTemperature() {
  float voltage = analogRead(tempSensorPin) * (5.0 / 1023.0);
  float temperatureC = voltage * 100.0;   // LM35
  return temperatureC;
}

bool isNightMode(int R1, int R2) {
  return (R1 < nightModeThreshold && R2 < nightModeThreshold);
}

void activateNightMode() {
  if (!isNightModeActive) {
    isNightModeActive = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Night Mode");
    lcd.setCursor(0, 1);
    lcd.print("Servo Locked");
    sg90.write(90); // lock to center
  }
}

void deactivateNightMode() {
  if (isNightModeActive) {
    isNightModeActive = false;
    lcd.clear();
  }
}

void controlServo(int diff) {
  int errorMargin = map(abs(diff), 0, maxLightDifference, 10, 2);

  if (abs(diff) > errorMargin) {
    int adjustment = map(diff, -maxLightDifference, maxLightDifference, -10, 10);
    initial_position = constrain(initial_position + adjustment, 0, 180);
    sg90.write(initial_position);
    delay(100);
  }
}

void displayInfo(int diff, float temperature) {
  lcd.setCursor(0, 0);
  lcd.print("Angle:");
  lcd.print(initial_position);
  lcd.print("   ");

  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(temperature);
  lcd.print(" C   ");
}

void plotData(int R1, int R2, float temperature, int angle) {
  Serial.print("LDR1:");
  Serial.print(R1);
  Serial.print("\tLDR2:");
  Serial.print(R2);
  Serial.print("\tTemperature:");
  Serial.print(temperature);
  Serial.print("\tAngle:");
  Serial.println(angle);
}
