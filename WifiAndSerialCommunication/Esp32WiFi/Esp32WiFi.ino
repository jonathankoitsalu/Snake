#include <WiFi.h>
#include <HTTPClient.h>
//defines for Serial2 ports
#define RXD2 16
#define TXD2 17
//variables to store WiFi info.
const char* ssid = "";
const char* pass = "";
//global variables used by multiple functions.
HTTPClient http;
bool newData = false;
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];
char namee[16] = {0};
char score[16] = {0};


void setup() {
  //initalize Serial comms and WiFi.
  initSerials();
  initWifi(ssid, pass);
  Serial.println("ready");
}

void loop() {
  
  readUart();
  //if a new score has been sent from arduino parse it and send it to webserver.
  //
  if (newData == true) { 
    strcpy(tempChars, receivedChars);
    parseUart();
    //start the char array that holds the webserver end point and add name and score to the endpoint.
    char serverPath[128] = "http://whysnakes.herokuapp.com/score?apikey=ärdetbajenkanske?&name=";
    strcat(serverPath, namee);
    strcat(serverPath, "&score=");
    strcat(serverPath, score);
    sendData(serverPath);
  }
}
