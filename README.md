# SlicingDice Official Arduino Client (v2.0.0)

Official Arduino client for [SlicingDice](http://www.slicingdice.com/), Data Warehouse and Analytics Database as a Service.  

[SlicingDice](http://www.slicingdice.com/) is a serverless, API-based, easy-to-use and really cost-effective alternative to Amazon Redshift and Google BigQuery.

## Documentation

If you are new to SlicingDice, check our [quickstart guide](https://docs.slicingdice.com/docs/quickstart-guide) and learn to use it in 15 minutes.

Please refer to the [SlicingDice official documentation](https://docs.slicingdice.com/) for more information on [how to create a database](https://docs.slicingdice.com/docs/how-to-create-a-database), [how to insert data](https://docs.slicingdice.com/docs/how-to-insert-data), [how to make queries](https://docs.slicingdice.com/docs/how-to-make-queries), [how to create columns](https://docs.slicingdice.com/docs/how-to-create-columns), [SlicingDice restrictions](https://docs.slicingdice.com/docs/current-restrictions) and [API details](https://docs.slicingdice.com/docs/api-details).

### Note

SlicingDice's Arduino client currently supports only data insert commands. Let us
know if you application requires Arduino to query data from SlicingDice
and we'll make sure to add this feature to our backlog.

## Installing

[Click here]() to download our Arduino client as a `zip` file. After downloading it, you only need to import the zipped contents into your project path.

## Usage

```c
#include <SlicingDice.h>
#include <ArduinoJson.h>

// If you need a demo API key visit: https://docs.slicingdice.com/docs/try-before-you-buy
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
    byte dns[] = { 8, 8, 8, 8 };
    Ethernet.begin(mac, ip, dns, gateway, subnet);
}

// Send an insert command to Slicing Dice API and print the result
void loop() {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& data = jsonBuffer.createObject();
    JsonObject& nestedInsertion = data.createNestedObject("user1@slicingdice.com");
    nestedInsertion["age"] = 22;

    // Auto create non-existent fields
    JsonArray& autoCreate = data.createNestedArray("auto-create");
    autoCreate.add("table");
    autoCreate.add("column");

    // Insert object
    sd.insert(data);

    // Print result for debugging
    Serial.print("Status code: ");
    Serial.println(sd.statusCode);
    Serial.println(sd.response);
}
```

## Tests and examples

Whether you want to test the client installation or simply check more examples on how the client works, take a look at [tests directory](test/).

## Reference

`SlicingDice` encapsulates logic for sending requests to the [insert endpoint](https://docs.slicingdice.com/docs/how-to-insert-data).

### Attributes

* `statusCode (int)` - HTTP status code after inserting to SlicingDice. Should be `200` in ordinary circumstances or one of the HTTP requests defined at the [API errors](https://docs.slicingdice.com/docs/api-errors) section.
* `response (String)` - Response after inserting data. Useful for debugging purposes.

### Constructors

`SlicingDice(const char* apiKey, boolean production, const char* host, int port)`
* `apiKey (const char*)` - [API key](https://docs.slicingdice.com/docs/api-keys) to authenticate requests with the SlicingDice API.
* `production(boolean)` - (Default: true) If true the client will send requests to production end-point, otherwise to tests end-point.
* `host (const char*)` - (Default: api.slicingdice.com) [Connection endpoint](https://docs.slicingdice.com/docs/api-connection-and-headers) to use when generating requests to SlicingDice.
* `port (int)` - (Default: 80) Port to connect to when generating requests. Particularly useful when connect to `http://localhost`.

### `void insert(JsonObject& query)`
Insert data to existing entities or create new entities, if necessary. This method corresponds to a [POST request at /insert](https://docs.slicingdice.com/docs/how-to-insert-data).

#### Request example

```c
#include <SlicingDice.h>
#include <ArduinoJson.h>

// If you need a demo API key visit: https://docs.slicingdice.com/docs/try-before-you-buy
String apiKey = String("YOUR_API_KEY");
// if false will use test endpoint, otherwise production endpoint
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

// Send an insertion request to Slicing Dice API and print the result
void loop() {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& data = jsonBuffer.createObject();
    JsonObject& nestedInsertion = data.createNestedObject("user1@slicingdice.com");
    nestedInsertion["age"] = 22;
    
    // Auto create non-existent fields
    JsonArray& autoCreate = data.createNestedArray("auto-create");
    autoCreate.add("table");
    autoCreate.add("column");

    // Insert object
    sd.insert(data);

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
    "inserted-entities": 1,
    "inserted-fields": 1,
    "took": 0.023
}
```

## License

[MIT](https://opensource.org/licenses/MIT)
