#pragma once
#include "bot.hpp"
#include "WiFiClientSecure.h"
#include <ArduinoJson.h>

class RandomFactPublisher
{
    private:
        // api = "https://useless-facts.sameerkumar.website/api";
        const char* host = "useless-facts.sameerkumar.website";
        const int port = 443;
        int diff = 1;
        Bot bot;
        bool running = false;
        const char* fingerprint = "09 6C 0D 80 FF FD 5C 77 A9 52 29 2D 77 B4 5B 10 39 2F 58 56";

    public:
        RandomFactPublisher(Bot &bot);

        void begin();

        void post();
};