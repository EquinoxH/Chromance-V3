#include "profiles/rainfall.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace Rainfall {

        // Private Variables & Functions
        namespace {
            int lastSpawnLocationIndex;
            int lastColourIndex;

            void spawnRaindrop() {
                if (Chromance::getNumTrails() >= numRaindrops) return;
                if (Utils::getMillisecondsSinceLog() < spawnDelay) return;

                int spawnLocationIndex = Random::getRandomIntExcept(spawnLocations.size(), lastSpawnLocationIndex);
                int spawnLocation = spawnLocations[spawnLocationIndex];

                int colourIndex = Random::getRandomIntExcept(colours.size(), lastColourIndex);
                CRGB colour = colours[colourIndex];

                Chromance::createTrail(colour, spawnLocation, 12, false, 1, 14, false);
                Utils::logCurrentTime();

                lastSpawnLocationIndex = spawnLocationIndex;
                lastColourIndex = colourIndex;
            }
        }

        // Public Settings
        int numRaindrops = 10;
        int spawnDelay = 50;
        int trailSpeed = 1;

        // Public Functions
        void setupCommand(AsyncWebServer& server) {
            server.on("/rainfall", HTTP_GET, [](AsyncWebServerRequest* request) {
                if (request->hasParam("numRaindrops")) numRaindrops = request->arg("numRaindrops").toInt();
                if (request->hasParam("spawnDelay")) spawnDelay = request->arg("spawnDelay").toInt();
                if (request->hasParam("trailSpeed")) trailSpeed = request->arg("trailSpeed").toInt();
                if (request->hasParam("defaults") && request->arg("defaults") == "true") restoreDefaults();

                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::rainfall);
                MyNetwork::sendResponse(request, "Set profile to rainfall");
                });
        }

        void restoreDefaults() {
            numRaindrops = 10;
            spawnDelay = 50;
            trailSpeed = 1;
        }

        void setProfile() {
            Chromance::backgroundColour = CRGB::Black;
            Chromance::displayMode = Chromance::absolute;
            Chromance::profile = Profiles::rainfall;
            Utils::logCurrentTime();
            lastSpawnLocationIndex = -1;
            lastColourIndex = -1;
        }

        void doUpdate() {
            spawnRaindrop();
        }
    }
}