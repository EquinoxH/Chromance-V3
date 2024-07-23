#pragma once

class AsyncWebServer;

namespace Profiles {
    namespace RGB {
        extern int numTrails;
        extern int trailLength;
        extern int spawnDelay;
        extern int trailSpeed;

        void setupCommand(AsyncWebServer& server);
        void restoreDefaults();
        void setProfile();
        void doUpdate();
    }
}