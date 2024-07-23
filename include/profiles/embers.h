#pragma once

#include <vector>

class AsyncWebServer;

namespace Profiles {
    namespace Embers {
        extern int numEmbers;
        extern int speed;
        extern int spawnDelay;

        const std::vector<int> spawnLocations{
            377, 294, 322, 84, 69, 532, 14, 196, 266, 251, 504, 434
        };

        void setupCommand(AsyncWebServer& server);
        void restoreDefaults();
        void setProfile();
        void doUpdate();
    }
}