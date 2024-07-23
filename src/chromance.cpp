#include <algorithm>
#include <string>
#include <chrono>

#include "profileManager.h"
#include "chromance.h"
#include "debugTools.h"
#include "utils.h"
#include "neopixel.h"
#include "colourUtils.h"

#include "shapes/singleTrail.h"
#include "shapes/slowTrail.h"
#include "shapes/doubleTrail.h"
#include "shapes/segment.h"
#include "shapes/dot.h"

namespace Chromance {
    const double currentLimit = debugMode ? 1000.0 : 9600.0;
    int speed = 10;
    int fps = 30;
    bool trackCurrent = false;
    std::string profile = "rgb";
    DisplayMode displayMode = absolute;
    CRGB backgroundColour = CRGB::Black;

    NeoPixel strip0(16, 168); // Green Network
    NeoPixel strip1(21, 154); // Black Network
    NeoPixel strip2(22, 84); // Red Network
    NeoPixel strip3(25, 154); // Blue Network

    std::vector<SingleTrail*> trails;
    std::vector<SlowTrail> slowTrails;
    std::vector<DoubleTrail*> doubleTrails;
    std::vector<Segment> segments;
    std::vector<Dot> dots;

    std::vector<SingleTrail*> deadTrails;
    std::map<SingleTrail*, int> trailFadesRemainingMap;

    std::vector<DoubleTrail*> deadDoubleTrails;
    std::map<DoubleTrail*, int> doubleTrailFadesRemainingMap;

    // Create Shape Functions

    void createTrail(CRGB colour = CRGB::Red, int start = 0, int lifetime = 140, bool isImmortal = false, double speed = 1, int length = 14, bool hasDeathEffect = false) {
        trails.push_back(new SingleTrail(colour, start, lifetime, isImmortal, speed, length, hasDeathEffect));
    }

    void createSlowTrail(CRGB colour = CRGB::Red, int start = 0, int lifetime = 140, bool isImmortal = false, int speed = 10, bool hasDeathEffect = false) {
        slowTrails.push_back(SlowTrail(colour, start, lifetime, isImmortal, speed, hasDeathEffect));
    }

    void createDoubleTrail(CRGB colour = CRGB::Red, int start = 0, int trailLength = 20, int speed = 1, int lifetime = 140, bool isImmortal = false, bool deathEffect = false) {
        doubleTrails.push_back(new DoubleTrail(colour, start, trailLength, speed, lifetime, isImmortal, deathEffect));
    }

    void createSegment(int segmentID = 0, std::vector<CRGB> colours = std::vector<CRGB>{ CRGB::Red }, int startIndex = 0) {
        segments.push_back(Segment(segmentID, colours, startIndex));
    }

    void createDot(CRGB colour = CRGB::Red, int start = 0, int lifetime = 140) {
        dots.push_back(Dot(colour, start, lifetime));
    }

    // Shape Functions

    int getNumTrails() {
        return trails.size() + deadTrails.size();
    }

    int getNumSlowTrails() {
        return slowTrails.size();
    }

    int getNumDoubleTrails() {
        return doubleTrails.size();
    }

    int getNumSegments() {
        return segments.size();
    }

    int getNumDots() {
        return dots.size();
    }

    void clearSegments() {
        if (segments.size() > 0) {
            off();
            segments = std::vector<Segment>();
        }
    }

    // Strip Functions

    void off() {
        strip0.off();
        strip1.off();
        strip2.off();
        strip3.off();
    }

    void test() {
        strip0.test();
        strip1.test();
        strip2.test();
        strip3.test();
    }

    void fill(CRGB colour) {
        strip0.fill(colour);
        strip1.fill(colour);
        strip2.fill(colour);
        strip3.fill(colour);
    }

    void addBackgroundToBlend() {
        for (int i = 0; i < 560; i++) {
            addToLEDColour(i, backgroundColour);
        }
    }

    void identify() {
        strip0.fill(CRGB(5, 0, 0));
        strip1.fill(CRGB(0, 5, 0));
        strip2.fill(CRGB(0, 0, 5));
        strip3.fill(CRGB(5, 0, 5));
    }

    void writeUpdates() {
        strip0.writeUpdates();
        strip1.writeUpdates();
        strip2.writeUpdates();
        strip3.writeUpdates();
        FastLED.show();
    }

    void minorFadeAll() {
        strip0.minorFadeAll();
        strip1.minorFadeAll();
        strip2.minorFadeAll();
        strip3.minorFadeAll();
    }

