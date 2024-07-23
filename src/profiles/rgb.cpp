#include "profiles/rgb.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace RGB {
        // Private Variables And Functions
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
        int numTrails = 20;
        int trailLength = 14;
        int spawnDelay = 50;
        int trailSpeed = 1;

        // Public Functions 

        void setupCommand(AsyncWebServer& server) {
            server.on("/rgb", HTTP_GET, [](AsyncWebServerRequest* request) {
                if (request->hasParam("numTrails")) numTrails = request->arg("numTrails").toInt();
                if (request->hasParam("trailLength")) trailLength = request->arg("trailLength").toInt();
                if (request->hasParam("spawnDelay")) spawnDelay = request->arg("spawnDelay").toInt();
                if (request->hasParam("trailSpeed")) trailSpeed = request->arg("trailSpeed").toInt();
                if (request->hasParam("defaults") && request->arg("defaults") == "true") restoreDefaults();

                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::rgb);
                MyNetwork::sendResponse(request, "Set profile to RGB");
                });
        }

        void restoreDefaults() {
            numTrails = 20;
            trailLength = 14;
            spawnDelay = 50;
            trailSpeed = 1;
        }

        void setProfile() {
            Chromance::backgroundColour = CRGB::Black;
            Chromance::displayMode = Chromance::average;
            Chromance::profile = Profiles::rgb;
            Utils::logCurrentTime();
            lastSpawnLocation = -1;
        }

        void doUpdate() {
            spawnTrails();
        }
    }
}