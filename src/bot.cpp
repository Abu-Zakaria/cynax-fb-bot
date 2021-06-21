#include <Arduino.h>
#include "bot.hpp"
#include <LittleFS.h>
#include <ArduinoJson.h>

void Bot::init()
{
    Serial.println("Initializing the bot...");

    LittleFS.begin();
    char input_char = 0;
    String input_str = "";

    File file = LittleFS.open(access_token_file_name, "r");

    if(file)
    {
        Serial.print("your page access token is: ");
        while(file.available())
        {
            String line = file.readStringUntil('\n');
            
            Serial.println(line);
        }
    }
    else
    {
        Serial.print("Provide access token: ");

        bool break_loop = false;
        while(!break_loop)
        {
            if(Serial.available() > 0)
            {
                input_char = Serial.read();

                if(input_char != '\n')
                {
                    input_str += input_char;
                }
                else
                {
                    break_loop = true;
                    
                    file = LittleFS.open(access_token_file_name, "w");
                    String entry = input_str;
                    file.println(entry);
                    Serial.print("Entrying: ");
                    Serial.println(entry);
                }
            }
        }
    }
}

bool Bot::canConnect()
{
    return true;
}

void Bot::post(String content)
{
    // 
}