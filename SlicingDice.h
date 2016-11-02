#include <Arduino.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <Ethernet.h>


class SlicingDice {

public:
	SlicingDice(const char* apiUserKey);
	SlicingDice(const char* apiUserKey, const char* customHost);
	SlicingDice(const char* apiUserKey, const char* customHost, int customPort);

	void index(JsonObject& query);
	int statusCode;
	String response;

private:
	void makeRequest(const char* query);
	void readResponse();

	const char* apiKey;
	const char* host;
	int port;
	EthernetClient client;
};