#pragma once

#include <FastLED.h>
#include "shapes/trail.h"

class SlowTrail : public Trail {
private:
    int targetPosition;
    int progress;

public:
    SlowTrail(CRGB _colour, int _start, int _lifetime, int _immortal, int _speed, bool _deathEffect);
    void move() override;
    void show() override;
};