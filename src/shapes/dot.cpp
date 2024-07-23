#include "shapes/dot.h"
#include "chromance.h"

Dot::Dot(CRGB _colour, int _location, int _lifetime) {
    colour = _colour;
    location = _location;
    lifetime = _lifetime;
    startLifeTime = _lifetime;
}

void Dot::show() {
    Chromance::setLEDColour(location, colour);
    Chromance::fadeLED(location, 1 - (lifetime / (double)startLifeTime));
}

void Dot::update() {
    --lifetime;
    show();
}

bool Dot::shouldDie() {
    return lifetime == 0;
}