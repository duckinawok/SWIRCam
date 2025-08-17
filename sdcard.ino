//----------------------------------------------------
//-----------------------SD CARD----------------------
//----------------------------------------------------

void savePhoto() {
  Serial.println("SAVING IMAGE TO SD CARD");
  String filename = getNextFilename();
  if (filename.length() > 0) {
    savePGM(filename.c_str());
  } else {
    Serial.println("Could not find free filename");
  }
}

void savePGM(const char* filename) {
  File file = SD.open(filename, FILE_WRITE);
  if (!file) {
    Serial.println("❌ Failed to open file for writing.");
    return;
  }

  // Write the binary PGM header
  file.print("P5\n");
  file.print(String(WIDTH) + " " + String(HEIGHT) + "\n");
  file.print("255\n");

  // Write image data row by row
  for (int y = 0; y < HEIGHT; y++) {
    file.write(image[y], WIDTH);  // Write one row (240 bytes)
  }

  file.close();
  Serial.println(String("✅ Image saved as") + filename);
}

String getNextFilename() {
  int index = 1;
  String filename;

  while (true) {
    filename = "/image" + String(index) + ".pgm";
    if (!SD.exists(filename)) {
      return filename;
    }
    index++;
    if (index > 9999) {  // safety stop to prevent infinite loop
      Serial.println("⚠️ Too many images, can't find free filename!");
      return "";
    }
  }
}

