/*
    Creator: oasdflkjo
    Date: 27.11.2021
*/

const int ledPin = 2;

void setup()
{
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
}

void loop()
{
    digitalWrite(ledPin, HIGH);
    Serial.print("Hello ");
    delay(1000);
    digitalWrite(ledPin, LOW);
    Serial.print("world!\n");
    delay(1000);
}