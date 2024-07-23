#include <FastLED.h>

#include "neopixel.h"
#include "chromance.h"
#include "colourUtils.h"

// Members

CRGB leds1[numLEDs1];
CRGB leds2[numLEDs2];
CRGB leds3[numLEDs3];
CRGB leds4[numLEDs4];

// Constructor

NeoPixel::NeoPixel(int gpioPin, int leds) {
    Serial.println("Creating NeoPixel for pin " + pin);
    pin = gpioPin;
    numLEDs = leds;
    stripBrightness = 1;

    for (int i = 0; i < numLEDs; i++) {
        trueColours.push_back(CRGB::Black);
        pixelBrightnessValues.push_back(1);
        coloursToBlend.push_back(std::vector<CRGB>());
    }

    writeUpdates();
}

// Prviate Functions

CRGB* NeoPixel::getPixelsArray() {
    switch (pin) {
    case 16: return leds1;
    case 21: return leds2;
    case 22: return leds3;
    case 25: return leds4;
    }
}

// Public Functions

double NeoPixel::getCurrent() {
    double totalCurrent = 0;
    for (int i = 0; i < numLEDs; i++) {
        totalCurrent += ColourUtils::calculateColourCurrent(getPixelColour(i));
    }

    return totalCurrent;
}

double NeoPixel::getActualCurrent() {
    double totalCurrent = 0;
    for (int i = 0; i < numLEDs; i++) {
        totalCurrent += ColourUtils::calculateColourCurrent(ColourUtils::getColourAtBrightness(getPixelColour(i), pixelBrightnessValues[i] * stripBrightness));
    }

    return totalCurrent;
}

CRGB NeoPixel::getPixelColour(int index) {
    switch (Chromance::displayMode) {
    case Chromance::DisplayMode::absolute: return trueColours[index];
    case Chromance::sum: return ColourUtils::sumColours(coloursToBlend[index]);
    case Chromance::average: return ColourUtils::averageColours(coloursToBlend[index]);
    }
}

double NeoPixel::getPixelBrightness(int index) {
    return pixelBrightnessValues[index];
}

void NeoPixel::setPixelColour(int index, CRGB colour) {
    trueColours[index] = colour;
    pixelBrightnessValues[index] = 1;
}

void NeoPixel::setPixelBrightness(int index, double brightness) {
    pixelBrightnessValues[index] = brightness;
}

void NeoPixel::setStripBrightness(double brightness) {
    stripBrightness = brightness;
}

void NeoPixel::addToPixelColour(int index, CRGB colour) {
    coloursToBlend[index].push_back(colour);
}

void NeoPixel::off() {
    fill(CRGB::Black);
}

void NeoPixel::test() {
    fill(CRGB(0, 0, 5));
}

void NeoPixel::writeUpdates() {
    // if (pin == 16) {
    //     Serial.print("LED 0 num colours: ");
    //     Serial.println(coloursToBlend[0].size());
    // }

    CRGB* pixels = getPixelsArray();
    for (int i = 0; i < numLEDs; i++) {
        pixels[i] = ColourUtils::getColourAtBrightness(getPixelColour(i), getPixelBrightness(i) * stripBrightness);
    }
}

void NeoPixel::fill(CRGB colour) {
    for (int i = 0; i < numLEDs; i++) {
        setPixelColour(i, colour);
    }
}

void NeoPixel::fadePixel(int index, double amount) {
    double brightness = getPixelBrightness(index);
    if (brightness <= 0) return;

    brightness -= amount;
    if (brightness > 0) {
        setPixelBrightness(index, brightness);
    }
    else {
        setPixelColour(index, CRGB::Black);
    }
}

void NeoPixel::minorFadeAll() {
    for (int i = 0; i < numLEDs; i++) {
        fadePixel(i, 0.02);
    }
}

void NeoPixel::fadeAll() {
    for (int i = 0; i < numLEDs; i++) {
        fadePixel(i, 0.1);
    }
}

void NeoPixel::superFadeAll() {
    for (int i = 0; i < numLEDs; i++) {
        fadePixel(i, 0.5);
    }
}

void NeoPixel::clearBlendColours() {
    for (int i = 0; i < numLEDs; i++) {
        coloursToBlend[i].clear();
    }
}