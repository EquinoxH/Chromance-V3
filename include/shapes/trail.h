#pragma once

#include <vector>
#include <FastLED.h>

class Trail {
protected:
    CRGB colour;
    int length;
    int lifetime;

    int currentPosition;
    std::vector<int> positionHistory;
    int direction;
    double speed;

    double fadeProgress;
    bool isAtStartOfSegment;
    bool immortal;
    bool deathEffect;

public:
    virtual void move();
    virtual void show();
    virtual void fade();

    int getCurrentPosition();
    int getCurrentDirection();

    bool shouldDie();
    bool hasDeathEffect();
    bool fadeComplete();
};