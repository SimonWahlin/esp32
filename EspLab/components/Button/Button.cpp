#include <functional>
#include "Button.h"
using Arduino_h::digitalRead;
using INC_TASK_H::xTaskCreate;

Button::Button(const char* name, int buttonPin)
    : name(name)
{
    configuration.buttonPin = buttonPin;
    initialize();
}
Button::Button(const char* name, int buttonPin, int responseTime)
    : name(name)
{
    configuration.buttonPin = buttonPin;
    configuration.responseTime = responseTime;
    initialize();
}
void Button::buttonEventTask(void *parameter)
{
    ButtonConfig *buttonConfig = (ButtonConfig *)parameter;
    for (;;)
    {
        buttonConfig->buttonState <<= 1;
        buttonConfig->buttonState.set(0, digitalRead(buttonConfig->buttonPin));
        if(buttonConfig->isPressed == false && buttonConfig->buttonState.to_ulong() == buttonConfig->pressedState.to_ullong()) 
        {
            xQueueSend(buttonConfig->queueHandle, &buttonConfig->pressed, portMAX_DELAY);
            Serial.println("Button pressed!");
            buttonConfig->isPressed = true;
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        else if (buttonConfig->isPressed == true && buttonConfig->buttonState.to_ulong() == buttonConfig->releasedState.to_ulong()) {
            xQueueSend(buttonConfig->queueHandle, &buttonConfig->released, portMAX_DELAY);
            Serial.println("Button released!");
            buttonConfig->isPressed = false;
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

        vTaskDelay(buttonConfig->responseTime / 9 / portTICK_PERIOD_MS);
    }
}

void Button::Start()
{
    if (taskHandle == NULL)
    {
        xTaskCreate(
            Button::buttonEventTask, // Function that should be called
            name,                    // Name of the task (for debugging)
            1024,                    // Stack size (words)
            &configuration,          // Parameter to pass
            1,                       // Task priority
            &taskHandle              // Task handle
        );
    }
    else
    {
        vTaskResume(taskHandle);
    }
}

void Button::Stop()
{
    if (taskHandle != NULL)
    {
        vTaskSuspend(taskHandle);
    }
}

void Button::Remove()
{
    if (taskHandle != NULL)
    {
        vTaskDelete(taskHandle);
    }
}

void Button::initialize() 
{
    pinMode(configuration.buttonPin, INPUT_PULLDOWN);
    queue = xQueueCreate( 10, sizeof( int ) );
    configuration.queueHandle = queue;
}