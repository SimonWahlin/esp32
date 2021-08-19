#include "StatusLed.h"
using Arduino_h::digitalWrite;
using INC_TASK_H::xTaskCreate;

StatusLed::StatusLed()
{
    StatusLedConfig configuration;
    const char *name = "StatusLED";
    StatusLed{name, &configuration};
}
StatusLed::StatusLed(const char *name)
{
    StatusLedConfig configuration;
    StatusLed{name, &configuration};
}
StatusLed::StatusLed(const char *name, StatusLedConfig *configuration)
    : name(name), configuration(configuration)
{
}

void StatusLed::toggleLED(void *parameter)
{
    // StatusLedConfig *configPtr = (StatusLedConfig *)parameter;
    // StatusLedConfig statusLedConfig;
    // statusLedConfig = *configPtr;
    for (;;)
    { // infinite loop
        StatusLedConfig statusLedConfig = *(StatusLedConfig *)parameter;
        Serial.println("Blinking");
        Serial.println(statusLedConfig.blinkPin);
        Serial.println(statusLedConfig.blinkCount);
        Serial.println(statusLedConfig.blinkTimeHigh);
        Serial.println(statusLedConfig.blinkTimeLow);
        Serial.println(statusLedConfig.blinkPause);

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
        else
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
            StatusLed::name,      // Name of the task (for debugging)
            1024,                 // Stack size (words)
            configuration,        // Parameter to pass
            1,                    // Task priority
            &this->taskHandle     // Task handle
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
// #include <FreeRTOS.h>
// #include <Arduino.h>

// StatusLed
//     int pin
//     int blinkTimeHigh
//     int blinkDelayLow
//     int blinkCount
//     int blinkPause
//    void Start()
//    void Stop()

// class StatusLed
// {
// pivate:
//     TaskHandle_t statusLedHandle;
// public:
//     int blinkTimeHigh = 500;
//     int blinkDelayLow = 500;
//     int blinkCount = 1;
//     int blinkPause = 0;

//     StatusLed();

//     void Start();

//     void Stop();
// };

// void toggleLED(void *parameter)
// {
//     StatusLedConfig *statusLedConfig = (StatusLedConfig *)parameter;
//     for (;;)
//     { // infinite loop
//         if (statusLedConfig->blinkCount == 0 && statusLedConfig->activeHigh)
//         {
//             digitalWrite(statusLedConfig->pin, HIGH);
//         }
//         else if (statusLedConfig->blinkCount == 0 && !statusLedConfig->activeHigh)
//         {
//             digitalWrite(statusLedConfig->pin, LOW);
//         }
//         else
//         {
//             for (int i = 0; i < statusLedConfig->blinkCount; i++)
//             {
//                 // Turn the LED on
//                 digitalWrite(statusLedConfig->pin, HIGH);

//                 // Pause the task for blinkInterval milliseconds
//                 vTaskDelay(statusLedConfig->blinkInterval / portTICK_PERIOD_MS);

//                 // Turn the LED off
//                 digitalWrite(statusLedConfig->pin, LOW);

//                 // Pause the task for blinkInterval milliseconds
//                 vTaskDelay(statusLedConfig->blinkInterval / portTICK_PERIOD_MS);
//             }
//         }
//         // Pause the task for blinkDelay milliseconds
//         vTaskDelay(statusLedConfig->blinkDelay / portTICK_PERIOD_MS);
//     }
// }

// class StatusLED
// {
// private:
//     void toggleLED(void *parameter)
//     {
//         StatusLedConfig *statusLedConfig = (StatusLedConfig *)parameter;
//         for (;;)
//         { // infinite loop
//             if (statusLedConfig->blinkCount == 0 && statusLedConfig->activeHigh)
//             {
//                 digitalWrite(statusLedConfig->pin, HIGH);
//             }
//             else if (statusLedConfig->blinkCount == 0 && !statusLedConfig->activeHigh)
//             {
//                 digitalWrite(statusLedConfig->pin, LOW);
//             }
//             else
//             {
//                 for (int i = 0; i < statusLedConfig->blinkCount; i++)
//                 {
//                     // Turn the LED on
//                     digitalWrite(statusLedConfig->pin, HIGH);

//                     // Pause the task for blinkInterval milliseconds
//                     vTaskDelay(statusLedConfig->blinkInterval / portTICK_PERIOD_MS);

//                     // Turn the LED off
//                     digitalWrite(statusLedConfig->pin, LOW);

//                     // Pause the task for blinkInterval milliseconds
//                     vTaskDelay(statusLedConfig->blinkInterval / portTICK_PERIOD_MS);
//                 }
//             }
//             // Pause the task for blinkDelay milliseconds
//             vTaskDelay(statusLedConfig->blinkDelay / portTICK_PERIOD_MS);
//         }
//     }

// public:
//     StatusLedConfig config;

//     void Start(){

//     };

//     StatusLED(StatusLedConfig statusLedConfig)
//     {
//         config = statusLedConfig;
//     }

//     ~StatusLED()
//     {
//     }
// };