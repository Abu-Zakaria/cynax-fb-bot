#pragma once
#include <WString.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFi.h>
#include "wifi_info.hpp"
#include "access_token.hpp"
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include "url_encode.hpp"

class Bot
{
    private:
        String page_id;
        const char* api_host = "graph.facebook.com";
        const char* bot_host = "fb-bot.cynax120.com";
        int api_port = 443;
        const char* fingerprint = "64 6A 5B 69 8B 12 93 B5 D8 B2 20 D5 3F 4E 74 04 CA BA 95 5E";
        const char* bot_api_fingerprint = "60 01 09 58 34 0C 5A 93 C6 77 78 73 A4 EC 30 41 AB 4B 14 EA";
        IPAddress ip_address;

    public:
        void init();

        void connectWifi();

        DynamicJsonDocument getMe();

        void publishPost(String post_content);

        String post(String uri, String content);

        String get(const char* uri);

        String sendHTTPRequest(String header, WiFiClientSecure client);

        const char* getBotFingerprint();
};