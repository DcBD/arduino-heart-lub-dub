#ifndef ArduinoHeartLubDub_H_
#define ArduinoHeartLubDub_H_

#include <Arduino.h>

void cardiacCycle(
    const int bpm,
    void (*lub)(),
    void afterLub(),
    void (*dub)(),
    void afterDub());

#endif