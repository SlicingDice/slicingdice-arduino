#include <Arduino.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <Ethernet.h>


class SlicingDice {

public:
	SlicingDice(String apiUserKey, boolean useProduction = false, const char* customHost = "api.slicingdice.com", int customPort=80);

	void insert(JsonObject& data);
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