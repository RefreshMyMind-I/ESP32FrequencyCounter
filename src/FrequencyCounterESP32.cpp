// FrequencyCounterESP32.cpp

#include "FrequencyCounterESP32.h"

FrequencyCounterESP32* FrequencyCounterESP32::instance = nullptr;  // Add this line

FrequencyCounterESP32::FrequencyCounterESP32(int inputPin) {
  this->inputPin = inputPin;
  this->pulseCount = 0;
  this->lastPulseCount = 0;
  this->lastMillis = 0;
  instance = this;
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

void IRAM_ATTR FrequencyCounterESP32::handlePulseStatic() {
  if (instance) {
    instance->handlePulse();
  }
}

void FrequencyCounterESP32::handlePulse() {
  pulseCount++;
}
