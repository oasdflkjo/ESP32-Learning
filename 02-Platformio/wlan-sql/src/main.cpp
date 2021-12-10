/*
    Creator: oasdflkjo
    Date: 10.12.2021
*/
#include <WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "secrets.h"

// LCD defines and init
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// why this?
byte mac_addr[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

// defines are only used because project is in github
IPAddress server_addr(IP_1, IP_2, IP_3, IP_4);

WiFiClient client;
MySQL_Connection conn((Client *)&client);

const char *ssid = WLAN_SSID;
const char *password = WLAN_PW;

char *sql_usr = SQL_USER;
char *sql_pw = SQL_PW;

void setup()
{
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.setTextSize(2);
  display.setTextColor(WHITE);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Connecting\nto\nWiFi");
    display.display();
    delay(500);
  }
  Serial.println(WiFi.localIP());
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Connected\nto\nWiFi");
    display.display();
    delay(500);
  }
  else
  {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("WiFi\nError");
    display.display();
    delay(500);
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("sending");
  conn.connect(server_addr, 3306, sql_usr, sql_pw);
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  cur_mem->execute("use sql11457449;");
  cur_mem->execute("INSERT INTO `my-iot-tempereture-storage` (`timestamp`, `temperature`) VALUES (NOW(), '123.4');");
  delete cur_mem;
  display.print("sent");
  delay(5000);
}