// Creation Crate Month 16: Alarm Clock

// Import libraries
#include <DS1302RTC.h>
#include <TimeLib.h>
#include <SevSeg.h>
#include <Time.h>

// Define pins
#define BUZZER_PIN A0
#define LED_PIN A4
#define BUTTON_PIN A5

// Clock settings
String alarm = "12:09";        // Time alarm will sound (must be in 24 hour time format)
boolean use12HourTime = false; // Set to "false" to display the time in 24 hour time format

// Initialize 7 segment display and RTC
SevSeg sevseg;
DS1302RTC rtc(A1, A2, A3);

// Alarm clock variables
boolean alarmSet = false;
boolean alarmActive = false;
boolean buttonPressed = false;
long alarmStartTime = 0;
String serialInput;

char timeBuffer[5];

// Returns true if the given string is a valid time (format: "hh:mm")
boolean isValidTimeString(String timeString)
{
    int numberOfColons = 0;
    for (int i = 0; i < timeString.length(); i++)
    {
        if (timeString.charAt(i) == ':')
            numberOfColons++;

        if (timeString.charAt(i) != ':' && !isDigit(timeString.charAt(i)))
            return false;
    }

    if (numberOfColons != 1 || getHour(timeString) < 0 ||
        getHour(timeString) > 23 || getMinute(timeString) < 0 ||
        getMinute(timeString) > 60)
        return false;
    else
        return true;
}

// Returns the hour value given a time string (format: "hh:mm")
int getHour(String timeString)
{
    return timeString.substring(0, timeString.indexOf(":"))
        .toInt();
}

// Returns the minute value given a time string (format: "hh:mm")
int getMinute(String timeString)
{
    return timeString.substring(timeString.indexOf(":") +
                                1)
        .toInt();
}

void setup()
{
    // Set pin modes
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);

    // Initialize Serial communications
    Serial.begin(9600);

    // Configure the 7 segment display
    byte numDigits = 4;
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, false);

    // Configure the Time library to retrieve the time from the RTC
    setSyncProvider(rtc.get);
    // setTime(11, 42, 10, 1, 2, 2021);
    // rtc.set(now());
}
// void loop()
// {
//     sevseg.setChars("1234");
//     // sevseg.setNumber(1234);
//     sevseg.refreshDisplay();
// }
void loop()
{

    //"snprintf" stores a time string such that the minute always has 2 digits and the hour has 1-2 digits
    if (use12HourTime)
        snprintf(timeBuffer, sizeof(timeBuffer), "%2d%02d", hourFormat12(), minute()); // Uses 12 hour time format if use12HourTime is true
    else
        snprintf(timeBuffer, sizeof(timeBuffer), "%2d%02d", hour(), minute());

    // Update the 7 segment display
    sevseg.setChars(timeBuffer);
    sevseg.refreshDisplay();

    // Show the state of "alarmSet" on the LED
    digitalWrite(LED_PIN, alarmSet);

    // Make the button toggle the state of the LED, but only once per each press
    if (digitalRead(BUTTON_PIN) && !buttonPressed)
    {
        buttonPressed = true;
        alarmSet = !alarmSet;
        alarmActive = false;
    }

    // Once the button is released, buttonPressed is set to false allowing the button to be pressed again
    //(Without this, holding the button down will continue to toggle the alarmSet status)
    if (!digitalRead(BUTTON_PIN))
    {
        buttonPressed = false;
    }

    // Activate the alarm if alarmSet is true, the alarm is not currently    active, and the time is the alarm time
    if (alarmSet && !alarmActive && second() == 0 && minute() == getMinute(alarm) && hour() == getHour(alarm))
    {
        alarmActive = true;
        alarmStartTime = millis(); // Start the alarm elapsed time timer
    }

    // Activate the buzzer if alarmActive is true
    if (alarmActive)
    {
        int elapsedTime = (millis() - alarmStartTime) % 1000; // elapsedTime ranges from 0-999, allows for a 1 second long beep pattern

        if (elapsedTime < 150) // Buzzer on for 0-149ms
            digitalWrite(BUZZER_PIN, HIGH);
        else if (elapsedTime < 300) // Buzzer off for 150-299ms
            digitalWrite(BUZZER_PIN, LOW);
        else if (elapsedTime < 450) // Buzzer on for 300-449ms
            digitalWrite(BUZZER_PIN, HIGH);
        else // Buzzer off for 450-999ms
            digitalWrite(BUZZER_PIN, LOW);
    }
    else
    {
        digitalWrite(BUZZER_PIN, LOW); // Turn buzzer off if alarmActive is false
    }

    if (Serial.available()) // If Serial message is sent to the Uno R3
    {
        serialInput = Serial.readString();  // Store the input in serialInput
        if (isValidTimeString(serialInput)) // Check the string is a valid time string
        {
            Serial.println("Set time to " + serialInput);
            // setTime(hour, minute, second, month, day, year)
            setTime(getHour(serialInput), getMinute(serialInput), 0, 1, 1, 2017); // Sets time to the time string, 0sec, 1/1/2017
            rtc.set(now());                                                       // Update the RTC to the new time
        }
        else
        {
            Serial.println("Error - invalid time: " + serialInput);
        }
    }
}