#pragma once

class AsyncWebServer;
class AsyncWebServerRequest;

namespace MyNetwork {

    extern AsyncWebServer server;

    bool connectToNetwork();
    void startServer();
    void sendResponse(AsyncWebServerRequest* reqest, const String& response);

    void setupOffCommand();
    void setupShuffleCommand();
    void setupAbsoluteCommand();
    void setupAverageCommand();
    void setupSumCommand();
}