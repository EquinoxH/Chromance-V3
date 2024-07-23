#include "profiles/fireworks.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace Fireworks {

        // Private Variables And Functions
        namespace {
            int lastSpawnLocationIndex;
            CRGB nextColour;

            void spawnFirework() {
                if (Utils::getMillisecondsSinceLog() < spawnDelay) return;

                nextColour = ColourUtils::getRandomColour();
                int spawnIndex = Random::getRandomIntExcept(spawnLocations.size(), lastSpawnLocationIndex);
                int spawnLocation = spawnLocations[spawnIndex];

                Chromance::createTrail(CRGB::Red, spawnLocation, 12, false, 1, 14, true);
                lastSpawnLocationIndex = spawnIndex;
                Utils::logCurrentTime();
            }

            void spawnPulse(int deathLocation) {
                Hub hub = Hubs::getConnectedHub(deathLocation);
                std::vector<int> leds = hub.getLEDs();
                for (int i = 0; i < leds.size(); i++) {
                    Chromance::createTrail(nextColour, leds[i], 13, false, 1, 14, false);
                }
            }
        }

        // Public Settings

        int spawnDelay = 400;

        // Public Functions

        void setupCommand(AsyncWebServer& server) {
            server.on("/fireworks", HTTP_GET, [](AsyncWebServerRequest* request) {
                if (request->hasParam("spawnDelay")) spawnDelay = request->arg("spawnDelay").toInt();
                if (request->hasParam("defaults") && request->arg("defaults") == "true") restoreDefaults();

                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::fireworks);
                MyNetwork::sendResponse(request, "Set response to fireworks");
                });
        }

        void restoreDefaults() {
            spawnDelay = 400;
        }

        void setProfile() {
            Chromance::backgroundColour = CRGB::Black;
            Chromance::displayMode = Chromance::absolute;
            Chromance::profile = Profiles::fireworks;
            Utils::logCurrentTime();
            lastSpawnLocationIndex = -1;
        }

        void doUpdate() {
            spawnFirework();
        }

        void onDeath(int deathLocation) {
            spawnPulse(deathLocation);
        }
    }
}
