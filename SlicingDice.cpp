#include "SlicingDice.h"


SlicingDice::SlicingDice(const char* apiUserKey) {
    host = "api.slicingdice.com";
    port = 80;
    apiKey = apiUserKey;
    test = 0;
}

SlicingDice::SlicingDice(const char* apiUserKey, const char* customHost) {
    host = customHost;
    port = 80;
    apiKey = apiUserKey;
    test = 0;
}

SlicingDice::SlicingDice(const char* apiUserKey, const char* customHost, int customPort) {
    host = customHost;
    port = customPort;
    apiKey = apiUserKey;
    test = 0;
}

SlicingDice::SlicingDice(const char* apiUserKey, const char* customHost, int customPort, int customTest) {
    host = customHost;
    port = customPort;
    apiKey = apiUserKey;
    test = customTest;
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

    client.print(F("POST /v1/"));
    if (test == 1) {
      client.print("test/");
    }
    client.println(F("index/ HTTP/1.1"));
    client.println(F("Content-Type: application/json"));
    client.print(F("Authorization: "));
    client.println(apiKey);
    client.println(F("Connection: close"));
    client.print(F("Content-Length: "));
    client.println(strlen(query));
    client.println();
    client.print(query);
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
