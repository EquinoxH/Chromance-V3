#pragma once

#include <FastLED.h>
#include <vector>

#include "trail.h"

class SingleTrail : public Trail {
public:
    SingleTrail(CRGB _colour, int _start, int _lifetime, bool _immortal, int _speed, int _length, bool _deathEffect);
    void moveWithSpeed();
    void move() override;
    void show() override;
    void fade() override;
};