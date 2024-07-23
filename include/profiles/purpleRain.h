#pragma once

#include <FastLED.h>
#include <vector>

class AsyncWebServer;

namespace Profiles {
    namespace PurpleRain {
        extern int numRaindrops;
        extern int spawnDelay;
        extern int trailSpeed;

        const std::vector<int> spawnLocations{
            364, 307, 335, 97, 56, 545, 27, 209, 279, 238, 517, 447
        };
        const std::vector<CRGB> colours{
            CRGB::BlueViolet,
            CRGB::DarkMagenta,
            CRGB::DarkSlateBlue,
            CRGB::DarkViolet,
            CRGB::DeepPink,
            CRGB::Fuchsia,
            CRGB::HotPink,
            CRGB::Lavender,
            CRGB::LavenderBlush,
            CRGB::Magenta,
            CRGB::MediumOrchid,
            CRGB::MediumPurple,
            CRGB::MediumVioletRed,
            CRGB::Orchid,
            CRGB::Plum,
            CRGB::Purple,
            CRGB::SlateBlue,
            CRGB::Thistle
        };

        void setupCommand(AsyncWebServer& server);
        void restoreDefaults();
        void setProfile();
        void doUpdate();
    }
}