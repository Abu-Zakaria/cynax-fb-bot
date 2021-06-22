#include <Arduino.h>
#include <LittleFS.h>

#include "bot.hpp"

void setup() {
    Serial.begin(9600);
    Serial.println("Setting up...");
    
    Bot bot;

    bot.init();
}

void loop() {
    
}