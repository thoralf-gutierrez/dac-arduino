#include <SCD30.h>
#include <LiquidCrystal.h>

#if defined(ARDUINO_ARCH_AVR)
    #pragma message("Defined architecture for ARDUINO_ARCH_AVR.")
    #define SERIAL Serial
#elif defined(ARDUINO_ARCH_SAM)
    #pragma message("Defined architecture for ARDUINO_ARCH_SAM.")
    #define SERIAL SerialUSB
#elif defined(ARDUINO_ARCH_SAMD)
    #pragma message("Defined architecture for ARDUINO_ARCH_SAMD.")
    #define SERIAL SerialUSB
#elif defined(ARDUINO_ARCH_STM32F4)
    #pragma message("Defined architecture for ARDUINO_ARCH_STM32F4.")
    #define SERIAL SerialUSB
#else
    #pragma message("Not found any architecture.")
    #define SERIAL Serial
#endif

const int gatePin = 3;
const int buttonPin = 2;

// 1 is not pressed, 0 is pressed
int buttonOldState = 1;
int buttonCurrentState = 1;

// turned off
int fanState = LOW;

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(gatePin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  Serial.begin(9600);

  Wire.begin();
  scd30.initialize();

  lcd.begin(16, 2);
  lcd.print("Thor Industries");
}

void loop() {

  buttonCurrentState = digitalRead(buttonPin);

  if (buttonCurrentState != buttonOldState) {
    if (buttonCurrentState == 0) {
      // button just got pressed
      if (fanState == HIGH){
        fanState = LOW;
      } else {
        fanState = HIGH;
      }
    }
  }

  digitalWrite(gatePin, fanState);

  buttonOldState = buttonCurrentState;

  float result[3] = {0};

  if (scd30.isAvailable()) {
      scd30.getCarbonDioxideConcentration(result);
      // CO2 in ppm
      SERIAL.print(result[0]);
      SERIAL.print(",");
      lcd.setCursor(0, 1);
      lcd.print("CO2: ");
      lcd.print(result[0]);
      lcd.print(" ppm");

      // Temp in C
      SERIAL.print(result[1]);
      SERIAL.print(",");
      // Humidity in %
      SERIAL.print(result[2]);

      SERIAL.println("");
  }

  delay(100);
}
