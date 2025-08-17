// ---------------------------------------------------
// ----------------SERIAL COMMANDS--------------------
// ---------------------------------------------------

void command(String cmd) {
  if (cmd.equalsIgnoreCase("START")) {
    Serial.println("STARTED");
    running = true;
  } 
  else if (cmd.equalsIgnoreCase("PROBE")) {
    probing = true;
  }
  else if (cmd.equalsIgnoreCase("HALT") and probing == 1){
    probing = false;
  }
  else if (cmd.equalsIgnoreCase("ZOOM")){
    zoom = !zoom;
    if (zoom) {
      displayScale();
    }
    else {
      displayPhoto();
    }
  }
  else if (cmd.substring(0,6).equalsIgnoreCase("SHIFT ")){
    shiftPixels = cmd.substring(6).toInt();
    Serial.print("Pixel shift set to ");
    Serial.println(shiftPixels);
  }
  else if (cmd.substring(0,8).equalsIgnoreCase("SAMPLES ")){
    numSamples = cmd.substring(8).toInt();
    Serial.print("Samples per pixel set to ");
    Serial.println(numSamples);
  }
  else if (cmd.equalsIgnoreCase("STRETCH")){
    if (stretch) {
      stretch = 0;
      Serial.println("Disabled image stretch");
    }
    else {
      stretch = 1;
      Serial.println("Enabled image stretch");
    }
    if (zoom) { displayScale(); }
    else { displayPhoto(); }
  }
  else if (cmd.substring(0, 6).equalsIgnoreCase("TIMER ")) {
    timer = cmd.substring(6).toInt();
    if (timer <= 20000) {
      Serial.print("Timer set to ");
      Serial.println(timer);
    }
    else {
      timer = 0;
      Serial.println("Timer too long dummy");
    }
  }
  else if (cmd.substring(0, 11).equalsIgnoreCase("MULTIPLIER ")) {
    multiplier = cmd.substring(11).toInt();
    Serial.print("Multiplier set to ");
    Serial.println(multiplier);
  }
  else if (cmd.substring(0, 5).equalsIgnoreCase("BIAS ")) {
    int biasSamps = 1;
    if (cmd.substring(5).toInt() < 1) {
      bias = 0;
      Serial.println("Bias set to 0");
    }
    else {
      biasSamps = cmd.substring(5).toInt();
        int adcValue = 0;
      for (int i=0; i<biasSamps; i++) {
        adcValue += readADC_fast();
      }
      bias = adcValue/biasSamps+1;
      Serial.print("Bias captured! Set to: ");
      Serial.println(bias);
    }
    
  }
  else {
    Serial.println("Didn't catch that mate");
  }
}

