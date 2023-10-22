void homePosition() {
  checkSwitchState();
  digitalWrite(enablePin, LOW);
  digitalWrite(dirPin, HIGH);         //turn clockwise
  if (rotation == true) {
    digitalWrite (dirPin, LOW);
  }
  trace = "Closing";
  displayStat();

  while ((digitalRead(limitSwitchPin) == HIGH)) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayTime);
  }
  //checkSwitchState();

  digitalWrite(enablePin, HIGH);
  stepPosition = 0;
  gateCloseState = true;
  gateOpenState = false;
  trace = "Closed";
  displayStat();
  checkSwitchState();
}
