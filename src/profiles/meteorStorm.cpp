#include "profiles/meteorStorm.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace MeteorStorm {

        // Private Variables And Functions
        namespace {
            int lastSpawnLocationIndex;

            void spawnMeteor() {
                int locationIndex = Random::getRandomIntExcept(spawnLocations.size(), lastSpawnLocationIndex);
                int spawnLocation = spawnLocations[locationIndex];

                Chromance::createTrail(ColourUtils::getMeteorColour(), spawnLocation, 12, false, 3, 14, false);
                lastSpawnLocationIndex = locationIndex;
            }
        }

        // Public Functions

        void setupCommand(AsyncWebServer& server) {
            server.on("/meteorStorm", HTTP_GET, [](AsyncWebServerRequest* request) {
                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::meteorStorm);
                MyNetwork::sendResponse(request, "Set profile to meteorStorm");
                });
        }

        void setProfile() {
            Chromance::backgroundColour = CRGB::Black;
            Chromance::displayMode = Chromance::absolute;
            Chromance::profile = Profiles::meteorStorm;
        }

        void doUpdate() {
            spawnMeteor();
        }
    }
}