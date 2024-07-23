#pragma once

#include <FastLED.h>
#include <vector>

class AsyncWebServer;

namespace Profiles {
    namespace Flower {
        const std::vector<int> innerSegments{ 6, 33, 5, 17, 34, 16 };
        const std::vector<int> outerSegments{ 7, 4, 32, 37, 36, 35, 18, 19, 20, 15, 23, 10 };
        const std::vector<CRGB> innerColours{ CRGB::Violet, CRGB::Magenta, CRGB::DeepPink, CRGB::Magenta };
        const std::vector<CRGB> outerColours{ CRGB::SpringGreen, CRGB::LawnGreen, CRGB::Lime, CRGB::LawnGreen };

        void setupCommand(AsyncWebServer& server);
        void setProfile();
        void doUpdate();
    }
}