#pragma once
#include <FastLED.h>
#include <vector>

class AsyncWebServer;

namespace Profiles {
    namespace Rainbow {
        const std::vector<int> innerSegments{
            21, 22, 28,
            6, 7, 10,
            11, 38, 39,
            19, 20, 34,
            5, 36, 37
        };
        const std::vector<int> outerSegments{
            9, 24, 25, 26, 27, 14, 13, 12,
            8, 3, 2, 1, 0, 31, 30, 29,
            15, 16, 23,
            4, 32, 33,
            17, 18, 35
        };
        const std::vector<CRGB> colours{
            CRGB::Red,
            CRGB::Orange,
            CRGB::Yellow,
            CRGB::Lime,
            CRGB::Blue,
            CRGB::Purple
        };

        void setupCommand(AsyncWebServer& server);
        void setProfile();
        void doUpdate();
    }
}