#pragma once

#include <FastLED.h>

class Dot {
private:
    CRGB colour;
    int location;
    int lifetime;
    int startLifeTime;

    void show();

public:
    Dot(CRGB _colour, int _location, int _lifetime);

    void update();
    bool shouldDie();
};