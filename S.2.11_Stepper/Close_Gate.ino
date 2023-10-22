void closeGate() {
  Serial.println(" Close Gate");

  digitalWrite(reedRelayPin, LOW);

  if (startTime == 0) {
    startTime = millis();
    closeTime = closeDelayTime + startTime;
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print("Close in");
    display.setTextSize(2);
    display.setCursor(0, 50);
    display.print ("Seconds");
    display.display();
    display.setTextSize(4);
  }
  currentTime = millis();
  countDown = (closeTime - currentTime) / 1000;
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Close in");
  display.setTextSize(2);
  display.setCursor(0, 50);
  display.print ("Seconds");
  display.display();
  display.setTextSize(4);

  display.setCursor(0, 20);
  //display.setTextColor(BLACK);

  display.print(countDown);
  display.display();

  if (currentTime >= closeTime) {
    homePosition();
    trace = "Closed";
    displayStat();
    startTime = 0;
    digitalWrite(greenLEDpin, LOW);
    digitalWrite(redLEDpin, HIGH);
  }
}
