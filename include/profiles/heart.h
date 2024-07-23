#pragma once

#include <FastLED.h>
#include <vector>

class AsyncWebServer;

namespace Profiles {
    namespace Heart {
        const std::vector<int> segments{ 7, 11, 38, 31, 30, 29, 12, 13, 14, 21, 22, 10, 6 };
        const std::vector<CRGB> colours{
            CRGB::HotPink,
            CRGB::LightCoral,
            CRGB::DeepPink,
            CRGB::Fuchsia,
            CRGB::Magenta,
            CRGB::Violet,
            CRGB::Magenta,
            CRGB::Fuchsia,
            CRGB::DeepPink,
            CRGB::LightCoral
        };

        void setupCommand(AsyncWebServer& server);
        void setProfile();
        void doUpdate();
    }
}