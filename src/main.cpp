#include <Arduino.h>

#include "main.h"

std::string firstProfile = Profiles::pulse;
std::string lastProfile;
bool connected = false;
auto profileStartTime = std::chrono::high_resolution_clock::now();

// ToDo:
// Convert std::string to String
// Convert printf to Serial.print

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(921600);
  doUSBWarning();
  initialiseChromance();
  Chromance::off();
  Chromance::writeUpdates();

  connected = MyNetwork::connectToNetwork();
  if (connected) {
    MyNetwork::startServer();
  }
}

void loop() {
  Chromance::doUpdate();
  if (ProfileManager::shuffleMode && firstProfile != Profiles::shapeTest) {
    shuffleProfile();
  }
}

void doUSBWarning() {
  Serial.println("Unplug USB now");
  DebugTools::blinkNumTimes(2);
  delay(1000);
  Serial.println("Printing Working\n");
}

void initialiseChromance() {
  if (debugGeneral) Serial.println("Initialising");
  FastLED.addLeds<WS2812B, ledPin1, GRB>(leds1, numLEDs1);
  FastLED.addLeds<WS2812B, ledPin2, GRB>(leds2, numLEDs2);
  FastLED.addLeds<WS2812B, ledPin3, GRB>(leds3, numLEDs3);
  FastLED.addLeds<WS2812B, ledPin4, GRB>(leds4, numLEDs4);
  FastLED.setBrightness(255);

  Hubs::initialiseHubs();
  Random::initialise();
  ProfileManager::initialise();
  ProfileManager::setProfile(firstProfile);
  if (debugGeneral) Serial.println("Initialised");
}

void shuffleProfile() {
  auto currentTime = std::chrono::high_resolution_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - profileStartTime).count();

  if (elapsed >= 60) {
    std::string nextProfile = ProfileManager::getRandomExcept(lastProfile);
    ProfileManager::setProfile(nextProfile);
    profileStartTime = std::chrono::high_resolution_clock::now();
    lastProfile = nextProfile;
  }
}