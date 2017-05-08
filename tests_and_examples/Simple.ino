#include <SlicingDice.h>
#include <ArduinoJson.h>

// Demo API key, if you need a new demo API key visit: https://panel.slicingdice.com/docs/#api-details-api-connection-api-keys-demo-key
String apiKey = String("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfX3NhbHQiOiJkZW1vMThtIiwicGVybWlzc2lvbl9sZXZlbCI6MywicHJvamVjdF9pZCI6MTc5LCJjbGllbnRfaWQiOjEwfQ.OTb6REW9JtYF9wVUZhXajq4wheU5ULNbM5iEmMCYhhM");
// if false will use test end-point, otherwise production end-point
boolean useProduction = false;
SlicingDice sd = SlicingDice(apiKey, useProduction);

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
    byte dns[] = { 8, 8, 8, 8 };
    Ethernet.begin(mac, ip, dns, gateway, subnet);
}

// Send an insert command to Slicing Dice API and print the result
void loop() {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& insertion = jsonBuffer.createObject();
    JsonObject& nestedQueryInsertion = insertion.createNestedObject("user1@slicingdice.com");
    nestedQueryInsertion["age"] = 22;
    insertion["auto-create-fields"] = true;
    sd.insert(insertion);
    Serial.print("Status code: ");
    Serial.println(sd.statusCode);
    Serial.println(sd.response);
}