#include <Arduino.h>
#include "StatusLed.h"
#include "Button.h"

#define statusLEDPin 17  // Pin of the LED
#define resetButtonPin 5 // Pin of the reset button

// const int statusLedPin = 17;  // Pin of the LED
// const int resetButtonPin = 5; // Pin of the reset button

StatusLedConfig blueLedConfig;
StatusLed blueLed("blueLED", blueLedConfig);

Button myButton("MyButton", resetButtonPin, 100);

void setup()
{
  Serial.begin(115200);
  pinMode(statusLEDPin, OUTPUT); // TODO: move to class init method
  blueLed.PrintConfig();

  // Set up default config for the blue LED
  blueLed.configuration.blinkPin = statusLEDPin;
  blueLed.configuration.blinkCount = 0;
  blueLed.configuration.blinkTimeHigh = 300;
  blueLed.configuration.blinkTimeLow = 300;
  blueLed.configuration.blinkPause = 1000;

  blueLed.PrintConfig();
  blueLed.Start();

  myButton.Start();

  delay(2000);
  Serial.println("BlinkCount is 10");
  blueLed.configuration.blinkCount = 10;
  delay(3000);
  Serial.println("BlinkCount is -1");
  blueLed.configuration.blinkCount = -1;
  delay(10000);
  Serial.println("Stopped");
  blueLed.Stop();
  delay(5000);
  blueLed.Remove();
  delay(5000);
}

void loop()
{
  
}