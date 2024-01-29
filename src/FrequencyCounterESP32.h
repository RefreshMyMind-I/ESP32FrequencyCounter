// FrequencyCounterESP32.h

#ifndef FrequencyCounterESP32_h
#define FrequencyCounterESP32_h

#include <Arduino.h>

class FrequencyCounterESP32 {
public:
  FrequencyCounterESP32(int inputPin);
  void begin();
  unsigned long getFrequency();

private:
  int inputPin;
  volatile unsigned long pulseCount;
  unsigned long lastPulseCount;
  unsigned long lastMillis;

  static void IRAM_ATTR handlePulseStatic(void* instance);
  void handlePulse();
};

#endif
