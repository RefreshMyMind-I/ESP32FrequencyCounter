// FrequencyCounterESP32.cpp

#include "FrequencyCounterESP32.h"

FrequencyCounterESP32::FrequencyCounterESP32(int inputPin) {
  this->inputPin = inputPin;
  this->pulseCount = 0;
  this->lastPulseCount = 0;
  this->lastMillis = 0;
}

void FrequencyCounterESP32::begin() {
  pinMode(inputPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(inputPin), handlePulseStatic, RISING);
}

unsigned long FrequencyCounterESP32::getFrequency() {
  noInterrupts();
  unsigned long currentPulseCount = pulseCount;
  interrupts();

  unsigned long frequency = currentPulseCount - lastPulseCount;

  lastPulseCount = currentPulseCount;
  lastMillis = millis();

  return frequency;
}

void IRAM_ATTR FrequencyCounterESP32::handlePulseStatic(void* instance) {
  static_cast<FrequencyCounterESP32*>(instance)->handlePulse();
}

void FrequencyCounterESP32::handlePulse() {
  pulseCount++;
}
