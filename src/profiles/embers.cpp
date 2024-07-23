#include "profiles/embers.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace Embers {
        namespace {
            int lastSpawnLocationIndex;

            void spawnEmber() {
                if (Chromance::getNumSlowTrails() >= numEmbers) return;
                if (Utils::getMillisecondsSinceLog() < spawnDelay) return;

                int spawnLocationIndex = Random::getRandomIntExcept(spawnLocations.size(), lastSpawnLocationIndex);
                int spawnLocation = spawnLocations[spawnLocationIndex];

                Chromance::createSlowTrail(CRGB::OrangeRed, spawnLocation, 12, false, speed, false);
                Utils::logCurrentTime();
                lastSpawnLocationIndex = spawnLocationIndex;
            }
        }

        // Public Settings
        int numEmbers = 20;
        int speed = 5;
        int spawnDelay = 250;

        void setupCommand(AsyncWebServer& server) {
            server.on("/embers", HTTP_GET, [](AsyncWebServerRequest* request) {
                if (request->hasParam("numEmbers")) numEmbers = request->arg("numEmbers").toInt();
                if (request->hasParam("speed")) speed = request->arg("speed").toInt();
                if (request->hasParam("spawnDelay")) spawnDelay = request->arg("spawnDelay").toInt();
                if (request->hasParam("defaults") && request->arg("defaults") == "true") restoreDefaults();

                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::embers);
                MyNetwork::sendResponse(request, "Set profile to embers");
                });
        }

        void restoreDefaults() {
            numEmbers = 20;
            speed = 5;
            spawnDelay = 250;
        }

        void setProfile() {
            Chromance::off();
            Chromance::backgroundColour = CRGB::Black;
            Chromance::displayMode = Chromance::absolute;
            Chromance::profile = Profiles::embers;
            Utils::logCurrentTime();
            lastSpawnLocationIndex = -1;
        }

        void doUpdate() {
            spawnEmber();
        }
    }
}