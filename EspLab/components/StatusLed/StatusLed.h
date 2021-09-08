#include <FreeRTOS.h>
#include <Arduino.h>

struct StatusLedConfig
{
    int blinkPin      = 2;
    int blinkTimeHigh = 500;
    int blinkTimeLow  = 500;
    int blinkCount    = 1;
    int blinkPause    = 0;
};

class StatusLed
{
private:
    TaskHandle_t taskHandle;
    static void toggleLED(void *parameter);
public:
    const char* name;
    StatusLedConfig configuration;

    StatusLed();
    StatusLed(const char* name);
    StatusLed(const char* name, StatusLedConfig configuration);

    void Start();

    void Stop();

    void Remove();

    void PrintConfig();
};
