#pragma once

#include <FastLED.h>
#include <vector>

class AsyncWebServer;

namespace Profiles {
    namespace Aurora {
        extern int numTrailsPerColour;
        extern int trailLength;
        extern int spawnDelay;
        extern int trailSpeed;

        const std::vector<CRGB> colours{ CRGB::Red, CRGB::Green };

        void setupCommand(AsyncWebServer& server);
        void restoreDefaults();
        void setProfile();
        void doUpdate();
    }
}