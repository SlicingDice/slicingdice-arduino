#include <SlicingDice.h>
#include <ArduinoJson.h>

SlicingDice sd = SlicingDice("mytoken");

void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
    }

    // Arduino network settings
    byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
    byte ip[] = { 192, 168, 1, 10 };
    byte gateway[] = { 192, 168, 1, 1 }; 
    byte subnet[] = { 255, 255, 255, 0 };
    byte dnxs[] = { 8, 8, 8, 8 };
    Ethernet.begin(mac, ip, dnxs, gateway, subnet);
}

void loop() {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& queryIndex = jsonBuffer.createObject();
    JsonObject& nestedQueryIndex = queryIndex.createNestedObject("user1@slicingdice.com");
    nestedQueryIndex["age"] = 22;
    sd.index(queryIndex);
    Serial.print("Status code: ");
    Serial.println(sd.statusCode);
    Serial.println(sd.response);
}
