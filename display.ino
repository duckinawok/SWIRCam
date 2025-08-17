//----------------------------------------------------
//----------------------DISPLAY-----------------------
//----------------------------------------------------

void displayPhoto(){
  int pixel = 0;
  int scaleVal = 255/maxVal;
  Serial.println("Downsampling (2x2 averaging)");  // 120x120 result

  for (int y = 0; y < HEIGHT; y += 2) {
    for (int x = 0; x < WIDTH; x += 2) {
      // Average the 2x2 block
      uint16_t sum = image[y][x]
                   + image[y][x + 1]
                   + image[y + 1][x]
                   + image[y + 1][x + 1];
      image_downsampled[y / 2][x / 2] = sum / 4;
    }
  }

  Serial.println("Displaying Photo");
  for (int i = 0; i < 120; i++){
    for (int j = 0; j < 120; j++){
      if (stretch == 0) {
        pixel = image_downsampled[i][j];
      }
      else {
        pixel = (image_downsampled[i][j])*scaleVal;
      }
      tft.fillRect(119-i+4, j+4, 1, 1, tft.Color565(pixel, pixel, pixel));
    }
  }
}

void displayScale (){
  int pixel = 0;
  int scaleVal = 255/maxVal;
  Serial.println("Displaying 1:1 scale crop");

  for (int i=0; i<120; i++){
    for (int j=0; j<120; j++) {
      if (stretch == 0) {
        pixel = image[i+60][j+60];
      }
      else {
        pixel = (image[i+60][j+60]) * scaleVal;
      }
      tft.fillRect(119-i+4, j+4, 1, 1, tft.Color565(pixel, pixel, pixel));
    }
  }

}

