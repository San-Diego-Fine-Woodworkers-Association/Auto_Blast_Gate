void openGate() {
  Serial.print(" Open Gate");
  printStat();

  digitalWrite(reedRelayPin, HIGH);

  if (digitalRead(limitSwitchPin) == HIGH) {
    homePosition();
    printStat();
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(0, 20);
  display.print("Opening");
  display.display();

  digitalWrite(enablePin, LOW);
  //digitalWrite(reedRelayPin, LOW);

  digitalWrite(dirPin, LOW);       // turn counterClockwise
  if (rotation == true) {
    digitalWrite (dirPin, HIGH);
  }
  for (stepPosition = 0; stepPosition < fullRunSteps; stepPosition++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayTime);
  }
  digitalWrite(enablePin, HIGH);
  gateOpenState = true;
  trace = "Open";
  displayStat();
  startTime = 0;

  //digitalWrite(reedRelayPin, HIGH);
  digitalWrite(greenLEDpin, HIGH);
  digitalWrite(redLEDpin, LOW);
  digitalWrite(enablePin, HIGH);
}
