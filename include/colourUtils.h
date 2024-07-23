#pragma once

#include <FastLED.h>
#include <vector>

namespace ColourUtils {
    double calculateColourCurrent(CRGB colour);
    CRGB sumColours(std::vector<CRGB>& colours);
    CRGB averageColours(std::vector<CRGB>& colours);
    CRGB getColourAtBrightness(CRGB colour, double brightness);
    CRGB getRandomColour();
    CRGB getMeteorColour();
    String colourToString(CRGB colour);
    CRGB colourFromString(String string);
}