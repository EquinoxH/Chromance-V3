#pragma once

#include <FastLED.h>
#include <vector>

class AsyncWebServer;

namespace Profiles {
    namespace Rainfall {
        extern int numRaindrops;
        extern int spawnDelay;
        extern int trailSpeed;

        const std::vector<int> spawnLocations{
            364, 307, 335, 97, 56, 545, 27, 209, 279, 238, 517, 447
        };
        const std::vector<CRGB> colours{
            CRGB::Aqua,
            CRGB::CornflowerBlue,
            CRGB::Cyan,
            CRGB::DarkBlue,
            CRGB::DarkTurquoise,
            CRGB::DeepSkyBlue,
            CRGB::DodgerBlue,
            CRGB::LightBlue,
            CRGB::LightCyan,
            CRGB::LightSkyBlue,
            CRGB::LightSteelBlue,
            CRGB::MediumBlue,
            CRGB::MidnightBlue,
            CRGB::Navy,
            CRGB::RoyalBlue,
            CRGB::SkyBlue
        };

        void setupCommand(AsyncWebServer& server);
        void restoreDefaults();
        void setProfile();
        void doUpdate();
    }
}