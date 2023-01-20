#include "SCD30.h"

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

void setup() {
    Wire.begin();
    SERIAL.begin(115200);
    scd30.initialize();
}

void loop() {
    float result[3] = {0};

    if (scd30.isAvailable()) {
        scd30.getCarbonDioxideConcentration(result);
        // CO2 in ppm
        SERIAL.print(result[0]);
        SERIAL.print(",");
        // Temp in C
        SERIAL.print(result[1]);
        SERIAL.print(",");
        // Humidity in %
        SERIAL.print(result[2]);

        SERIAL.println("");
    }

    delay(1000);
}
