#include "profiles/purpleRain.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace PurpleRain {

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
            server.on("/purpleRain", HTTP_GET, [](AsyncWebServerRequest* request) {
                if (request->hasParam("numRaindrops")) Profiles::PurpleRain::numRaindrops = request->arg("numRaindrops").toInt();
                if (request->hasParam("spawnDelay")) Profiles::PurpleRain::spawnDelay = request->arg("spawnDelay").toInt();
                if (request->hasParam("trailSpeed")) Profiles::PurpleRain::trailSpeed = request->arg("trailSpeed").toInt();
                if (request->hasParam("defaults") && request->arg("defaults") == "true") restoreDefaults();

                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::purpleRain);
                MyNetwork::sendResponse(request, "Set profile to purpleRain");
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
            Chromance::profile = Profiles::purpleRain;
            Utils::logCurrentTime();
            lastSpawnLocationIndex = -1;
            lastColourIndex = -1;
        }

        void doUpdate() {
            spawnRaindrop();
        }
    }
}