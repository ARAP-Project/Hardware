#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "commands.h"

namespace Led {
    void init();
    void update();
    void setMode(LedMode mode);
    LedMode getMode();
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setBrightness(uint8_t brightness);
    void clear();
    void onRobotStateChange(RobotState state);
    void showDirection(int16_t left, int16_t right);
}

#endif
