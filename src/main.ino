#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "secrets.h"

const char* api_url = "https://api.weatherapi.com/v1/current.json?key=" APIKEY "&q=Milwaukee";
'''
api get temp_f from json response
get condition from json response
get wind_mph from json response
get feelslike_f from json response
'''

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to WiFi...");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("Connected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    if(WiFi.status() == WL_CONNECTED){
        HTTPClient http;

        http.begin(api_url);
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0) {
            String payload = http.getString();
            Serial.println(payload);
        } else {
            Serial.print("Error on HTTP request: ");
            Serial.println(httpResponseCode);
        }
        http.end();
    }

    delay(60000); // Wait 1 minute
}