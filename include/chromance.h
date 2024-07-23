#pragma once

#include <map>
#include <string>
#include <FastLED.h>
#include <vector>

class NeoPixel;
class SingleTrail;
class SlowTrail;
class DoubleTrail;
class Segment;
class Dot;

namespace Chromance {
    enum DisplayMode {
        absolute,
        sum,
        average
    };

    // Members
    extern const double currentLimit;
    extern int speed;
    extern int fps;
    extern bool trackCurrent;
    extern std::string profile;
    extern DisplayMode displayMode;
    extern CRGB backgroundColour;

    extern NeoPixel strip0;
    extern NeoPixel strip1;
    extern NeoPixel strip2;
    extern NeoPixel strip3;

    extern int updateCount;

    extern std::vector<SingleTrail*> trails;
    extern std::vector<SlowTrail> slowTrails;
    extern std::vector<DoubleTrail*> doubleTrails;
    extern std::vector<Segment> segments;
    extern std::vector<Dot> dots;

    extern std::vector<SingleTrail*> deadTrails;
    extern std::map<SingleTrail*, int> trailFadesRemainingMap;

    extern std::vector<DoubleTrail*> deadDoubleTrails;
    extern std::map<DoubleTrail*, int> doubleTrailFadesRemainingMap;

    // Create Shape Functions

    void createTrail(CRGB colour, int start, int lifetime, bool immortal, double speed, int length, bool hasDeathEffect);
    void createSlowTrail(CRGB colour, int start, int lifetime, bool immortal, int speed, bool hasDeathEffect);
    void createDoubleTrail(CRGB colour, int start, int trailLength, int speed, int lifetime, bool immortal, bool hasDeathEffect);
    void createSegment(int segmentID, std::vector<CRGB> colours, int startIndex);
    void createDot(CRGB colour, int start, int lifetime);
    void createCircle(CRGB colour, int hubID, int lifetime);

    // Shape Functions

    int getNumTrails();
    int getNumSlowTrails();
    int getNumDoubleTrails();
    int getNumSegments();
    int getNumDots();

    void clearSegments();

    // Strip Functions

    void off();
    void test();
    void fill(CRGB colour);
    void addBackgroundToBlend();
    void identify();
    void writeUpdates();

    void minorFadeAll();
    void fadeAll();
    void superFadeAll();
    void clearBlendColours();
    void doUpdate();

    double getCurrent();
    double getActualCurrent();
    double calculateBrightnessLimit();
    void setBrightness();
    // int getNumOnLEDs();

    NeoPixel& getStrip(int stripID);
    CRGB getLED(int stripID, int index);
    CRGB getLED(int ledNumber);

    void fadeLED(int stripID, int index, double amount);
    void fadeLED(int ledNumber, double amount);

    void setLEDColour(int stripID, int index, CRGB colour);
    void setLEDColour(int ledNumber, CRGB colour);

    void addToLEDColour(int stripID, int index, CRGB colour);
    void addToLEDColour(int ledNumber, CRGB colour);
}