#include "profiles/aurora.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace Aurora {

        // Private Variables & Functions
        namespace {
            int lastSpawnLocation;
            int colourIndex;

            void spawnTrail() {
                if (Chromance::getNumDoubleTrails() >= 2 * numTrailsPerColour) return;
                if (Utils::getMillisecondsSinceLog() < spawnDelay) return;

                int spawnLocation = Hubs::getRandom().getRandomLEDExcept(lastSpawnLocation);
                CRGB colour = colours[colourIndex];

                Chromance::createDoubleTrail(colour, spawnLocation, trailLength, trailSpeed, 140, false, false);
                Utils::logCurrentTime();

                lastSpawnLocation = spawnLocation;
                ++colourIndex;
                if (colourIndex == colours.size()) {
                    colourIndex = 0;
                }
            }
        }

        // Public Settings
        int numTrailsPerColour = 5;
        int trailLength = 80;
        int spawnDelay = 500;
        int trailSpeed = 1;

        // Public Functions

        void setupCommand(AsyncWebServer& server) {
            server.on("/aurora", HTTP_GET, [](AsyncWebServerRequest* request) {
                if (request->hasParam("numTrailsPerColour")) numTrailsPerColour = request->arg("numTrailsPerColour").toInt();
                if (request->hasParam("trailLength")) trailLength = request->arg("trailLength").toInt();
                if (request->hasParam("spawnDelay")) spawnDelay = request->arg("spawnDelay").toInt();
                if (request->hasParam("trailSpeed")) trailSpeed = request->arg("trailSpeed").toInt();
                if (request->hasParam("defaults") && request->arg("defaults") == "true") restoreDefaults();

                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::aurora);
                MyNetwork::sendResponse(request, "Set profile to Aurora");
                });
        }

        void restoreDefaults() {
            numTrailsPerColour = 5;
            trailLength = 80;
            spawnDelay = 500;
            trailSpeed = 1;
        }

        void setProfile() {
            Chromance::backgroundColour = CRGB::Blue;
            Chromance::displayMode = Chromance::average;
            Chromance::profile = Profiles::aurora;
            Utils::logCurrentTime();
            lastSpawnLocation = -1;
            colourIndex = 0;
        }

        void doUpdate() {
            spawnTrail();
        }
    }
}