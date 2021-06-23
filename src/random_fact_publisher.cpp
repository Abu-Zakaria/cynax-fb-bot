#include "random_fact_publisher.hpp"

RandomFactPublisher::RandomFactPublisher(Bot &u_bot)
{
    bot = u_bot;
}

void RandomFactPublisher::begin()
{
    running = true;

    while(running)
    {
        post();
        delay(1000 * 60 * 5);
    }
}

void RandomFactPublisher::post()
{
    String uri = "/api";
    String header = String("GET ") + uri + " HTTP/1.1\r\n" + 
                    "Host: " + host + "\r\n" +
                    "Connection: close \r\n\r\n";
    
    WiFiClientSecure client;

    client.setFingerprint(this->fingerprint);

    Serial.print("Preparing request...");
    Serial.println(header);
    while(!client.connect(host, port))
    {
        Serial.print(".");
        delay(500);
    }

    String response = bot.sendHTTPRequest(header, client);

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, response);
    String fact = doc["data"];

    client.stopAll();

    bot.publishPost(fact + String(" linebreak:|]"));
    Serial.println("Post published");
}