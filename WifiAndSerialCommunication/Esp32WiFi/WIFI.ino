//initalize Wifi.
void initWifi(const char* ssid, const char* pass) {
  WiFi.begin(ssid, pass);
  Serial.println("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

  }
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());
}

//sends data to webserver endpoint with GET function. Sets newData to false when send is complete.
void sendData(char* serverPath) {

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(serverPath);
    http.begin(serverPath);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("HTTP response: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else {
      Serial.print("error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  newData = false;
}

//receives Data from webserer endpoint specified by parameter. Returns the data received.
String receiveData(char* server){
  String payload = "";
  if (WiFi.status() == WL_CONNECTED){
    http.begin(server);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      Serial.print("HTTP response: ");
      Serial.println(httpResponseCode);
      payload = http.getString();
      Serial.println(payload);
    }
    else{
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  return payload;
}
