// ---------------------------------------------------
// -------------------LOOP----------------------------
// ---------------------------------------------------

// main running loop
void loop() {
  // Parse serial commands
  if (Serial.available()){
    command(Serial.readStringUntil('\n'));
  }

  // Probe and print adc values (use the serial plotter!)
  if (probing) {
    probe();
  }

  // Calibrate if button pressed
  if (digitalRead(CAL_BUTTON) == HIGH) {
    centre();
    delay(300); // debounce
  }
  
  // Run scan if button pressed or command entered
  if (digitalRead(PHOTO_BUTTON) == HIGH or running) {
    running = 0;
    takePhoto();
    if (zoom) { displayScale(); }
    else { displayPhoto(); }
    savePhoto();
    delay(300); // debounce
  }
}

