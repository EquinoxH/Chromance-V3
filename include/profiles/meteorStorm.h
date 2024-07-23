#pragma once

#include <FastLED.h>
#include <vector>

class AsyncWebServer;

namespace Profiles {
    namespace MeteorStorm {
        const std::vector<int> spawnLocations{
            349, 125, 41, 405, 140, 154, 378, 224, 461, 293, 83, 195, 490
        };

        void setupCommand(AsyncWebServer& server);
        void setProfile();
        void doUpdate();
    }
}