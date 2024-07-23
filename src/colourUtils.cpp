#include "colourUtils.h"
#include "myRandom.h"

double ColourUtils::calculateColourCurrent(CRGB colour) {
    return 55 * ((colour.r + colour.g + colour.b) / (3.0 * 255.0));
}

CRGB ColourUtils::sumColours(std::vector<CRGB>& colours) {
    if (colours.size() == 0) return CRGB::Black;

    int totalR = 0;
    int totalG = 0;
    int totalB = 0;

    for (CRGB colour : colours) {
        totalR += colour.r;
        totalG += colour.g;
        totalB += colour.b;
    }

    if (totalR > 255) totalR = 255;
    if (totalG > 255) totalG = 255;
    if (totalB > 255) totalB = 255;

    return CRGB(totalR, totalG, totalB);
}

CRGB ColourUtils::averageColours(std::vector<CRGB>& colours) {
    if (colours.size() == 0) return CRGB::Black;

    int totalR = 0;
    int totalG = 0;
    int totalB = 0;

    for (CRGB colour : colours) {
        totalR += colour.r;
        totalG += colour.g;
        totalB += colour.b;
    }

    totalR /= colours.size();
    totalG /= colours.size();
    totalB /= colours.size();

    return CRGB(totalR, totalG, totalB);
}

CRGB ColourUtils::getColourAtBrightness(CRGB colour, double brightness) {
    int r = colour.r * brightness;
    int g = colour.g * brightness;
    int b = colour.b * brightness;
    return CRGB(r, g, b);
}

CRGB ColourUtils::getRandomColour() {
    int r = Random::getRandomInt(255);
    int g = Random::getRandomInt(255);
    int b = Random::getRandomInt(255);
    return CRGB(r, g, b);
}

CRGB ColourUtils::getMeteorColour() {
    int g = Random::getRandomInt(128);
    return CRGB(255, g, 0);
}

String ColourUtils::colourToString(CRGB colour) {
    return "(" + String(colour.r) + "," + String(colour.g) + "," + String(colour.b) + ")";
}

CRGB ColourUtils::colourFromString(String string) {
    int commaIndex1 = string.indexOf(',');
    int commaIndex2 = string.indexOf(',', commaIndex1 + 1);

    String redString = string.substring(0, commaIndex1);
    String greenString = string.substring(commaIndex1 + 1, commaIndex2);
    String blueString = string.substring(commaIndex2 + 1);

    int red = redString.toInt();
    int green = greenString.toInt();
    int blue = blueString.toInt();

    return CRGB(red, green, blue);
}