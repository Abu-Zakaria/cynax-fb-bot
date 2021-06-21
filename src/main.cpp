#include <Arduino.h>
#include <LittleFS.h>

#include "bot.hpp"

void setup() {
    Serial.begin(9600);
    Serial.println("Setting up...");

    pinMode(D1, OUTPUT);

    digitalWrite(D1, HIGH);
    if(!LittleFS.begin())
    {
        digitalWrite(D1, LOW);
        Serial.println("LittleFS couldn't be loaded");
        return;
    }
    

    File file = LittleFS.open("/test.txt", "r");

    if(!file)
    {
        digitalWrite(D1, LOW);
        Serial.println("file doesnt exists");
    }
    else
    {
        analogWrite(D1, 20);
    }

    file = LittleFS.open("/test.txt", "w");

    file.println("Hello there");
    file.println("Welcome to LittleFs");

    file.close();

    file = LittleFS.open("/test.txt", "r");

    if(file)
    {
        Serial.println("file exists now");

        while(file.available())
        {
            String line = file.readStringUntil('\n');
            Serial.println(line);
        }
    }

    file.close();

    Bot bot;

    bot.init();
}

char input_char = 0;
String serial_input = "";

void loop() {
    // if(Serial.available() > 0)
    // {
    //     input_char = Serial.read();

    //     if(input_char != '\n')
    //     {
    //         serial_input += input_char;
    //     }
    //     else
    //     {
    //         Serial.println("serial_input: " + serial_input);
    //     }
    // }
}