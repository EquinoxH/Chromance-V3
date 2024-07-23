#pragma once

class AsyncWebServer;

namespace Profiles {
    namespace Pulse {
        extern bool bigMode;
        extern int trailSpeed;
        extern int trailLength;

        void setupCommand(AsyncWebServer& server);
        void restoreDefaults();
        void setProfile();
        void doUpdate();
    }
}