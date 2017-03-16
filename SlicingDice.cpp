#include "SlicingDice.h"


SlicingDice::SlicingDice(String apiUserKey, boolean production) {
    construct(apiUserKey, "api.slicingdice.com", 80, production);
}

SlicingDice::SlicingDice(String apiUserKey, const char* customHost) {
    construct(apiUserKey, customHost, 80, true);
}

SlicingDice::SlicingDice(String apiUserKey, const char* customHost, int customPort) {
    construct(apiUserKey, customHost, customPort, true);
}

SlicingDice::SlicingDice(String apiUserKey, const char* customHost, int customPort, boolean production) {
    construct(apiUserKey, customHost, customPort, production);
}

void SlicingDice::construct(String apiUserKey, const char* customHost, int customPort, boolean production) {
    host = customHost;
    port = customPort;
    apiKey = apiUserKey;
    useProduction = production;
}

/* Index data on Slicing Dice API
 *
 * query - the query to send to Slicing Dice API
 */
void SlicingDice::index(JsonObject& query) {
    char queryConverted[query.measureLength() +  1];
    query.printTo(queryConverted, sizeof(queryConverted));
    makeRequest(queryConverted);
}

/* Make a HTTP request to Slicing Dice API 
 * 
 * query - the query to send to Slicing Dice API
 */
void SlicingDice::makeRequest(const char* query){
    client.connect(host, port);
    while (!client.connected()) {
        client.connect(host, port);
    }

    String testEndPoint = String("");

    if (!useProduction) {
        testEndPoint = String("test/");
    }

    client.println("POST /v1/" + testEndPoint + "index HTTP/1.1");
    client.println(F("Content-Type: application/json"));
    String hostString = String(host);
    client.println("Host: " + hostString);
    client.println("Authorization: " + apiKey);
    client.println(F("Connection: close"));

    String actualLength = String(strlen(query));
    client.println("Content-Length: " + actualLength);
    client.println();  
    client.println(query);
    readResponse();    
    client.stop();
}

//Read response from HTTP request to Slicing Dice API
void SlicingDice::readResponse(){
    response = " ";
    boolean currentLineIsBlank = true;
    boolean hasBody = false;
    boolean inStatus = false;

    char statusCodeRequest[4];
    int i = 0;

    while (client.connected()){
        if (client.available()) {
            char c = client.read();
            // Set status code request
            if(c == ' ' && !inStatus){
                inStatus = true;
            }

            if(inStatus && i < 3 && c != ' '){
                statusCodeRequest[i] = c;
                i++;
            }
            if(i == 3){
                statusCodeRequest[i] = '\0';
                statusCode = atoi(statusCodeRequest);
            }

            // Set response request
            if(hasBody){
                if(response != NULL) response.concat(c);
            } else {
                if (c == '\n' && currentLineIsBlank) {
                    hasBody = true;
                }

                else if (c == '\n') {
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    currentLineIsBlank = false;
                }
            }
        }
    }
    response.trim();
}
