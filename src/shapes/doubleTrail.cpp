#include <math.h>

#include "shapes/doubleTrail.h"
#include "hub.h"
#include "chromance.h"
#include "debugTools.h"
#include "colourUtils.h"

// Constructor

DoubleTrail::DoubleTrail(CRGB _colour, int _start, int _length, int _speed, int _lifetime, bool _immortal, bool _deathEffect) {
    colour = _colour;
    currentPosition = _start;
    length = _length;
    speed = _speed;
    lifetime = _lifetime;
    immortal = _immortal;
    deathEffect = _deathEffect;

    positionHistory.push_back(currentPosition);
    direction = _start % 2 == 0 ? 1 : -1;
    isAtStartOfSegment = true;
    deviation = length / 8.0;
    fadeProgress = 0;
}

// Public Functions

void DoubleTrail::moveWithSpeed() {
    for (int i = 0; i < speed; i++) {
        move();
    }
}

void DoubleTrail::move() {
    int nextPosition = 0;
    if (Hubs::ledIsStartOrEnd(currentPosition) && !isAtStartOfSegment) {
        Hub currentHub = Hubs::getConnectedHub(currentPosition);
        nextPosition = currentHub.getRandomLEDExcept(currentPosition);
        direction = nextPosition % 2 == 0 ? 1 : -1;
        isAtStartOfSegment = true;
    }
    else {
        nextPosition = currentPosition + direction;
        isAtStartOfSegment = false;
    }

    currentPosition = nextPosition;
    positionHistory.push_back(currentPosition);
    if (positionHistory.size() > length) {
        positionHistory.erase(positionHistory.begin());
    }

    show();

    if (!immortal) {
        --lifetime;
    }
}

void DoubleTrail::show() {
    for (int i = 0; i < positionHistory.size(); i++) {
        double brightness = getBrightnessAtPosition(i);
        CRGB pixelColour = ColourUtils::getColourAtBrightness(colour, brightness);
        if (Chromance::displayMode == Chromance::absolute) {
            Chromance::setLEDColour(positionHistory[i], pixelColour);
        }
        else {
            Chromance::addToLEDColour(positionHistory[i], pixelColour);
        }
    }
}

void DoubleTrail::fade() {
    fadeProgress += 2 / (double)length;
    for (int i = 0; i < positionHistory.size(); i++) {
        double brightness = getBrightnessAtPosition(i);
        brightness *= (1 - fadeProgress);
        CRGB pixelColour = ColourUtils::getColourAtBrightness(colour, brightness);

        if (Chromance::displayMode == Chromance::absolute) {
            Chromance::setLEDColour(positionHistory[i], pixelColour);
        }
        else {
            Chromance::addToLEDColour(positionHistory[i], pixelColour);
        }
    }
}

// Private Functions

double DoubleTrail::getBrightnessAtPosition(int index) {
    double mean = (length - 1) / 2.0;
    double x = index - mean;
    double exponent = -0.5 * pow(x / deviation, 2);
    double amplitude = 1.0 / (deviation * sqrt(2 * M_PI));
    double brightness = amplitude * exp(exponent);

    if (index == 0 || index == length - 1) {
        brightness = 0.0;
    }
    else {
        brightness /= amplitude;
    }

    return brightness;
}