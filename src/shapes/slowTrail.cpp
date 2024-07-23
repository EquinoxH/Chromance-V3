#include <FastLED.h>

#include "shapes/slowTrail.h"
#include "hub.h"
#include "chromance.h"
#include "debugTools.h"
#include "colourUtils.h"

// Constructor

SlowTrail::SlowTrail(CRGB _colour, int _start, int _lifetime, int _immortal, int _speed, bool _deathEffect) {
    colour = _colour;
    currentPosition = _start;
    targetPosition = -1;
    direction = _start % 2 == 0 ? 1 : -1;
    lifetime = _lifetime;
    isAtStartOfSegment = true;
    immortal = _immortal;
    speed = _speed;
    progress = 0;
    deathEffect = _deathEffect;
}

// Public Functions

void SlowTrail::move() {
    if (debugSlowTrails) printf("Current Position: %d\n", currentPosition);

    // Find Next Position
    bool arrivedAtHub = false;
    if (targetPosition == -1) {
        if (Hubs::ledIsStartOrEnd(currentPosition) && !isAtStartOfSegment) {
            printf("Arrived at hub\n");
            Hub currentHub = Hubs::getConnectedHub(currentPosition);
            targetPosition = currentHub.getRandomLEDExcept(currentPosition);
            arrivedAtHub = true;
            if (debugSlowTrails) printf("Picked New Hub Target: %d\n", targetPosition);
        }
        else {
            targetPosition = currentPosition + direction;
            if (debugSlowTrails) printf("Picked New Target: %d = %d + %d\n", targetPosition, currentPosition, direction);
        }
    }

    progress += speed;
    if (progress > 100) progress = 100;

    Chromance::setLEDColour(currentPosition, ColourUtils::getColourAtBrightness(colour, (1 - (progress / 100.0))));
    Chromance::setLEDColour(targetPosition, ColourUtils::getColourAtBrightness(colour, (progress / 100.0)));

    if (progress == 100) {
        isAtStartOfSegment = Hubs::ledIsStartOrEnd(currentPosition) && Hubs::ledIsStartOrEnd(targetPosition);

        currentPosition = targetPosition;
        targetPosition = -1;
        progress = 0;

        if (isAtStartOfSegment) direction = currentPosition % 2 == 0 ? 1 : -1;
        if (!immortal) --lifetime;
    }
}

void SlowTrail::show() {
    if (Chromance::displayMode == Chromance::absolute) {
        Chromance::setLEDColour(currentPosition, colour);
    }
    else {
        Chromance::addToLEDColour(currentPosition, colour);
    }
}