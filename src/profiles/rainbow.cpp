#include "profiles/rainbow.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace Rainbow {

        void setupCommand(AsyncWebServer& server) {
            server.on("/rainbow", HTTP_GET, [](AsyncWebServerRequest* request) {
                ProfileManager::shuffleMode = false;
                ProfileManager::setProfile(Profiles::rainbow);
                MyNetwork::sendResponse(request, "Set profile to rainbow");
                });
        }

        void setProfile() {
            Chromance::backgroundColour = CRGB::Black;
            Chromance::displayMode = Chromance::absolute;
            Chromance::profile = Profiles::rainbow;
        }

        void doUpdate() {
            if (Chromance::getNumSegments() == 0) {
                for (int segment : outerSegments) {
                    Chromance::createSegment(segment, colours, 0);
                }
                for (int segment : innerSegments) {
                    Chromance::createSegment(segment, colours, 1);
                }
            }
        }
    }
}