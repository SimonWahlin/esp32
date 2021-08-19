#include <Arduino.h>
#include "StatusLed.h"

const int statusLedPin = 17;   // Pin of the LED
const int resetButtonPin = 16; // Pin of the reset button

StatusLedConfig blueLedConfig;

void setup()
{
  Serial.begin(115200);
  pinMode(statusLedPin, OUTPUT);
  pinMode(resetButtonPin, INPUT_PULLDOWN);
  
  // Set up default config for the blue LED
  blueLedConfig.blinkPin = statusLedPin;
  blueLedConfig.blinkCount = 0;
  blueLedConfig.blinkTimeHigh = 300;
  blueLedConfig.blinkTimeLow = 300;
  blueLedConfig.blinkPause = 1000;

  StatusLed blueLed("blueLED", &blueLedConfig);
  blueLed.Start();
  delay(2000);
  Serial.println("BlinkCount is 10");
  blueLed.configuration->blinkCount = 10;
  delay(3000);
  Serial.println("BlinkCount is -1");
  blueLed.configuration->blinkCount = -1;
  delay(10000);
  Serial.println("Stopped");
  blueLed.Stop();
  delay(5000);
  blueLed.Remove();
  delay(5000);
}

void loop()
{
  // digitalWrite(statusLed, HIGH);
  // delay(1000);
  // digitalWrite(statusLed, LOW);
  // delay(1000);
  // static bool reset = false;
  // Serial.println(digitalRead(resetButton));
  // delay(100);
  // ToDo: Better debounce
  // if(digitalRead(resetButton) == HIGH)
  // {
  //   delay(100);
  //   if(digitalRead(resetButton) == HIGH)
  //   {
  //     Serial.println("Reset button held down");
  //     delay(3000);
  //     if(digitalRead(resetButton) == HIGH) {
  //       reset = true;
  //     }
  //   }
  // }
  // put your main code here, to run repeatedly:
}