#include "bot.hpp"
#include <LittleFS.h>

void Bot::init()
{
    Serial.println("Initializing the bot...");

    connectWifi();

    DynamicJsonDocument data = getMe();
    String id = data["id"];

    page_id = id;
}

void Bot::connectWifi()
{
    Serial.println("connecting wifi..");
    LittleFS.begin();

    WiFi.mode(WIFI_STA);

    Serial.print("Wifi ssid: ");
    Serial.println(WIFI_SSID);
    Serial.print("Wifi password: ");
    Serial.println(WIFI_PASSWORD);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting WiFi..");
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected!");

    ip_address = WiFi.localIP();
}

void Bot::publishPost(String post_content)
{
    Serial.println("Publishing post");
    if(!page_id)
    {
        Serial.println("Page id not found! Call init() to fix this problem");
    }

    DynamicJsonDocument doc(1024);
    doc["message"] = post_content;
    doc["access_token"] = ACCESS_TOKEN;

    urlencode_string(post_content);
    String req_data = "message=" + post_content + "&access_token=" + ACCESS_TOKEN;

    String uri = String("/") + page_id + String("/feed");
    String response = post(uri, req_data);
    Serial.print("Response:");
    Serial.println(response);
}

DynamicJsonDocument Bot::getMe()
{
    String response = get("/me?");
    Serial.println("response: " + response);

    DynamicJsonDocument doc(256);
    deserializeJson(doc, response);
    return doc;
}

String Bot::post(String uri, String data)
{
    String full_uri = String("/bot_http.php?") + data + String("&uri=") + String(api_host) +
                        String("/") + uri;
    Serial.println(full_uri);

    String header = String("GET ") + full_uri + " HTTP/1.1\r\n" +
            "Host: " + bot_host + "\r\n"
            "Connectin: close\r\n\r\n";

    WiFiClientSecure client;
    client.setFingerprint(bot_api_fingerprint);
    Serial.print("fingerprint: ");
    Serial.println(bot_api_fingerprint);
    Serial.print("host: ");
    Serial.println(bot_host);
    Serial.print("port: ");
    Serial.println(api_port);

    Serial.print("Preparing request...");
    while(!client.connect(bot_host, api_port))
    {
        Serial.print(".");
        delay(500);
    }

    return sendHTTPRequest(header, client);
}

String Bot::get(const char* uri)
{
    String full_uri = String(uri) + "access_token=" + ACCESS_TOKEN;
    Serial.println(full_uri);
    String header = String("GET ") + full_uri + " HTTP/1.1\r\n" + 
                    "Host: " + api_host + "\r\n" +
                    "Connection: close \r\n\r\n";
    
    WiFiClientSecure client;
    client.setFingerprint(fingerprint);
    Serial.print("fingerprint: ");
    Serial.println(fingerprint);
    Serial.print("host: ");
    Serial.println(api_host);
    Serial.print("port: ");
    Serial.println(api_port);

    Serial.print("Preparing request...");
    while(!client.connect(api_host, api_port))
    {
        Serial.print(".");
        delay(500);
    }

    return sendHTTPRequest(header, client);
}

String Bot::sendHTTPRequest(String header, WiFiClientSecure client)
{
    client.print(header);

    while(client.connected())
    {
        String line = client.readStringUntil('\n');
        if(line == "\r")
        {
            // reponse header received
            break;
        }
    }

    String line = "";
    while(client.available())
    {
        line += client.readStringUntil('\n');
    }

    return line;
}