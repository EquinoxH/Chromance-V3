#include "profiles/meteor.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace Meteor {

        // Private Variables And Functions
        namespace {
            int spawnDelay;
            int lastSpawnLocationIndex;

            void spawnMeteor() {
                if (Utils::getMillisecondsSinceLog() <= spawnDelay) return;

                int locationIndex = Random::getRandomIntExcept(spawnLocations.size(), lastSpawnLocationIndex);

                int spawnLocation = spawnLocations[locationIndex];

                Chromance::createTrail(ColourUtils::getMeteorColour(), spawnLocation, 12, false, 3, 14, false);
                Utils::logCurrentTime();
                lastSpawnLocationIndex = locationIndex;
                spawnDelay = Random::getRandomInt(500, 1000);
            }
        }

        // Public Functions

        void setupCommand(AsyncWebServer& server) {
            server.on("/meteor", HTTP_GET, [](AsyncWebServerRequest* request) {
                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::meteor);
                MyNetwork::sendResponse(request, "Set profile to meteor");
                });
        }

        void setProfile() {
            Chromance::backgroundColour = CRGB::Black;
            Chromance::displayMode = Chromance::absolute;
            Chromance::profile = Profiles::meteor;
            Utils::logCurrentTime();
            spawnDelay = 0;
        }

        void doUpdate() {
            spawnMeteor();
        }
    }
}