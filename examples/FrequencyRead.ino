#include <Arduino.h>
#include "FrequencyCounterESP32.h"

const int inputPin = 2;  // Change this to the pin you are using

FrequencyCounterESP32 frequencyCounter(inputPin);

void setup() {
  Serial.begin(115200);
  frequencyCounter.begin();
}

void loop() {
  unsigned long frequency = frequencyCounter.getFrequency();
  Serial.print("Frequency: ");
  Serial.print(frequency);
  Serial.println(" Hz");
  delay(1000);
}
