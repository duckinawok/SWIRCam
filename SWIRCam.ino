// SWIR Scanning Camera Code
// Organised from working code from 15-08-2025

#include <TFT_ILI9163C.h>
#include <SPI.h>
#include <SD.h>
#include "driver/gpio.h"
// #include <Adafruit_MCP3008.h>

// SD card SPI pin assignments
#define SD_CS   26
#define SD_CLK  18
#define SD_MOSI 23
#define SD_MISO 19

// LCD SPI pin assignments
#define LCD_CS   5
#define LCD_DC   27
#define LCD_RST  26
#define LEDC_CHANNEL     0       // PWM channel 0
#define LEDC_TIMER_BIT   8       // 8-bit resolution (0-255)
#define LEDC_BASE_FREQ   5000    // 5 kHz PWM frequency
#define LED_PIN          2       // GPIO2 for LED

// ADC SPI pins and fast CS pin writes
#define ADC_CS 14
#define ADC_CLK 0
#define ADC_MISO 4
#define ADC_LOW()   REG_WRITE(GPIO_OUT_W1TC_REG, (1 << ADC_CS))
#define ADC_HIGH()  REG_WRITE(GPIO_OUT_W1TS_REG, (1 << ADC_CS))

// Stepper motor pins
#define STEP_X 22
#define STEP_Y 25
#define CAL_BUTTON 17
#define PHOTO_BUTTON 16
#define SWITCH_XY 15
#define DIR_X 21
#define DIR_Y 33
#define ENABLE_XY 32

// Create up tft and adc objects
TFT_ILI9163C tft = TFT_ILI9163C(LCD_CS, LCD_DC, -1);
SPIClass *adcSPI = new SPIClass(HSPI);
// Adafruit_MCP3008 adc;

// captured image and downsampled display image
#define WIDTH 240
#define HEIGHT 240
uint8_t image[HEIGHT][WIDTH];
uint8_t image_downsampled[HEIGHT / 2][WIDTH / 2];

//MS2,MS1:
//00: 1/8
//01: 1/32
//10: 1/64
//11: 1/16

