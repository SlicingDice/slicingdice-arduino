# SlicingDice Official Arduino Client (v1.0)

Official Arduino client for [SlicingDice](http://www.slicingdice.com/), Data Warehouse and Analytics Database as a Service.  

[SlicingDice](http://www.slicingdice.com/) is a serverless, API-based, easy-to-use and really cost-effective alternative to Amazon Redshift and Google BigQuery.

## Documentation

If you are new to SlicingDice, check our [quickstart guide](http://panel.slicingdice.com/docs/#quickstart-guide) and learn to use it in 15 minutes.

Please refer to the [SlicingDice official documentation](http://panel.slicingdice.com/docs/) for more information on [analytics databases](http://panel.slicingdice.com/docs/#analytics-concepts), [data modeling](http://panel.slicingdice.com/docs/#data-modeling), [indexing](http://panel.slicingdice.com/docs/#data-indexing), [querying](http://panel.slicingdice.com/docs/#data-querying), [limitations](http://panel.slicingdice.com/docs/#current-slicingdice-limitations) and [API details](http://panel.slicingdice.com/docs/#api-details).

## Installing

[Click here]() to download our Arduino client as a `zip` file. After downloading it, you only need to import the zipped contents into your project path.

## Usage

```c
#include <SlicingDice.h>
#include <ArduinoJson.h>

// If you need a demo API key visit: https://panel.slicingdice.com/docs/#api-details-api-connection-api-keys-demo-key
String apiKey = String("YOUR_API_KEY");
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
    byte dnxs[] = { 8, 8, 8, 8 };
    Ethernet.begin(mac, ip, dnxs, gateway, subnet);
}

// Send an indexation command to Slicing Dice API and print the result
void loop() {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& queryIndex = jsonBuffer.createObject();
    JsonObject& nestedQueryIndex = queryIndex.createNestedObject("user1@slicingdice.com");
    nestedQueryIndex["age"] = 22;
    // Auto create non-existent fields
    queryIndex["auto-create-fields"] = true;

    // Index object
    sd.index(queryIndex);

    // Print result for debugging
    Serial.print("Status code: ");
    Serial.println(sd.statusCode);
    Serial.println(sd.response);
}
```

## Tests and examples

Whether you want to test the client installation or simply check more examples on how the client works, take a look at [tests directory](test/).

## Reference

`SlicingDice` encapsulates logic for sending requests to the [index endpoint](http://panel.slicingdice.com/docs/#api-details-api-endpoints-post-index).

### Attributes

* `statusCode (int)` - HTTP status code after indexing to SlicingDice. Should be `200` in ordinary circumstances or one of the HTTP requests defined at the [API errors](http://panel.slicingdice.com/docs/#api-details-api-errors) section.
* `response (String)` - Response after indexing data. Useful for debugging purposes.

### Constructors

`SlicingDice(const char* apiKey, boolean production)`
* `apiKey (const char*)` - [API key](http://panel.slicingdice.com/docs/#api-details-api-connection-api-keys) to authenticate requests with the SlicingDice API.
* `production(boolean)` - If true the client will send requests to production end-point, otherwise to tests end-point

`SlicingDice(const char* apiKey, const char* host)`
* `apiKey (const char*)` - [API key](http://panel.slicingdice.com/docs/#api-details-api-connection-api-keys) to authenticate requests with the SlicingDice API.
* `host (const char*)` - [Connection endpoint](http://panel.slicingdice.com/docs/#api-details-api-connection-connection-endpoints) to use when generating requests to SlicingDice.

`SlicingDice(const char* apiKey, const char* host, int port)`
* `apiKey (const char*)` - [API key](http://panel.slicingdice.com/docs/#api-details-api-connection-api-keys) to authenticate requests with the SlicingDice API.
* `host (const char*)` - [Connection endpoint](http://panel.slicingdice.com/docs/#api-details-api-connection-connection-endpoints) to use when generating requests to SlicingDice.
* `port (int)` - Port to connect to when generating requests. Particularly useful when connect to `http://localhost`.

`SlicingDice(const char* apiKey, const char* host, int port, boolean production)`
* `apiKey (const char*)` - [API key](http://panel.slicingdice.com/docs/#api-details-api-connection-api-keys) to authenticate requests with the SlicingDice API.
* `host (const char*)` - [Connection endpoint](http://panel.slicingdice.com/docs/#api-details-api-connection-connection-endpoints) to use when generating requests to SlicingDice.
* `port (int)` - Port to connect to when generating requests. Particularly useful when connect to `http://localhost`.
* `production(boolean)` - If true the client will send requests to production end-point, otherwise to tests end-point

### `void index(JsonObject& query)`
Index data to existing entities or create new entities, if necessary. This method corresponds to a [POST request at /index](http://panel.slicingdice.com/docs/#api-details-api-endpoints-post-index).

#### Request example

```c
#include <SlicingDice.h>
#include <ArduinoJson.h>

// If you need a demo API key visit: https://panel.slicingdice.com/docs/#api-details-api-connection-api-keys-demo-key
String apiKey = String("YOUR_API_KEY");
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
    byte dnxs[] = { 8, 8, 8, 8 };
    Ethernet.begin(mac, ip, dnxs, gateway, subnet);
}

// Send an indexation command to Slicing Dice API and print the result
void loop() {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& queryIndex = jsonBuffer.createObject();
    JsonObject& nestedQueryIndex = queryIndex.createNestedObject("user1@slicingdice.com");
    nestedQueryIndex["age"] = 22;
    // Auto create non-existent fields
    queryIndex["auto-create-fields"] = true;

    // Index object
    sd.index(queryIndex);

    // Print result for debugging
    Serial.print("Status code: ");
    Serial.println(sd.statusCode);
    Serial.println(sd.response);
}
```

#### Output example

```
Status code: 200
{
    "status": "success",
    "indexed-entities": 1,
    "indexed-fields": 1,
    "took": 0.023
}
```

## License

[MIT](https://opensource.org/licenses/MIT)
