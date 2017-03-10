#include <Arduino.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <Ethernet.h>


class SlicingDice {

public:
	SlicingDice(String apiUserKey);
	SlicingDice(String apiUserKey, const char* customHost);
	SlicingDice(String apiUserKey, const char* customHost, int customPort);
  	SlicingDice(String apiUserKey, const char* customHost, int customPort, boolean production);

	void index(JsonObject& query);
	int statusCode;
	String response;

private:
	void makeRequest(const char* query);
  	void construct(String apiUserKey, const char* customHost, int customPort, boolean production);
	void readResponse();

	String apiKey;
	const char* host;
	int port;
	boolean useProduction;
	EthernetClient client;
};