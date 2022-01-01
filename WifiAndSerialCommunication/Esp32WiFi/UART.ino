//Initiates Serial communication, Serial2 for arduino and Serial for serial monitor.
void initSerials() {
  Serial2.begin(38400, SERIAL_8N1, RXD2, TXD2);
  Serial.begin(38400);
}
//reads uart and checks which type of command to handle.
void readUart() {
  static byte index = 0;
  static bool receiving = false;

  char receivedChar;
  //while there's somethin to read on UART and newData has been handled.
  while (Serial2.available() > 0 && newData == false) {
    receivedChar = Serial2.read(); //check the first char to arrive to see which type of command it is.
    if (receiving == true) { //if character was ! start building string to until endline is received.
      if (receivedChar != '\n') {
        receivedChars[index] = receivedChar;
        index++;

        if (index >= numChars) {
          index = numChars - 1; 
        }
      }
      else { //finish the string and set receiving back to false and index to 0 and newData to true.
        receivedChars[index] = '\0';
        receiving = false;
        index = 0;
        newData = true;
      }
    }
    else if (receivedChar == '!') { //! is for getting name and score from arduino and send to webserver/db.
      receiving = true;
    }
    else if (receivedChar == '@') { //@ is for getting highscore from webserver and send it to arduino.
      String payload = receiveData("http://whysnakes.herokuapp.com/gethighscore");
      if (payload != ""){
        sendUart(payload+'\n');
      }
      else{
        Serial.print("failed to get data");
      }
    }
    else if (receivedChar == '+') { //+ is for getting speed value from webserver and send it to arduino.
      String speedDemon = receiveData("http://whysnakes.herokuapp.com/getspeed");
      if (speedDemon != ""){
        sendUart(speedDemon + "\n");
      }
    }
  }
}

//parses the string received from arduino uart and stores name and score in variables.
void parseUart() {
    char* tokenIndex;
    tokenIndex = strtok(tempChars, ",");
    strcpy(namee, tokenIndex);
    tokenIndex = strtok(NULL, ",");
    strcpy(score, tokenIndex);
}

//sends payload via UART to arduino and serial monitor.
void sendUart(String payload) {
  Serial2.print(payload);
  Serial.print(payload);
}
