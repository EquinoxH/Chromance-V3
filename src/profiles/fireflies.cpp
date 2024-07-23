#include "profiles/fireflies.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace Fireflies {

        // Private Variables & Functions
        namespace {
            int lastSpawnLocation;

            void spawnFirefly() {
                if (Chromance::getNumDots() >= numFireflies) return;
                if (Utils::getMillisecondsSinceLog() <= spawnDelay) return;

                int spawnLocation = Random::getRandomIntExcept(560, lastSpawnLocation);
                Chromance::createDot(CRGB::YellowGreen, spawnLocation, lifetime);
                lastSpawnLocation = spawnLocation;
                Utils::logCurrentTime();
            }
        }

        // Public Settings
        int numFireflies = 20;
        int lifetime = 40;
        int spawnDelay = 50;

        // Public Functions

        void setupCommand(AsyncWebServer& server) {
            server.on("/fireflies", HTTP_GET, [](AsyncWebServerRequest* request) {
                if (request->hasParam("numFireflies")) numFireflies = request->arg("numFireflies").toInt();
                if (request->hasParam("lifetime")) lifetime = request->arg("lifetime").toInt();
                if (request->hasParam("spawnDelay")) spawnDelay = request->arg("spawnDelay").toInt();
                if (request->hasParam("defaults") && request->arg("defaults") == "true") restoreDefaults();

                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::fireflies);
                MyNetwork::sendResponse(request, "Set profile to fireflies");
                });
        }

        void restoreDefaults() {
            numFireflies = 20;
            lifetime = 40;
            spawnDelay = 50;
        }

        void setProfile() {
            Chromance::backgroundColour = CRGB::Black;
            Chromance::displayMode = Chromance::absolute;
            Chromance::profile = Profiles::fireflies;
            Utils::logCurrentTime();
            lastSpawnLocation = -1;
        }

        void doUpdate() {
            spawnFirefly();
        }
    }
}