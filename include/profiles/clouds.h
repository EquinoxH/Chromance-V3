#pragma once

#include <FastLED.h>

class AsyncWebServer;

namespace Profiles {
    namespace Clouds {
        extern int numClouds;
        extern int cloudLength;
        extern int spawnDelay;
        extern int cloudSpeed;

        extern CRGB cloudColour;
        extern CRGB backgroundColour;

        void setupCommand(AsyncWebServer& server);
        void restoreDefaults();
        void setProfile();
        void doUpdate();
    }
}