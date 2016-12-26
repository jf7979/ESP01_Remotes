#include <ESP8266WiFi.h>

const char *ssid = "ESPAP";
const char *password = "EspPass7979";

//http://192.168.4.1

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

int val0 = 1;
int val2 = 1;

void setup() {

  // prepare GPIO1
  pinMode(0, OUTPUT);
  digitalWrite(0, 1);

  // prepare GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, 1);

  // Connect to WiFi network

  WiFi.softAP(ssid, password);
  //IPAddress myIP = WiFi.softAPIP();
  // Start the server
  server.begin();

}




void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data

  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');

  client.flush();

  // Match the request

  if (req.indexOf("/gpio0/on") != -1)
  {
    val0 = 0;
  }
  else if (req.indexOf("/gpio2/on") != -1)
  {
    val2 = 0;
  }
  else if (req.indexOf("/gpio0/off") != -1)
  {
    val0 = 1;
  }
  else if (req.indexOf("/gpio2/off") != -1)
  {
    val2 = 1;
  }


  // Set GPIO1 according to the request
  digitalWrite(0, val0);
  // Set GPIO2 according to the request
  digitalWrite(2, val2);

  //client.flush();

  // Prepare the response
  //String s = "ACK";

  // Send the response to the client
  //client.print(s);

  // Set GPIO1 according to the request
  //digitalWrite(0, 1);
  // Set GPIO2 according to the request
  //digitalWrite(2, 1);


}
