
#include <Arduino.h>

/**
 * @brief This simulates a heart beat (LUB AND DUB)
 * @param bpm - Beats per minute
 * @param lub - Function to be called when LUB is happening
 * @param afterLub - Function to be called after LUB is done
 * @param dub - Function to be called when DUB is happening
 * @param afterDub - Function to be called after DUB is done
 */
void cardiacCycle(const int bpm, void (*lub)(), void (*afterLub)(), void (*dub)(), void (*afterDub)())
{
    // Calculate duration of RR interval in milliseconds
    float rr_interval_duration = 60000.0 / bpm;
    // Calculate duration of pause between systole in milliseconds
    float pause_between_systole = (0.35 * 1000) / 2;
    // Calculate duration of pause between full cycles in milliseconds
    float pause_duration_between_full_cycle = rr_interval_duration - (pause_between_systole * 2);

    static unsigned long previousMillis = 0;
    static int state = 0;

    unsigned long currentMillis = millis();

    // State machine to control the cardiac cycle
    // This is to avoid using delay() function
    switch (state)
    {
    case 0: // Lub
        if (currentMillis - previousMillis >= pause_between_systole)
        {
            lub();
            state = 1;
            previousMillis = currentMillis;
        }
        break;
    case 1: // After Lub
        if (currentMillis - previousMillis >= pause_between_systole)
        {
            afterLub();
            state = 2;
            previousMillis = currentMillis;
        }
        break;
    case 2: // Dub
        if (currentMillis - previousMillis >= pause_duration_between_full_cycle)
        {
            dub();
            state = 3;
            previousMillis = currentMillis;
        }
        break;
    case 3: // After Dub
        if (currentMillis - previousMillis >= pause_between_systole)
        {
            afterDub();
            state = 0;
            previousMillis = currentMillis;
        }
        break;
    }
}