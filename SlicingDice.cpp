#include "SlicingDice.h"


SlicingDice::SlicingDice(String apiUserKey) {
    host = "api.slicingdice.com";
    port = 80;
    apiKey = apiUserKey;
    test = 0;
}

SlicingDice::SlicingDice(String apiUserKey, const char* customHost) {
    host = customHost;
    port = 80;
    apiKey = apiUserKey;
    test = 0;
}

SlicingDice::SlicingDice(String apiUserKey, const char* customHost, int customPort) {
    host = customHost;
    port = customPort;
    apiKey = apiUserKey;
    test = 0;
}

SlicingDice::SlicingDice(String apiUserKey, const char* customHost, int customPort, int customTest) {
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

    String testEndPoint = String("");

    if (test == 1) {
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
