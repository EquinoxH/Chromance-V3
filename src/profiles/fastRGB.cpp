#include "profiles/fastRGB.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace FastRGB {

        // Private Variables & Functions
        namespace {
            int lastSpawnLocation;

            void spawnTrails() {
                if (Chromance::getNumTrails() >= numTrails) return;
                if (Utils::getMillisecondsSinceLog() < spawnDelay) return;

                int spawnLocation = Hubs::getRandom().getRandomLEDExcept(lastSpawnLocation);
                Chromance::createTrail(ColourUtils::getRandomColour(), spawnLocation, 70, false, trailSpeed, trailLength, false);
                Utils::logCurrentTime();
                lastSpawnLocation = spawnLocation;
            }
        }

        // Public Settings
        int numTrails = 10;
        int trailLength = 28;
        int spawnDelay = 250;
        int trailSpeed = 2;

        // Public Functions

        void setupCommand(AsyncWebServer& server) {
            server.on("/fastRGB", HTTP_GET, [](AsyncWebServerRequest* request) {
                if (request->hasParam("numTrails")) numTrails = request->arg("numTrails").toInt();
                if (request->hasParam("trailLength")) trailLength = request->arg("trailLength").toInt();
                if (request->hasParam("spawnDelay")) spawnDelay = request->arg("spawnDelay").toInt();
                if (request->hasParam("trailSpeed")) trailSpeed = request->arg("trailSpeed").toInt();
                if (request->hasParam("defaults") && request->arg("defaults") == "true") restoreDefaults();

                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::fastRGB);
                MyNetwork::sendResponse(request, "Set profile to fastRGB");
                });
        }

        void restoreDefaults() {
            numTrails = 10;
            trailLength = 28;
            spawnDelay = 250;
            trailSpeed = 2;
        }

        void setProfile() {
            Chromance::backgroundColour = CRGB::Black;
            Chromance::displayMode = Chromance::average;
            Chromance::profile = Profiles::fastRGB;
            Utils::logCurrentTime();
        }

        void doUpdate() {
            spawnTrails();
        }
    }
}