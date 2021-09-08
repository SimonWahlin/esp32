#pragma once

#include <bitset>
#include <FreeRTOS.h>
#include <Arduino.h>

struct ButtonConfig
{
    std::bitset<10> buttonState = 0b1111111111;;
    const std::bitset<10> pressedState = 0b1000000000;
    const std::bitset<10> releasedState = 0b0111111111;
    
    QueueHandle_t queueHandle;
    const int pressed = 1;
    const int released = 0;
    
    bool isPressed = false;
    int buttonPin = 0;
    int responseTime = 271;
};

class Button
{
private:
    TaskHandle_t taskHandle;
    static void buttonEventTask(void *parameter);
    void initialize();

public:
    const char* name;
    ButtonConfig configuration;
    QueueHandle_t queue;
    Button(const char* name, int buttonPin);
    Button(const char* name, int buttonPin, int responseTime);

    void Start();

    void Stop();

    void Remove();
};