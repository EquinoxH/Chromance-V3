#pragma once

#include <vector>
#include "FastLED.h"

const int ledPin1 = 16;
const int ledPin2 = 21;
const int ledPin3 = 22;
const int ledPin4 = 25;

const int numLEDs1 = 168;
const int numLEDs2 = 154;
const int numLEDs3 = 84;
const int numLEDs4 = 154;

extern CRGB leds1[numLEDs1];
extern CRGB leds2[numLEDs2];
extern CRGB leds3[numLEDs3];
extern CRGB leds4[numLEDs4];

class NeoPixel {
private:

    // Members
    int pin;
    int numLEDs;
    double stripBrightness;

    std::vector<CRGB> trueColours;
    std::vector<double> pixelBrightnessValues;
    std::vector<std::vector<CRGB>> coloursToBlend;

    // Functions
    CRGB* getPixelsArray();

public:

    // Constructor
    NeoPixel(int gpioPin, int leds);

    // Functions
    double getCurrent();
    double getActualCurrent();

    CRGB getPixelColour(int index);
    double getPixelBrightness(int index);

    void setPixelColour(int index, CRGB colour);
    void setPixelBrightness(int index, double brightness);
    void setStripBrightness(double brightness);

    void addToPixelColour(int index, CRGB colour);

    void off();
    void test();
    void fill(CRGB colour);
    void writeUpdates();

    void fadePixel(int index, double amount);
    void minorFadeAll();
    void fadeAll();
    void superFadeAll();
    void clearBlendColours();
};