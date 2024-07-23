#pragma once

class CRGB;
class AsyncWebServer;

namespace Profiles {
    namespace Warning {
        extern int numTrails;
        extern int trailLength;
        extern int spawnDelay;
        extern int trailSpeed;
        extern int lifetime;
        extern CRGB colour;

        void setupCommand(AsyncWebServer& server);
        void restoreDefaults();
        void setProfile();
        void doUpdate();
    }
}