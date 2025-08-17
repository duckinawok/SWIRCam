// ---------------------------------------------------
// -------------------SETUP---------------------------
// ---------------------------------------------------

void setup() {
  Serial.begin(115200);
  ledcSetup(LEDC_CHANNEL, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
  ledcAttachPin(LED_PIN, LEDC_CHANNEL);
  ledcWrite(LEDC_CHANNEL, 96);  // 50% brightness

  // startup screen and fill with red
  Serial.println("Configuring screen");
  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(tft.Color565(255, 0, 0));
  Serial.println("Screen configured");

  // setup switches
  pinMode(CAL_BUTTON, INPUT_PULLDOWN);
  pinMode(PHOTO_BUTTON, INPUT_PULLDOWN);
  pinMode(SWITCH_XY, INPUT_PULLDOWN);

  // setup x and y steppers
  pinMode(STEP_X, OUTPUT);
  pinMode(DIR_X, OUTPUT);
  digitalWrite(STEP_X, LOW);
  pinMode(STEP_Y, OUTPUT);
  pinMode(DIR_Y, OUTPUT);
  digitalWrite(STEP_Y, LOW);

  // setup enable xy
  pinMode(ENABLE_XY, OUTPUT);
  digitalWrite(ENABLE_XY, HIGH);

  // pinMode(analogPin, INPUT);
  // analogReadResolution(8);

  // configure SD card reader
  SPI.begin(SD_CLK, SD_MISO, SD_MOSI, SD_CS);
  if (!SD.begin(SD_CS, SPI)) {
    Serial.println("❌ SD card initialization failed!");
    return;
  }
  Serial.println("✅ SD card initialized.");
  
  // configure adc
  pinMode(ADC_CS, OUTPUT);
  digitalWrite(ADC_CS, HIGH);  // idle high
  adcSPI->begin(ADC_CLK, ADC_MISO, -1, ADC_CS);  // SCLK, MISO, MOSI, CS (MOSI unused) new: SCLK 0, MISO 4
  adcSPI->beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));  // 20 MHz SPI

  /* 
  if (!adc.begin(14)) {  // GPIO 14 is CS
    Serial.println("MCP3008 not found. Check wiring.");
    while (1);
  }
  */

  // fill with yellow when done
  tft.fillScreen(tft.Color565(255, 255, 0));
}

