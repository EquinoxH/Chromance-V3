#pragma once

#include <vector>

class AsyncWebServer;

namespace Profiles {
    namespace Snowfall {
        extern int numFlakes;
        extern int speed;
        extern int spawnDelay;

        const std::vector<int> spawnLocations{
            364, 307, 335, 97, 56, 545, 27, 209, 279, 238, 517, 447
        };

        void setupCommand(AsyncWebServer& server);
        void restoreDefaults();
        void setProfile();
        void doUpdate();
    }
}