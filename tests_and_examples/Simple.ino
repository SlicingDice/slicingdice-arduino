#include "SlicingDice.h"
#include <ArduinoJson.h>

// Demo API key, if you need a new demo API key visit: https://panel.slicingdice.com/docs/#api-details-api-connection-api-keys-demo-key
String apiKey = String("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfX3NhbHQiOiJkZW1vNTZtIiwicGVybWlzc2lvbl9sZXZlbCI6MywicHJvamVjdF9pZCI6MjE3LCJjbGllbnRfaWQiOjEwfQ.rKHWahhcTN8Hvhns8-O2_KwjC_b3SFHd3kqZLyDMrfc");
const char* host = "api.slicingdice.com";
int port = 80;
// test = 1 indicates that will use test end-point, 0 indicates will use production end-point
int test = 1;
SlicingDice sd = SlicingDice(apiKey, host, port, test);

void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
    }

    // Arduino network settings, should match your internet connection properties
    byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
    byte ip[] = { 192, 168, 0, 10 };
    byte gateway[] = { 192, 168, 0, 1 }; 
    byte subnet[] = { 255, 255, 255, 0 };
    byte dnxs[] = { 8, 8, 8, 8 };
    Ethernet.begin(mac, ip, dnxs, gateway, subnet);
}

// Send an indexation command to Slicing Dice API and print the result
void loop() {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& queryIndex = jsonBuffer.createObject();
    JsonObject& nestedQueryIndex = queryIndex.createNestedObject("user1@slicingdice.com");
    nestedQueryIndex["age"] = 22;
    queryIndex["auto-create-fields"] = true;
    sd.index(queryIndex);
    Serial.print("Status code: ");
    Serial.println(sd.statusCode);
    Serial.println(sd.response);
}