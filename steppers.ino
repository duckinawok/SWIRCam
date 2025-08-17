// ---------------------------------------------------
// ---------------STEPPER MOTORS----------------------
// ---------------------------------------------------

// basic movement
void moveStepX() {
  digitalWrite(STEP_X, HIGH);
  delayMicroseconds(45);
  digitalWrite(STEP_X, LOW);
  delayMicroseconds(45);
}

void moveStepY() {
  delayMicroseconds(45);
  digitalWrite(STEP_Y, HIGH);
  delayMicroseconds(45);
  digitalWrite(STEP_Y, LOW);
}


// taring and centering
void centre() {
  //runSteps();
  digitalWrite(ENABLE_XY, LOW);
  delay(100);
  moveTareX();
  moveCentreX();
  moveTareY();
  moveCentreY();
  digitalWrite(ENABLE_XY, HIGH);
}

void moveTareX() {
  Serial.println("Start taring process X.");
  digitalWrite(DIR_X, HIGH);
  delay(100);

  while(digitalRead(SWITCH_XY)==LOW){
    digitalWrite(STEP_X, HIGH);
    delay(1);
    digitalWrite(STEP_X, LOW);
    delay(1);
  }
  Serial.println("Contact made! Tared X.");
}

void moveTareY() {
  Serial.println("Start taring process Y.");
  digitalWrite(DIR_Y, LOW);
  delay(100);

  while(digitalRead(SWITCH_XY)==LOW){
    digitalWrite(STEP_Y, HIGH);
    delay(1);
    digitalWrite(STEP_Y, LOW);
    delay(1);
  }
  Serial.println("Contact made! Tared Y.");
}

void moveCentreX() {
  Serial.println("Start centering process.");
  digitalWrite(DIR_X, LOW);
  int steps_X = 0;
  int target_X = stepsUntilContactX*stepsMultiplierX-120;
  delay(100);

  while(steps_X < target_X){
    digitalWrite(STEP_X, HIGH);
    delay(1);
    digitalWrite(STEP_X, LOW);
    delay(1);
    steps_X+=1;
  }
  Serial.println("Centered!");
}

void moveCentreY() {
  Serial.println("Start centering process.");
  digitalWrite(DIR_Y, HIGH);
  int steps_Y = 0;
  int target_Y = stepsUntilContactY*stepsMultiplierY-120;
  delay(100);

  while(steps_Y < target_Y){
    digitalWrite(STEP_Y, HIGH);
    delay(1);
    digitalWrite(STEP_Y, LOW);
    delay(1);
    steps_Y+=1;
  }
  Serial.println("Centered!");
}

