#pragma once

#include <vector>

class AsyncWebServer;

namespace Profiles {
    namespace Blizzard {
        extern int numFlakes;
        extern int speed;
        extern int trailLength;
        extern int spawnDelay;

        const std::vector<int> spawnLocations{
            349, 125, 41, 405, 140, 154, 378, 224, 461, 293, 83, 195, 490
        };

        void setupCommand(AsyncWebServer& server);
        void restoreDefaults();
        void setProfile();
        void doUpdate();
    }
}