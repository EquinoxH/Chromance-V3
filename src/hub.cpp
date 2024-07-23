#include "hub.h"
#include "myRandom.h"

#include <algorithm>

// Constructor
Hub::Hub(int _id, int _numSlots, std::vector<int> _ledIDs, std::vector<int> _segmentIDs) {
    id = _id;
    numSlots = _numSlots;
    ledIDs = _ledIDs;
    segmentIDs = _segmentIDs;
}

// Public Functions

int Hub::getID() {
    return id;
}

std::vector<int>& Hub::getLEDs() {
    return ledIDs;
}

int Hub::getRandomLED() {
    return ledIDs[Random::getRandomInt(ledIDs.size())];
}

int Hub::getRandomLEDExcept(int led) {
    int random = led;
    while (random == led) {
        random = ledIDs[Random::getRandomInt(ledIDs.size())];
    }

    return random;
}

namespace Hubs {
    std::vector<Hub> hubs;
    std::vector<int> slotMap;
    std::vector<std::vector<int>> ledMap;
    std::vector<std::vector<int>> segmentMap;

    void initialiseSlotMap() {
        slotMap = std::vector<int>{
            2,2,2,
            3,5,5,3,
            3,3,3,
            2,3,3,2,
            5,6,5,
            3,3,
            2,3,2,
            4,4,
            2
        };
    }

    void initialiseLEDMap() {
        ledMap.push_back(std::vector<int>{349, 350});
        ledMap.push_back(std::vector<int>{125, 126});
        ledMap.push_back(std::vector<int>{41, 42});

        ledMap.push_back(std::vector<int>{363, 364, 405});
        ledMap.push_back(std::vector<int>{139, 140, 321, 335, 336});
        ledMap.push_back(std::vector<int>{55, 56, 111, 112, 154});
        ledMap.push_back(std::vector<int>{27, 28, 559});

        ledMap.push_back(std::vector<int>{307, 308, 392});
        ledMap.push_back(std::vector<int>{97, 98, 153});
        ledMap.push_back(std::vector<int>{167, 545, 546});

        ledMap.push_back(std::vector<int>{377, 378});
        ledMap.push_back(std::vector<int>{223, 224, 322});
        ledMap.push_back(std::vector<int>{69, 461, 462});
        ledMap.push_back(std::vector<int>{13, 14});

        ledMap.push_back(std::vector<int>{209, 210, 293, 294, 391});
        ledMap.push_back(std::vector<int>{83, 84, 237, 238, 475, 476});
        ledMap.push_back(std::vector<int>{0, 447, 448, 531, 532});

        ledMap.push_back(std::vector<int>{279, 280, 489});
        ledMap.push_back(std::vector<int>{70, 517, 518});

        ledMap.push_back(std::vector<int>{195, 196});
        ledMap.push_back(std::vector<int>{251, 252, 490});
        ledMap.push_back(std::vector<int>{433, 434});

        ledMap.push_back(std::vector<int>{181, 182, 265, 266});
        ledMap.push_back(std::vector<int>{419, 420, 503, 504});

        ledMap.push_back(std::vector<int>{168, 406});
    }

    void initialiseSegmentMap() {
        segmentMap.push_back(std::vector<int>{24, 25});
        segmentMap.push_back(std::vector<int>{8, 9});
        segmentMap.push_back(std::vector<int>{2, 3});

        segmentMap.push_back(std::vector<int>{25, 26, 28});
        segmentMap.push_back(std::vector<int>{9, 10, 22, 23, 24});
        segmentMap.push_back(std::vector<int>{3, 4, 7, 8, 11});
        segmentMap.push_back(std::vector<int>{1, 2, 39});

        segmentMap.push_back(std::vector<int>{21, 22, 28});
        segmentMap.push_back(std::vector<int>{6, 7, 10});
        segmentMap.push_back(std::vector<int>{11, 38, 39});

        segmentMap.push_back(std::vector<int>{26, 27});
        segmentMap.push_back(std::vector<int>{15, 16, 23});
        segmentMap.push_back(std::vector<int>{4, 32, 33});
        segmentMap.push_back(std::vector<int>{0, 1});

        segmentMap.push_back(std::vector<int>{14, 15, 20, 21, 27});
        segmentMap.push_back(std::vector<int>{5, 6, 16, 17, 33, 34});
        segmentMap.push_back(std::vector<int>{0, 31, 32, 37, 38});

        segmentMap.push_back(std::vector<int>{19, 20, 34});
        segmentMap.push_back(std::vector<int>{5, 36, 37});

        segmentMap.push_back(std::vector<int>{13, 14});
        segmentMap.push_back(std::vector<int>{17, 18, 35});
        segmentMap.push_back(std::vector<int>{30, 31});

        segmentMap.push_back(std::vector<int>{12, 23, 18, 19});
        segmentMap.push_back(std::vector<int>{29, 30, 35, 36});

        segmentMap.push_back(std::vector<int>{12, 29});
    }

    void initialiseHubs() {
        initialiseSlotMap();
        initialiseLEDMap();
        initialiseSegmentMap();

        for (int i = 0; i < 25; i++) {
            Hub hub(i, slotMap[i], ledMap[i], segmentMap[i]);
            hubs.push_back(hub);
        }
    }

    Hub getHub(int id) {
        return hubs[id];
    }

    Hub getRandom() {
        return hubs[Random::getRandomInt(hubs.size())];
    }

    Hub getRandomExcept(int id) {
        return hubs[Random::getRandomIntExcept(hubs.size(), id)];
    }

    Hub getConnectedHub(int led) {
        for (Hub hub : hubs) {
            if (std::count(hub.getLEDs().begin(), hub.getLEDs().end(), led)) {
                return hub;
            }
        }

        return hubs[0];
    }

    bool ledIsStartOrEnd(int led) {
        return (led % 14 == 0 || (led + 1) % 14 == 0);
    }
}