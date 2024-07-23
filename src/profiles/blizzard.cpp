#include "profiles/blizzard.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace Blizzard {

        // Private Variables & Functions
        namespace {
            int lastSpawnIndex = -1;

            void spawnFlake() {
                if (Chromance::getNumTrails() >= numFlakes) return;
                if (Utils::getMillisecondsSinceLog() < spawnDelay) return;

                int spawnIndex = Random::getRandomIntExcept(spawnLocations.size(), lastSpawnIndex);
                int spawnLocation = spawnLocations[spawnIndex];

                Chromance::createTrail(CRGB::White, spawnLocation, 12, false, speed, trailLength, false);
                Utils::logCurrentTime();
                spawnDelay = Random::getRandomInt(50, 100);
            }
        }

        // Public Settings
        int numFlakes = 40;
        int speed = 3;
        int trailLength = 4;
        int spawnDelay = 10;

        // Public Functions

        void setupCommand(AsyncWebServer& server) {
            server.on("/blizzard", HTTP_GET, [](AsyncWebServerRequest* request) {
                if (request->hasParam("numFlakes")) numFlakes = request->arg("numFlakes").toInt();
                if (request->hasParam("speed")) speed = request->arg("speed").toInt();
                if (request->hasParam("trailLength")) trailLength = request->arg("trailLength").toInt();
                if (request->hasParam("spawnDelay")) spawnDelay = request->arg("spawnDelay").toInt();
                if (request->hasParam("defaults") && request->arg("defaults") == "true") restoreDefaults();

                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::blizzard);
                MyNetwork::sendResponse(request, "Set profile to blizzard");
                });
        }

        void restoreDefaults() {
            numFlakes = 40;
            speed = 3;
            trailLength = 4;
            spawnDelay = 10;
        }

        void setProfile() {
            Chromance::backgroundColour = CRGB::Black;
            Chromance::displayMode = Chromance::absolute;
            Chromance::profile = Profiles::blizzard;
            Utils::logCurrentTime();
        }

        void doUpdate() {
            spawnFlake();
        }
    }
}