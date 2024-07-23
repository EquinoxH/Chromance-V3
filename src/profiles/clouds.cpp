#include "profiles/clouds.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace Clouds {

        // Private Variables & Functions
        namespace {
            int lastSpawnLocation;
        }

        // Public Settings
        int numClouds = 6;
        int cloudLength = 80;
        int spawnDelay = 500;
        int cloudSpeed = 1;
        CRGB cloudColour = CRGB::White;
        CRGB backgroundColour = CRGB::DeepSkyBlue;

        // Public Functions

        void setupCommand(AsyncWebServer& server) {
            server.on("/clouds", HTTP_GET, [](AsyncWebServerRequest* request) {
                if (request->hasParam("numClouds")) numClouds = request->arg("numClouds").toInt();
                if (request->hasParam("cloudLength")) cloudLength = request->arg("cloudLength").toInt();
                if (request->hasParam("spawnDelay")) spawnDelay = request->arg("spawnDelay").toInt();
                if (request->hasParam("cloudSpeed")) cloudSpeed = request->arg("cloudSpeed").toInt();
                if (request->hasParam("defaults") && request->arg("defaults") == "true") restoreDefaults();

                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::clouds);
                MyNetwork::sendResponse(request, "Set profile to clouds");
                });
        }

        void restoreDefaults() {
            numClouds = 6;
            cloudLength = 80;
            spawnDelay = 500;
            cloudSpeed = 1;
            cloudColour = CRGB::White;
            backgroundColour = CRGB::DeepSkyBlue;
        }

        void setProfile() {
            Chromance::backgroundColour = backgroundColour;
            Chromance::displayMode = Chromance::sum;
            Chromance::profile = Profiles::clouds;
            Utils::logCurrentTime();
            lastSpawnLocation = -1;
        }

        void doUpdate() {
            if (Chromance::getNumDoubleTrails() >= numClouds) return;
            if (Utils::getMillisecondsSinceLog() < spawnDelay) return;

            int spawnLocation = Hubs::getRandom().getRandomLEDExcept(lastSpawnLocation);
            Chromance::createDoubleTrail(cloudColour, spawnLocation, cloudLength, cloudSpeed, 140, false, false);
            Utils::logCurrentTime();
            lastSpawnLocation = spawnLocation;
        }
    }
}