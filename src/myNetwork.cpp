#include "Arduino.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <string>
#include <ESPmDNS.h>

#include "myNetwork.h"
#include "wifiDetails.h"
#include "profileManager.h"
#include "chromance.h"
#include "colourUtils.h"

#include "profiles.h"

namespace MyNetwork {
    AsyncWebServer server(80);
}

bool MyNetwork::connectToNetwork() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WiFiDetails::ssid, WiFiDetails::password);
    Serial.println("\nConnecting to wifi...");

    int timeout = 10;
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
        --timeout;

        if (timeout <= 0) {
            return false;
        }
    }

    Serial.println("\nConnected to Wifi");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());

    if (!MDNS.begin("chromance")) {
        Serial.println("Error setting up mDNS");
    }
    else {
        Serial.println("mDNS responder started");
        MDNS.addService("http", "tcp", 80);
    }

    return true;
}

void MyNetwork::startServer() {
    setupOffCommand();
    setupShuffleCommand();
    setupAbsoluteCommand();
    setupAverageCommand();
    setupSumCommand();

    Profiles::Aurora::setupCommand(server);
    Profiles::Blizzard::setupCommand(server);
    Profiles::Blossom::setupCommand(server);
    Profiles::Clouds::setupCommand(server);
    Profiles::Embers::setupCommand(server);
    Profiles::FastRGB::setupCommand(server);
    Profiles::Fireflies::setupCommand(server);
    Profiles::Fireworks::setupCommand(server);
    Profiles::Flower::setupCommand(server);
    Profiles::Heart::setupCommand(server);
    Profiles::Meteor::setupCommand(server);
    Profiles::MeteorStorm::setupCommand(server);
    Profiles::Pulse::setupCommand(server);
    Profiles::PurpleRain::setupCommand(server);
    Profiles::Rainbow::setupCommand(server);
    Profiles::Rainfall::setupCommand(server);
    Profiles::RGB::setupCommand(server);
    Profiles::Snowfall::setupCommand(server);
    Profiles::Warning::setupCommand(server);

    server.begin();
    Serial.println("Server started");
}

void MyNetwork::sendResponse(AsyncWebServerRequest* request, const String& response) {
    request->send(200, "text/plain", response);
}

void MyNetwork::setupOffCommand() {
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest* request) {
        Chromance::off();
        ProfileManager::shuffleMode = false;
        sendResponse(request, "Chromance switched off");
        });
}

void MyNetwork::setupShuffleCommand() {
    server.on("/shuffle", HTTP_GET, [](AsyncWebServerRequest* request) {
        ProfileManager::shuffleMode = true;
        sendResponse(request, "Shuffle mode enabled");
        });
}

void MyNetwork::setupAbsoluteCommand() {
    server.on("/absolute", HTTP_GET, [](AsyncWebServerRequest* request) {
        Chromance::displayMode = Chromance::absolute;
        sendResponse(request, "Set displayMode to absolute");
        });
}

void MyNetwork::setupAverageCommand() {
    server.on("/average", HTTP_GET, [](AsyncWebServerRequest* request) {
        Chromance::displayMode = Chromance::average;
        sendResponse(request, "Set displayMode to average");
        });
}

void MyNetwork::setupSumCommand() {
    server.on("/sum", HTTP_GET, [](AsyncWebServerRequest* request) {
        Chromance::displayMode = Chromance::sum;
        sendResponse(request, "Set displayMode to average");
        });
}