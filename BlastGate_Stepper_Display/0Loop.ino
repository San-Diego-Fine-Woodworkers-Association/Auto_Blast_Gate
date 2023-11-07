void loop() {
  ArduinoOTA.handle();
  loopCount++;
  checkSwitchState();

  sensorIn = (analogRead(ANALOG_PIN_IN));

   /* 
  if (((digitalRead(linkPin)) == false))
  {
    link();
  }
 */
  
  if (sensorIn > trigger) {
    startTime = 0;
    if (gateOpenState != true)
    {
      Serial.println("Loop 16...");
      openGate();
    }
    else
    {
      trace = "open";
      displayStat();
      startTime = 0;
    }
  }


  if (sensorIn < trigger) {
    if (gateOpenState == true)
    {
      Serial.println("Loop 31...");
      ArduinoOTA.handle();
      closeGate();
    }

    //digitalWrite(greenLEDpin, HIGH);
    // digitalWrite(redLEDpin, LOW);
    printStat();

if(displayFlag ==     false) 
  {
    trace ="";
    displayStat();
    displayFlag=true;
  }

    delay(holdTime);
   ArduinoOTA.handle();
  }
}
