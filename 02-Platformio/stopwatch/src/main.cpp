#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int INTERRUPT_PIN = 4;

static int seconds = 0;
static int minutes = 0;
static int hours = 0;

// declarations
void myISR();
void setup();
void printdi(String message);
void update_time();
void print_and_increment_time();

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.setTextSize(2);
  display.setTextColor(WHITE);

  pinMode(INTERRUPT_PIN, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), myISR, RISING);
}

void loop()
{
  print_and_increment_time();
  update_time();
  delay(1000);
}

void update_time()
{
  if (seconds == 60)
  {
    seconds = 0;
    minutes++;
    if (minutes == 60)
    {
      minutes = 0;
      hours++;
    }
  }
}

void printdi(String message)
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(message);
  display.display();
}

void print_and_increment_time()
{
  String message = "";
  if (hours < 10)
  {
    message += "0";
  }
  message += hours;
  message += ":";
  if (minutes < 10)
  {
    message += "0";
  }
  message += minutes;
  message += ":";
  if (seconds < 10)
  {
    message += "0";
  }
  message += seconds;
  printdi(message);
  seconds++;
}

void myISR()
{
  seconds = 0;
  minutes = 0;
  hours = 0;
  print_and_increment_time();
}