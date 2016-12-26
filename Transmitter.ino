#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


const char* ssid     = "ESPAP";
const char* password = "EspPass7979";
int switchGPIO0;
int switchGPIO2;
int gpio0SwitchState = HIGH;
int gpio2SwitchState = HIGH;

void setup() {
  // Blue built in LED
  pinMode(LED_BUILTIN, OUTPUT);
  // GPIO0 as an input
  pinMode(0, INPUT);
  // GPIO2 as an input
  pinMode(2, INPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
  }
  digitalWrite(LED_BUILTIN, LOW);

}

void loop() {

  //Read gpio inputs each loop
  switchGPIO0 = digitalRead(0);
  switchGPIO2 = digitalRead(2);


  // Send http request each loop as long as gpio is LOW, receiver will handle the traffic
  if (switchGPIO0 == LOW && gpio0SwitchState == HIGH)
  {
    HTTPClient http;
    http.begin("http://192.168.4.1/gpio0/on"); //HTTP
    // start connection and send HTTP header
    int httpCode = http.GET();
    http.end();
    gpio0SwitchState = LOW;
  }
  else if (switchGPIO0 == HIGH && gpio0SwitchState == LOW)
  {
    // If switch is now OFF but last request was ON, send request to turn off
    HTTPClient http;
    http.begin("http://192.168.4.1/gpio0/off"); //HTTP
    // start connection and send HTTP header
    int httpCode = http.GET();
    http.end();
    gpio0SwitchState = HIGH;
  }




  if (switchGPIO2 == LOW && gpio2SwitchState == HIGH)
  {
    HTTPClient http;
    http.begin("http://192.168.4.1/gpio2/on"); //HTTP
    // start connection and send HTTP header
    int httpCode = http.GET();
    http.end();
    //switchGPIO2 = HIGH;
    gpio2SwitchState = LOW;
  }
  else if (switchGPIO2 == HIGH && gpio2SwitchState == LOW)
  {
    // If switch is now OFF but last request was ON, send request to turn off
    HTTPClient http;
    http.begin("http://192.168.4.1/gpio2/off"); //HTTP
    // start connection and send HTTP header
    int httpCode = http.GET();
    http.end();
    gpio2SwitchState = HIGH;
  }




  // If wif is not connected, go in to a flashing error mode
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
  }

  if (WiFi.status() = WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN, LOW);
  }


}
