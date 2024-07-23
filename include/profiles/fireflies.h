#pragma once

class AsyncWebServer;

namespace Profiles {
    namespace Fireflies {
        extern int numFireflies;
        extern int lifetime;
        extern int spawnDelay;

        void setupCommand(AsyncWebServer& server);
        void restoreDefaults();
        void setProfile();
        void doUpdate();
    }
}