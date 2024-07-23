#include "profiles/shapeTest.h"
#include "profileIncludes.h"

namespace Profiles {
    namespace ShapeTest {
        void doUpdate() {}
        void setProfile() {
            Chromance::backgroundColour = CRGB::Black;
            Chromance::profile = Profiles::shapeTest;
        }
    }
}