    void fadeAll() {
        strip0.fadeAll();
        strip1.fadeAll();
        strip2.fadeAll();
        strip3.fadeAll();
    }

    void superFadeAll() {
        strip0.superFadeAll();
        strip1.superFadeAll();
        strip2.superFadeAll();
        strip3.superFadeAll();
    }

    void clearBlendColours() {
        strip0.clearBlendColours();
        strip1.clearBlendColours();
        strip2.clearBlendColours();
        strip3.clearBlendColours();
    }

    // Update Shape Functions

    namespace {
        void updateTrails() {
            for (int i = 0; i < trails.size();) {
                SingleTrail* trail = trails[i];
                trail->moveWithSpeed();

                if (trail->shouldDie()) {
                    if (trail->hasDeathEffect()) {
                        int position = trail->getCurrentPosition() + trail->getCurrentDirection();
                        ProfileManager::onDeath(profile, position);
                    }

                    deadTrails.push_back(trail);
                    trailFadesRemainingMap[trail] = 10;
                    if (debugDeadTrails) printf("Adding trail %p to dead trails\n", trail);
                    trails.erase(trails.begin() + i);
                }
                else {
                    ++i;
                }
            }
        }

        void updateSlowTrails() {
            for (int i = 0; i < slowTrails.size();) {
                slowTrails[i].move();
                if (slowTrails[i].shouldDie()) {
                    if (slowTrails[i].hasDeathEffect()) {
                        int position = slowTrails[i].getCurrentPosition() + slowTrails[i].getCurrentDirection();
                        ProfileManager::onDeath(profile, position);
                    }
                    Chromance::setLEDColour(slowTrails[i].getCurrentPosition(), CRGB::Black);
                    slowTrails.erase(slowTrails.begin() + i);
                }
                else {
                    i++;
                }
            }
        }

        void updateDoubleTrails() {
            for (int i = 0; i < doubleTrails.size();) {
                DoubleTrail* trail = doubleTrails[i];
                trail->moveWithSpeed();
                if (trail->shouldDie()) {
                    if (trail->hasDeathEffect()) {
                        int position = trail->getCurrentPosition() + trail->getCurrentDirection();
                        ProfileManager::onDeath(profile, position);
                    }

                    deadDoubleTrails.push_back(trail);
                    doubleTrailFadesRemainingMap[trail] = 10;
                    doubleTrails.erase(doubleTrails.begin() + i);
                }
                else {
                    i++;
                }
            }
        }

        void updateSegments() {
            for (int i = 0; i < segments.size(); i++) {
                segments[i].update();
            }
        }

        void updateDots() {
            for (int i = 0; i < dots.size();) {
                dots[i].update();
                if (dots[i].shouldDie()) {
                    dots.erase(dots.begin() + i);
                }
                else {
                    i++;
                }
            }
        }

        void fadeDeadTrails() {
            if (debugDeadTrails) printf("Fading %d dead trails\n", deadTrails.size());
            for (int i = 0; i < deadTrails.size(); ) {
                SingleTrail* trail = deadTrails[i];

                trail->fade();
                --trailFadesRemainingMap[trail];

                // if(i == 0 && debugDeadTrails) printf("Trail %p has %d fades remaining\n", trail, fadesRemaining);

                if (trailFadesRemainingMap[trail] <= 0) {
                    trailFadesRemainingMap.erase(trail);
                    delete trail;
                    deadTrails.erase(deadTrails.begin() + i);
                }
                else {
                    ++i;
                }
            }
        }

        void fadeDeadDoubleTrails() {
            for (int i = 0; i < deadDoubleTrails.size();) {
                DoubleTrail* trail = deadDoubleTrails[i];
                trail->fade();
                --doubleTrailFadesRemainingMap[trail];

                if (trail->fadeComplete()) {
                    doubleTrailFadesRemainingMap.erase(trail);
                    deadDoubleTrails.erase(deadDoubleTrails.begin() + i);
                    delete trail;
                }
                else {
                    i++;
                }
            }
        }
    }

