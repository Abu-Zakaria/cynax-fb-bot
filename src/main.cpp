#include <Arduino.h>
#include <LittleFS.h>

#include "bot.hpp"
#include "random_fact_publisher.hpp"

void setup() {
    Serial.begin(9600);
    Serial.println("Setting up...");
    
    Bot bot;
    bot.init();

    RandomFactPublisher factPublisher(bot);

    factPublisher.begin();
}

void loop() {
    
}