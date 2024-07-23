#include "profiles/snowfall.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace Snowfall {

        // Private Variales & Functions
        namespace {
            int lastSpawnLocationIndex;

            void spawnFlake() {
                if (Chromance::getNumSlowTrails() >= numFlakes) return;
                if (Utils::getMillisecondsSinceLog() < spawnDelay) return;

                int spawnLocationIndex = Random::getRandomIntExcept(spawnLocations.size(), lastSpawnLocationIndex);
                int spawnLocation = spawnLocations[spawnLocationIndex];

                Chromance::createSlowTrail(CRGB::White, spawnLocation, 12, false, 10, false);
                Utils::logCurrentTime();
                lastSpawnLocationIndex = spawnLocationIndex;
            }
        }

        // Public Settings
        int numFlakes = 20;
        int speed = 5;
        int spawnDelay = 250;

        // Public Functions

        void setupCommand(AsyncWebServer& server) {
            server.on("/snowfall", HTTP_GET, [](AsyncWebServerRequest* request) {
                if (request->hasParam("numFlakes")) numFlakes = request->arg("numFlakes").toInt();
                if (request->hasParam("speed")) speed = request->arg("speed").toInt();
                if (request->hasParam("spawnDelay")) spawnDelay = request->arg("spawnDelay").toInt();
                if (request->hasParam("defaults") && request->arg("defaults") == "true") restoreDefaults();

                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::snowfall);
                MyNetwork::sendResponse(request, "Set profile to snowfall");
                });
        }

        void restoreDefaults() {
            numFlakes = 20;
            speed = 5;
            spawnDelay = 250;
        }

        void setProfile() {
            Chromance::off();
            Chromance::backgroundColour = CRGB::Black;
            Chromance::displayMode = Chromance::absolute;
            Chromance::profile = Profiles::snowfall;
            Utils::logCurrentTime();
            lastSpawnLocationIndex = -1;
        }

        void doUpdate() {
            spawnFlake();
        }
    }
}