    void doUpdate() {
        auto start = std::chrono::high_resolution_clock::now();

        if (Chromance::displayMode != Chromance::absolute) {
            clearBlendColours();
            addBackgroundToBlend();
        }
        else {
            fill(backgroundColour);
        }

        updateTrails();
        updateSlowTrails();
        updateDoubleTrails();
        updateSegments();
        updateDots();

        fadeDeadTrails();
        fadeDeadDoubleTrails();

        ProfileManager::doUpdate(profile);
        setBrightness();
        writeUpdates();

        auto end = std::chrono::high_resolution_clock::now();
        double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        double frameDelay = 1000 / (double)fps;
        frameDelay -= elapsed;
        if (frameDelay <= 0) {
            frameDelay = 0;
        }
        else {
            delay(frameDelay);
        }

        if (debugUpdateTime) {
            Serial.print("Update time (update/update+framedelay) ms: (");
            Serial.print(elapsed);
            Serial.print(" / ");
            Serial.print(elapsed + frameDelay);
            Serial.println(")");
        }

        if (debugCurrent) {
            Serial.print("Current (actual / planned): (");
            Serial.print(getActualCurrent());
            Serial.print(" / ");
            Serial.print(getCurrent());
            Serial.println(")");
        }
    }

    double getCurrent() {
        double current = 0;
        current += strip0.getCurrent();
        current += strip1.getCurrent();
        current += strip2.getCurrent();
        current += strip3.getCurrent();
        return current;
    }

    double getActualCurrent() {
        double current = 0;
        current += strip0.getActualCurrent();
        current += strip1.getActualCurrent();
        current += strip2.getActualCurrent();
        current += strip3.getActualCurrent();
        return current;
    }

    double calculateBrightnessLimit() {
        double current = getCurrent();
        return current < currentLimit ? 1 : currentLimit / current;
    }

    void setBrightness() {
        double brightness = calculateBrightnessLimit();
        strip0.setStripBrightness(brightness);
        strip1.setStripBrightness(brightness);
        strip2.setStripBrightness(brightness);
        strip3.setStripBrightness(brightness);
    }

    NeoPixel& getStrip(int stripID) {
        switch (stripID) {
        case 0: return strip0;
        case 1: return strip1;
        case 2: return strip2;
        case 3: return strip3;
        default: return strip0;
        }
    }

    CRGB getLED(int stripID, int index) {
        return getStrip(stripID).getPixelColour(index);
    }

    CRGB getLED(int ledNumber) {
        int stripID = 0;
        int index = 0;

        if (ledNumber < 168) {
            index = ledNumber;
        }
        else if (ledNumber < 322) {
            stripID = 1;
            index = ledNumber - 168;
        }
        else if (ledNumber < 406) {
            stripID = 2;
            index = ledNumber - 322;
        }
        else {
            stripID = 3;
            index = ledNumber - 406;
        }

        return getLED(stripID, index);
    }

    void fadeLED(int stripID, int index, double amount) {
        getStrip(stripID).fadePixel(index, amount);
    }

    void fadeLED(int ledNumber, double amount) {
        int stripID = 0;
        int index = 0;

        if (ledNumber < 168) {
            index = ledNumber;
        }
        else if (ledNumber < 322) {
            stripID = 1;
            index = ledNumber - 168;
        }
        else if (ledNumber < 406) {
            stripID = 2;
            index = ledNumber - 322;
        }
        else {
            stripID = 3;
            index = ledNumber - 406;
        }

        fadeLED(stripID, index, amount);
    }

    void setLEDColour(int stripID, int index, CRGB colour) {
        getStrip(stripID).setPixelColour(index, colour);
    }

    void setLEDColour(int ledNumber, CRGB colour) {
        int stripID = 0;
        int index = 0;

        if (ledNumber < 168) {
            index = ledNumber;
        }
        else if (ledNumber < 322) {
            stripID = 1;
            index = ledNumber - 168;
        }
        else if (ledNumber < 406) {
            stripID = 2;
            index = ledNumber - 322;
        }
        else {
            stripID = 3;
            index = ledNumber - 406;
        }

        setLEDColour(stripID, index, colour);
    }

    void addToLEDColour(int stripID, int index, CRGB colour) {
        getStrip(stripID).addToPixelColour(index, colour);
    }

    void addToLEDColour(int ledNumber, CRGB colour) {
        int stripID = 0;
        int index = 0;

        if (ledNumber < 168) {
            index = ledNumber;
        }
        else if (ledNumber < 322) {
            stripID = 1;
            index = ledNumber - 168;
        }
        else if (ledNumber < 406) {
            stripID = 2;
            index = ledNumber - 322;
        }
        else {
            stripID = 3;
            index = ledNumber - 406;
        }

        addToLEDColour(stripID, index, colour);
    }
}