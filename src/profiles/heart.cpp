#include "profiles/heart.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace Heart {

        void setupCommand(AsyncWebServer& server) {
            server.on("/heart", HTTP_GET, [](AsyncWebServerRequest* request) {
                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::heart);
                MyNetwork::sendResponse(request, "Set profile to heart");
                });
        }

        void setProfile() {
            Chromance::backgroundColour = CRGB::Black;
            Chromance::displayMode = Chromance::absolute;
            Chromance::profile = Profiles::heart;
        }

        void doUpdate() {
            if (Chromance::getNumSegments() == 0) {
                for (int segment : segments) {
                    Chromance::createSegment(segment, colours, 0);
                }
            }
        }
    }
}