#include "profiles/pulse.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace Pulse {

        // Private Variables & Functions
        namespace {

            int lastHub;
            int lastLife;

            void spawnPulse(CRGB colour, int hubID) {
                std::vector<int> leds = Hubs::getHub(hubID).getLEDs();
                for (int i = 0; i < leds.size(); i++) {
                    int lifetime = Random::getRandomIntExcept(14, 43, lastLife);
                    int led = leds[i];

                    Chromance::createTrail(colour, led, lifetime, false, 1, trailLength, false);
                    lastHub = hubID;
                    lastLife = lifetime;
                }
            }

            void spawnRandomPulse() {
                if (Chromance::getNumTrails() > 1) return;

                CRGB colour = ColourUtils::getRandomColour();
                Hub hub = Hubs::getRandomExcept(lastHub);

                if (bigMode) {
                    while (hub.getLEDs().size() < 4) {
                        hub = Hubs::getRandomExcept(lastHub);
                    }
                }

                spawnPulse(colour, hub.getID());
            }

            void spawnFirstPulse() {
                spawnPulse(CRGB::Blue, 15);
            }
        }

        // Public Settings
        bool bigMode = true;
        int trailSpeed = 1;
        int trailLength = 14;

        // Public Functions

        void setupCommand(AsyncWebServer& server) {
            server.on("/pulse", HTTP_GET, [](AsyncWebServerRequest* request) {
                if (request->hasParam("bigMode")) bigMode = request->arg("bigMode") == "true";
                if (request->hasParam("trailSpeed")) trailSpeed = request->arg("trailSpeed").toInt();
                if (request->hasParam("trailLength")) trailLength = request->arg("trailLength").toInt();
                if (request->hasParam("defaults") && request->arg("defaults") == "true") restoreDefaults();

                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::pulse);
                MyNetwork::sendResponse(request, "Set profile to pulse");
                });
        }

        void restoreDefaults() {
            bigMode = true;
            trailSpeed = 1;
            trailLength = 14;
        }

        void setProfile() {
            Chromance::backgroundColour = CRGB::Black;
            Chromance::displayMode = Chromance::absolute;
            Chromance::profile = Profiles::pulse;
            Chromance::speed = 10;
            lastLife = 0;
            lastHub = 0;
            spawnFirstPulse();
        }

        void doUpdate() {
            spawnRandomPulse();
        }
    }
}