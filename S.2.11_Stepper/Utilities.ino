
//------------------------------------------------------------------------------
void checkSwitchState() {

  ArduinoOTA.handle();


  //trace = "checkState";
  //displayStat();
  //delay(displayTime);

  if (digitalRead(limitSwitchPin) == HIGH) {
    limitSwitchState = false;
    gateCloseState = false;
  }

  else {
    limitSwitchState = true;
    gateOpenState = false;
    gateCloseState = true;
    digitalWrite(greenLEDpin, LOW);
    digitalWrite(redLEDpin, HIGH);
  } 
}

//--------------------------------------------------------------------------
void keepWiFiAlive (void * parameters) {

  for (;;) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Connected");
      vTaskDelay (30000 / portTICK_PERIOD_MS);   //wait 30 seconds before checking the status again
      continue;
    }
    unsigned long startAttempTime = millis();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("Attempting to connect");
    while (WiFi.status() != WL_CONNECTED &&
           (millis() - startAttempTime) < WiFiTimeOutMS) {}

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Connection failed!");
      vTaskDelay (30000 / portTICK_PERIOD_MS);   //wait 30 seconds before reattempting to connect to the WiFi
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.print ("WiFi connected  IP Address= ");
      Serial.println ( WiFi.localIP());
    }
  }
}

//------------------------------------------------------------------------------
void printStat() {
  Serial.print(loopCount);
  Serial.print("   ");
  Serial.print(trace);
  Serial.print("   ");
  Serial.print(sensorIn);
  Serial.print("   ");
  //Serial.print(stepPosition);
  Serial.print("   ");
  Serial.print (WiFi.localIP());;
  Serial.print("   ");
  Serial.print(millis());
  Serial.print("   ");
  Serial.print((currentTime));
  Serial.print("   ");
  Serial.print((startTime));
  Serial.print("   ");
  x = currentTime - startTime;
  Serial.print(closeTime);
  Serial.println("   ");
}
//------------------------------------------------------------------------------

void displayStat() {

  ArduinoOTA.handle();
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(80, 53);
  display.print (ver);
  display.setTextSize(3);
  display.setCursor(0, 10);
  display.print(trace);
  display.print("        ");
  display.setTextSize(1);
  display.setCursor(0,43);
  display.print(gateName);
  display.setCursor(0, 53);
  display.print (WiFi.localIP());
  display.display();
}

//----------------------------------------
void errorDisplay() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(4);
  display.setCursor(0, 20);
  display.print("Error");
  display.display();
  delay(20000);
  while (delayTime == delayTime) {
  }
}

//----------------------------------------
void SA() {
  linkPin =               33;
  stepPin =               04;
  dirPin =                02;
  enablePin  =            16;
  combo =                  false;
  delayTime =              400;
  fullRunSteps =           2500;
  rotation =               false;
}

//----------------------------------------
void SB() {
  linkPin =               33;
  stepPin =               04;
  dirPin =                02;
  enablePin  =            16;
  combo =                  false;
  delayTime =              110;
  fullRunSteps =           10000;
  rotation =               false;
}

//----------------------------------------
void SC() {
  combo =                  false;
  delayTime =              400;
  fullRunSteps =           2500;
  rotation =               false;
}

//----------------------------------------
void SD() {
  delayTime =              110;
  fullRunSteps =           10000;
  rotation =               false;
}

//----------------------------------------
void SE() {
  delayTime =              75;
  fullRunSteps =           21000;
  rotation =               true;
}
