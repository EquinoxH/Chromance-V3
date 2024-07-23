#include "profiles/flower.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace Flower {

        void setupCommand(AsyncWebServer& server) {
            server.on("/flower", HTTP_GET, [](AsyncWebServerRequest* request) {
                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::flower);
                MyNetwork::sendResponse(request, "Set profile to flower");
                });
        }

        void setProfile() {
            Chromance::backgroundColour = CRGB::Black;
            Chromance::displayMode = Chromance::absolute;
            Chromance::profile = Profiles::flower;
        }

        void doUpdate() {
            if (Chromance::getNumSegments() == 0) {
                for (int segment : outerSegments) {
                    Chromance::createSegment(segment, outerColours, 0);
                }
                for (int segment : innerSegments) {
                    Chromance::createSegment(segment, innerColours, 0);
                }
            }
        }
    }
}