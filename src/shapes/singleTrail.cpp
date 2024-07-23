#include <FastLED.h>

#include "shapes/singleTrail.h"
#include "hub.h"
#include "chromance.h"
#include "debugTools.h"
#include "colourUtils.h"

// Constructor

SingleTrail::SingleTrail(CRGB _colour, int _start, int _lifetime, bool _immortal, int _speed, int _length, bool _deathEffect) {
    colour = _colour;
    currentPosition = _start;
    direction = _start % 2 == 0 ? 1 : -1;
    length = _length;
    lifetime = _lifetime;
    fadeProgress = 0;
    isAtStartOfSegment = true;
    immortal = _immortal;
    speed = _speed;
    deathEffect = _deathEffect;

    positionHistory.push_back(_start);
}

// Public Functions

void SingleTrail::moveWithSpeed() {
    for (int i = 0; i < speed; i++) {
        move();
    }
}

void SingleTrail::move() {
    if (!immortal) --lifetime;

    int nextPosition = 0;
    if (Hubs::ledIsStartOrEnd(currentPosition) && !isAtStartOfSegment) {
        Hub currentHub = Hubs::getConnectedHub(currentPosition);
        nextPosition = currentHub.getRandomLEDExcept(currentPosition);
        direction = nextPosition % 2 == 0 ? 1 : -1;
        isAtStartOfSegment = true;
        if (debugTrails) Serial.println("Arrived at " + String(currentPosition) + " | Next position: " + String(nextPosition));
    }
    else {
        nextPosition = currentPosition + direction;
        isAtStartOfSegment = false;
    }

    currentPosition = nextPosition;
    positionHistory.push_back(currentPosition);
    if (positionHistory.size() >= length) {
        positionHistory.erase(positionHistory.begin());
    }

    show();
}

void SingleTrail::show() {
    for (int i = 0; i < positionHistory.size(); i++) {
        double brightness = i / (double)length;
        CRGB pixelColour = ColourUtils::getColourAtBrightness(colour, brightness);

        if (Chromance::displayMode == Chromance::absolute) {
            Chromance::setLEDColour(positionHistory[i], pixelColour);
        }
        else {
            Chromance::addToLEDColour(positionHistory[i], pixelColour);
        }
    }
}

void SingleTrail::fade() {
    fadeProgress += 0.1;
    for (int i = 0; i < positionHistory.size(); i++) {
        double brightness = i / (double)length;
        brightness *= (1.0 - fadeProgress);
        CRGB pixelColour = ColourUtils::getColourAtBrightness(colour, brightness);

        if (Chromance::displayMode == Chromance::absolute) {
            Chromance::setLEDColour(positionHistory[i], pixelColour);
        }
        else {
            Chromance::addToLEDColour(positionHistory[i], pixelColour);
        }
    }
}