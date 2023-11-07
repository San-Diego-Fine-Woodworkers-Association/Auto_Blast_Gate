void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

 Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0X3C);
  trace = "Booting";
  displayStat();

  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  /*while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
*/
delay(3000);

//------------------------------------------------------------------
  ArduinoOTA
  .onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  })
  .onEnd([]() {
    Serial.println("\nEnd");
  })
  .onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  })
  .onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  ArduinoOTA.setHostname(gateName);

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

//------------------------------------------------------------------

  if (boardID == 1 || boardID == 3 || boardID == 4 || boardID == 8)             SA();
  if (boardID == 2 || boardID == 5 || boardID == 6)                             SB();
  // if(boardID ==1 ||boardID ==3 || boardID==4)                                SC();
  if (boardID == 11 ||boardID == 12 || boardID == 16 )                          SD();
  if (boardID ==14 ||boardID >=19 || boardID == 18  || boardID == 22)                             SE();
  if (delayTime==9999) errorDisplay();


  pinMode(ANALOG_PIN_IN, INPUT);
  pinMode(reedRelayPin, OUTPUT);
  pinMode(greenLEDpin, OUTPUT);
  pinMode(redLEDpin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(limitSwitchPin, INPUT_PULLUP);
  pinMode(gateOn, OUTPUT);
  pinMode(gateOff, OUTPUT);
  // pinMode(manualSwitchStatePin, INPUT_PULLUP);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode (linkPin, INPUT_PULLUP);
  pinMode (speedPin, OUTPUT);

  digitalWrite(greenLEDpin, HIGH);
  digitalWrite(redLEDpin, HIGH);
  digitalWrite(reedRelayPin, LOW);
  digitalWrite(speedPin, HIGH);
  Serial.println("Starting");
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0X3C);
  trace = "Start";
  displayStat();
//------------------------------------------------------------------
  //                               Blast Gate Controller Setup
  ArduinoOTA.handle();
 
 homePosition();
  closeDelayTime = closeDelayTime * gateDelaySeconds;

  if (sensorIn > trigger)
  {
    startTime = 0;
    openGate();
    trace = "open";
    displayStat();
    startTime = 0;
  }

  if (sensorIn < trigger)
  {
    trace = "Closed";
    displayStat();

  }
}
