// ---------------------------------------------------
// -------------------SCANNING------------------------
// ---------------------------------------------------

// full image capture routine
void takePhoto() {
  //runSteps();
  digitalWrite(ENABLE_XY, LOW);
  delay(timer);
  runScan();
  resetAfterScan();
  digitalWrite(ENABLE_XY, HIGH);
}

// run an image scan
void runScan() {
  Serial.println("Taking a scan");
  int dirX = 0;
  int dirY = 1;

  digitalWrite(DIR_X, dirX);
  digitalWrite(DIR_Y, dirY);

  delay(10);
  unsigned long start = micros();
  Serial.println("Starting 240 pixel row");
  for (int j = 0; j < HEIGHT; j++){
    Serial.print("-"); Serial.print(j); Serial.println("-");

    // Pre shift
    if (shiftPixels > 0) {
      for (int i=0; i<shiftPixels; i++) { moveStepX(); }
    }

    // Scan row
    for (int i = 0; i < WIDTH; i++){
      takeMeasurement(j,i);
      moveStepX();
    }

    // Post shift
    if (shiftPixels < 0) {
      for (int i=0; i<-shiftPixels; i++) { moveStepX(); }
    }

    // Next row row
    moveStepY();

    // Change direction of fast pin
    dirX = (dirX+1)%2;
    digitalWrite(DIR_X, dirX);
    delayMicroseconds(200);
  }

  // Print scan statistics
  unsigned long end = micros();
  const float perPixel = (end-start)/(240*240.0);
  Serial.printf("240 rows of 240 Pixel Read Operation took %.2f seconds, or %.2f microseconds per pixel\n", (end - start)/1000000., perPixel);
  Serial.print("Min  :  ");
  Serial.println(minVal/255., 3);
  Serial.print("Max  :  ");
  Serial.println(maxVal/255., 3);
  Serial.println("");
}

// reset position for next image
void resetAfterScan() {
  delayMicroseconds(200);
  Serial.println("Resetting position in 3...");
  delay(500);
  Serial.println("2...");
  delay(500);
  Serial.println("1...");
  delay(500);
  digitalWrite(DIR_Y, LOW);

  for(int i = 0; i < 240; i++){
    moveStepY();
  }
  Serial.println("Position reset");
}

