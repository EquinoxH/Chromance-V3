#include "profiles/blossom.h"
#include "profileIncludes.h"

#include <math.h>

namespace Profiles {
    namespace Blossom {

        // Private Variables & Functions
        namespace {
            int spawnDelay = 50;
            int lastSpawnIndex = -1;
            std::chrono::_V2::system_clock::time_point startTime;

            double getTimeSinceStart() {
                auto currentTime = std::chrono::high_resolution_clock::now();
                return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
            }

            bool shouldSpawnPetal() {
                if (Chromance::getNumSlowTrails() >= numPetals) return false;
                return Utils::getMillisecondsSinceLog() >= spawnDelay;
            }

            void spawnPetal() {
                int spawnLocation = spawnLocations[Random::getRandomIntExcept(spawnLocations.size(), lastSpawnIndex)];
                int red = 255;
                double ratio = ((std::sin(getTimeSinceStart() / 1000) + 1) / 2);
                int greenBlue = (int)(ratio * 64);
                CRGB colour(red, greenBlue, greenBlue);

                Chromance::createSlowTrail(colour, spawnLocation, 12, false, speed, false);
                Utils::logCurrentTime();
                spawnDelay = Random::getRandomInt(50, 100);
            }
        }

        // Public Settings

        int numPetals = 20;
        int speed = 10;

        // Public Functions

        void setupCommand(AsyncWebServer& server) {
            server.on("/blossom", HTTP_GET, [](AsyncWebServerRequest* request) {
                if (request->hasParam("numPetals")) numPetals = request->arg("numPetals").toInt();
                if (request->hasParam("speed")) speed = request->arg("speed").toInt();
                if (request->hasParam("defaults") && request->arg("defaults") == "true") restoreDefaults();

                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::blossom);
                MyNetwork::sendResponse(request, "Set profile to blossom");
                });
        }

        void restoreDefaults() {
            numPetals = 20;
            speed = 10;
        }

        void setProfile() {
            Chromance::backgroundColour = CRGB::Black;
            Chromance::displayMode = Chromance::absolute;
            Chromance::profile = Profiles::blossom;
            Utils::logCurrentTime();
            startTime = std::chrono::high_resolution_clock::now();
        }

        void doUpdate() {
            if (shouldSpawnPetal()) {
                spawnPetal();
            }
        }
    }
}