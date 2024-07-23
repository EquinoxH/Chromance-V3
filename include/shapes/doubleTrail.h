#pragma once

#include <FastLED.h>
#include <vector>

#include "shapes/trail.h"

class DoubleTrail : public Trail {
private:
    double deviation;
    double getBrightnessAtPosition(int index);

public:
    DoubleTrail(CRGB _colour, int _start, int _length, int _speed, int _lifetime, bool _immortal, bool _deathEffect);
    void moveWithSpeed();
    void move() override;
    void show() override;
    void fade() override;
};