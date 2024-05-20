#include <LiquidCrystal.h>
#include <EEPROM.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);

const int pinoPIR = 11;
const int pinoLED = 12;
int backLight = 9;
String quantityIndicator;

int counter = 0;

void setup(){
  Serial.begin(9600);
  counter = EEPROM.read(0);
  printLCD();
  pinMode(pinoLED, OUTPUT);
  pinMode(pinoPIR, INPUT);
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH);
}

void loop(){
  if(digitalRead(pinoPIR) == HIGH){
    digitalWrite(pinoLED, HIGH);
    counter = counter + 1;
    quantityIndicator = " vez";
    EEPROM.write(0, counter);
    printLCD();
    delay(5000);
 } else {
    digitalWrite(pinoLED, LOW);
 }
}

void printLCD() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("O gatinho tomou");
  lcd.setCursor(0, 1);
 
  if(EEPROM.read(0) == 0 || EEPROM.read(0) > 1 ) { 
    quantityIndicator = " vezes";
  }
  
  lcd.print(String("agua ") + String(EEPROM.read(0)) + quantityIndicator + String(" hj"));
}