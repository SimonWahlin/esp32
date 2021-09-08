#include "StatusLed.h"
using Arduino_h::digitalWrite;
using INC_TASK_H::xTaskCreate;

StatusLed::StatusLed()
    : name("StatusLED")
{
}
StatusLed::StatusLed(const char *name)
    : name(name)
{
}
StatusLed::StatusLed(const char *name, StatusLedConfig configuration)
    : name(name), configuration(configuration)
{
}

void StatusLed::toggleLED(void *parameter)
{
    for (;;)
    { // infinite loop
        StatusLedConfig statusLedConfig = *(StatusLedConfig *)parameter;

        if (statusLedConfig.blinkCount == 0)
        {
            // if blinkCount is 0, turn on LED and wait 500ms for next instruction
            digitalWrite(statusLedConfig.blinkPin, HIGH);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        else if (statusLedConfig.blinkCount == -1)
        {
            // if blinkCount is 0, turn off LED and wait 500ms for next instruction
            digitalWrite(statusLedConfig.blinkPin, LOW);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        else if (statusLedConfig.blinkCount > 0)
        {
            // Turn the LED off
            digitalWrite(statusLedConfig.blinkPin, LOW);

            // Pause the task for blinkTimeLow milliseconds
            vTaskDelay(statusLedConfig.blinkTimeLow / portTICK_PERIOD_MS);

            // loop over blinkCount
            for (int i = 0; i < statusLedConfig.blinkCount; i++)
            {
                // Turn the LED on
                digitalWrite(statusLedConfig.blinkPin, HIGH);

                // Pause the task for blinkTimeHigh milliseconds
                vTaskDelay(statusLedConfig.blinkTimeHigh / portTICK_PERIOD_MS);

                // Turn the LED off
                digitalWrite(statusLedConfig.blinkPin, LOW);

                // Pause the task for blinkTimeLow milliseconds
                vTaskDelay(statusLedConfig.blinkTimeLow / portTICK_PERIOD_MS);
            }
        }
        // Pause the task for blinkDelay milliseconds
        vTaskDelay(statusLedConfig.blinkPause / portTICK_PERIOD_MS);
    }
}

void StatusLed::Start()
{
    if (taskHandle == NULL)
    {
        xTaskCreate(
            StatusLed::toggleLED, // Function that should be called
            name,                 // Name of the task (for debugging)
            1024,                 // Stack size (words)
            &configuration,       // Parameter to pass
            1,                    // Task priority
            &taskHandle           // Task handle
        );
    }
    else
    {
        vTaskResume(taskHandle);
    }
}

void StatusLed::Stop()
{
    if (taskHandle != NULL)
    {
        vTaskSuspend(taskHandle);
    }
}

void StatusLed::Remove()
{
    if (taskHandle != NULL)
    {
        vTaskDelete(taskHandle);
    }
}

void StatusLed::PrintConfig()
{
    Serial.println();
    Serial.println(name);
    Serial.println(configuration.blinkPin);
    Serial.println(configuration.blinkCount);
    Serial.println(configuration.blinkTimeHigh);
    Serial.println(configuration.blinkTimeLow);
    Serial.println(configuration.blinkPause);
}