#include "shapes/trail.h"

void Trail::move() {}
void Trail::show() {}
void Trail::fade() {}

int Trail::getCurrentPosition() {
    return currentPosition;
}

int Trail::getCurrentDirection() {
    return direction;
}

bool Trail::shouldDie() {
    return lifetime <= 0;
}

bool Trail::hasDeathEffect() {
    return deathEffect;
}

bool Trail::fadeComplete() {
    return fadeProgress >= 1;
}