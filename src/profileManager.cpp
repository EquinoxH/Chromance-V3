#include "profileManager.h"
#include "debugTools.h"
#include "chromance.h"
#include "myRandom.h"
#include "utils.h"

#include "profiles.h"

namespace ProfileManager {
    bool shuffleMode = true;
    std::map<std::string, std::function<void()>> setProfileFunctions;
    std::map<std::string, std::function<void()>> doUpdateFunctions;
    std::map<std::string, std::function<void(int)>> onDeathFunctions;

    namespace {
        void initialiseSetProfileFunctions() {
            setProfileFunctions[Profiles::aurora] = Profiles::Aurora::setProfile;
            setProfileFunctions[Profiles::blizzard] = Profiles::Blizzard::setProfile;
            setProfileFunctions[Profiles::blossom] = Profiles::Blossom::setProfile;
            setProfileFunctions[Profiles::clouds] = Profiles::Clouds::setProfile;
            setProfileFunctions[Profiles::embers] = Profiles::Embers::setProfile;
            setProfileFunctions[Profiles::fastRGB] = Profiles::FastRGB::setProfile;
            setProfileFunctions[Profiles::fireflies] = Profiles::Fireflies::setProfile;
            setProfileFunctions[Profiles::fireworks] = Profiles::Fireworks::setProfile;
            setProfileFunctions[Profiles::flower] = Profiles::Flower::setProfile;
            setProfileFunctions[Profiles::heart] = Profiles::Heart::setProfile;
            setProfileFunctions[Profiles::meteor] = Profiles::Meteor::setProfile;
            setProfileFunctions[Profiles::meteorStorm] = Profiles::MeteorStorm::setProfile;
            setProfileFunctions[Profiles::pulse] = Profiles::Pulse::setProfile;
            setProfileFunctions[Profiles::purpleRain] = Profiles::PurpleRain::setProfile;
            setProfileFunctions[Profiles::rainbow] = Profiles::Rainbow::setProfile;
            setProfileFunctions[Profiles::rainfall] = Profiles::Rainfall::setProfile;
            setProfileFunctions[Profiles::rgb] = Profiles::RGB::setProfile;
            setProfileFunctions[Profiles::snowfall] = Profiles::Snowfall::setProfile;
            setProfileFunctions[Profiles::warning] = Profiles::Warning::setProfile;

            setProfileFunctions[Profiles::shapeTest] = Profiles::ShapeTest::setProfile;
        }

        void initialiseDoUpdateFunctions() {
            doUpdateFunctions[Profiles::aurora] = Profiles::Aurora::doUpdate;
            doUpdateFunctions[Profiles::blizzard] = Profiles::Blizzard::doUpdate;
            doUpdateFunctions[Profiles::blossom] = Profiles::Blossom::doUpdate;
            doUpdateFunctions[Profiles::clouds] = Profiles::Clouds::doUpdate;
            doUpdateFunctions[Profiles::embers] = Profiles::Embers::doUpdate;
            doUpdateFunctions[Profiles::fastRGB] = Profiles::FastRGB::doUpdate;
            doUpdateFunctions[Profiles::fireflies] = Profiles::Fireflies::doUpdate;
            doUpdateFunctions[Profiles::fireworks] = Profiles::Fireworks::doUpdate;
            doUpdateFunctions[Profiles::flower] = Profiles::Flower::doUpdate;
            doUpdateFunctions[Profiles::heart] = Profiles::Heart::doUpdate;
            doUpdateFunctions[Profiles::meteor] = Profiles::Meteor::doUpdate;
            doUpdateFunctions[Profiles::meteorStorm] = Profiles::MeteorStorm::doUpdate;
            doUpdateFunctions[Profiles::pulse] = Profiles::Pulse::doUpdate;
            doUpdateFunctions[Profiles::purpleRain] = Profiles::PurpleRain::doUpdate;
            doUpdateFunctions[Profiles::rainbow] = Profiles::Rainbow::doUpdate;
            doUpdateFunctions[Profiles::rainfall] = Profiles::Rainfall::doUpdate;
            doUpdateFunctions[Profiles::rgb] = Profiles::RGB::doUpdate;
            doUpdateFunctions[Profiles::snowfall] = Profiles::Snowfall::doUpdate;
            doUpdateFunctions[Profiles::warning] = Profiles::Warning::doUpdate;

            doUpdateFunctions[Profiles::shapeTest] = Profiles::ShapeTest::doUpdate;
        }

        void initialiseOnDeathFunctions() {
            onDeathFunctions[Profiles::fireworks] = Profiles::Fireworks::onDeath;
        }
    }

    void initialise() {
        initialiseSetProfileFunctions();
        initialiseDoUpdateFunctions();
        initialiseOnDeathFunctions();
    }

    std::string getRandom() {
        return Profiles::profiles[Random::getRandomInt(Profiles::profiles.size())];
    }

    std::string getRandomExcept(std::string lastProfile) {
        std::string profile = getRandom();
        while (profile == lastProfile) {
            profile = getRandom();
        }

        return profile;
    }

    void setProfile(std::string profile) {
        if (debugProfileManager) printf("Setting profile: %s\n", profile);
        Chromance::clearSegments();

        if (setProfileFunctions.find(profile) != setProfileFunctions.end()) {
            setProfileFunctions[profile]();
        }
    }

    void doUpdate(std::string profile) {
        if (debugProfileUpdates) printf("Doing update for: %s\n", profile);
        doUpdateFunctions[profile]();
    }

    void onDeath(std::string profile, int deathLocation) {
        if (Utils::isKeyInMap(profile, onDeathFunctions)) {
            if (debugProfileManager) printf("Doing death for: %s\n", profile);
            onDeathFunctions[profile](deathLocation);
        }
    }
}