#include <exception>
#include <chrono>
#include <FastLED.h>

#include "profileManager.h"
#include "chromance.h"
#include "hub.h"
#include "myRandom.h"
#include "debugTools.h"
#include "myNetwork.h"
#include "neopixel.h"

void doUSBWarning();
void initialiseChromance();
void shuffleProfile();