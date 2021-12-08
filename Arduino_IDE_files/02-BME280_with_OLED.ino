/*
    Creator: oasdflkjo
    Date: 8.12.2021
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>

// LCD defines and init
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// BMP280 defines and what ever bmp is called in this context. ??object??
#define BMP_ADDRESS 0x76
#define BMP_CHIPID 0x58
Adafruit_BMP280 bmp;

// display buffer
char display_buffer[8];

void setup()
{
    // no error handling for now
    bmp.begin(BMP_ADDRESS, BMP_CHIPID);
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

    // settings from datasheet
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                    Adafruit_BMP280::SAMPLING_X2,
                    Adafruit_BMP280::SAMPLING_X16,
                    Adafruit_BMP280::FILTER_X16,
                    Adafruit_BMP280::STANDBY_MS_500);

    // display init
    display.display();
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
}

void loop()
{
    display.clearDisplay();
    display.setCursor(0, 0);
    // there might be a better way to do this
    // display accidentally centered text when dtostrf
    // length was 6 so i kept it
    dtostrf(bmp.readTemperature(), 6, 2, display_buffer);
    display.print(display_buffer);
    display.display();
    delay(2000);
}