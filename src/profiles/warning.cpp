#include "profiles/warning.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace Warning {

        // Private Variables & Functions
        namespace {
            int lastSpawnLocation;

            void spawnTrails() {
                if (Chromance::getNumTrails() >= numTrails) return;
                if (Utils::getMillisecondsSinceLog() < spawnDelay) return;

                int spawnLocation = Hubs::getRandom().getRandomLEDExcept(lastSpawnLocation);
                Chromance::createTrail(colour, spawnLocation, lifetime, false, trailSpeed, trailLength, false);
                Utils::logCurrentTime();
                lastSpawnLocation = spawnLocation;
            }
        }

        // Public Settings
        int numTrails = 5;
        int trailLength = 42;
        int spawnDelay = 50;
        int trailSpeed = 1;
        int lifetime = 140;
        CRGB colour = CRGB::Blue;

        // Public Functions

        void setupCommand(AsyncWebServer& server) {
            server.on("/warning", HTTP_GET, [](AsyncWebServerRequest* request) {
                if (request->hasParam("numTrails")) numTrails = request->arg("numTrails").toInt();
                if (request->hasParam("trailLength")) trailLength = request->arg("trailLength").toInt();
                if (request->hasParam("spawnDelay")) spawnDelay = request->arg("spawnDelay").toInt();
                if (request->hasParam("trailSpeed")) trailSpeed = request->arg("trailSpeed").toInt();
                if (request->hasParam("lifetime")) lifetime = request->arg("lifetime").toInt();
                if (request->hasParam("colour")) colour = ColourUtils::colourFromString(request->arg("colour"));
                if (request->hasParam("defaults") && request->arg("defaults") == "true") restoreDefaults();

                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::warning);
                MyNetwork::sendResponse(request, "Set profile to warning");
                });
        }

        void restoreDefaults() {
            numTrails = 5;
            trailLength = 42;
            spawnDelay = 50;
            trailSpeed = 1;
            lifetime = 140;
            colour = CRGB::Blue;
        }

        void setProfile() {
            Chromance::backgroundColour = CRGB::Black;
            Chromance::displayMode = Chromance::absolute;
            Chromance::profile = Profiles::warning;
            Utils::logCurrentTime();
            lastSpawnLocation = -1;
        }

        void doUpdate() {
            spawnTrails();
        }
    }
}