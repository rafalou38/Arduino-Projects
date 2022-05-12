#include <Wire.h>
#include "ds3231.h"
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#define LDR_PIN A3

Adafruit_7segment matrix = Adafruit_7segment();

const int BUFF_MAX = 128;
int convertedTimeHour = 0;

bool flagSetTimeMode = false;
bool timeSetFlag = false;

int setHour = 15;
int setMinute = 48;
int setSecond = 0;

int setDOW = 3;
int setDay = 30;
int setMonth = 3;
int setYear = 2022;

bool blinkColon = false;
int tcurrent = 0;
int timeHour = 0;
int timeMinute = 0;
int timeSecond = 0;

int brightness = 5;
#define BRIGHTNESS_MAX 30
#define BRIGHTNESS_MIN 1

char recv[BUFF_MAX];
unsigned long prev;
int interval = 1000;

void setup()
{
    Wire.begin();
    matrix.begin(0x70);
    DS3231_init(DS3231_INTCN);
    memset(recv, 0, BUFF_MAX);

    pinMode(LDR_PIN, INPUT);

    Serial.begin(9600);

    matrix.setBrightness(brightness);
    matrix.writeDisplay();
}

void loop()
{
    Serial.print("LDR: ");
    Serial.print(1024 - analogRead(LDR_PIN));
    Serial.print(" Brightness: ");
    Serial.println(brightness);

    while (flagSetTimeMode)
    {
        timeSetFlag = true;
        break;
    }

    if (timeSetFlag)
    {
        flagSetTimeMode = false;
        timeSetFlag = false;
        sendTime();
    }

    unsigned long now = millis();
    struct ts t;

    if ((now - prev > interval) && (Serial.available() <= 0))
    {
        DS3231_get(&t);
        prev = now;
    }

    timeHour = t.hour;
    timeMinute = t.min;
    timeSecond = t.sec;

    int currentTime = timeHour * 100 + timeMinute;

    matrix.print(currentTime);
    if (t.min < 10)
        matrix.writeDigitNum(3, 0);
    if (t.sec != tcurrent)
    {
        blinkColon = !blinkColon;
        tcurrent = t.sec;
    }

    matrix.drawColon(blinkColon);

    int new_brightness = map(
        min(max(1024 - analogRead(LDR_PIN), BRIGHTNESS_MIN), BRIGHTNESS_MAX),
        BRIGHTNESS_MIN, BRIGHTNESS_MAX, 0, 15);

    if (abs(new_brightness - brightness) > 2)
        brightness = new_brightness;

    matrix.setBrightness(brightness);

    matrix.writeDisplay();
}

void sendTime()
{
    struct ts t;
    t.sec = setSecond;
    t.min = setMinute;
    t.hour = setHour;
    t.wday = setDOW;
    t.mday = setDay;
    t.mon = setMonth;
    t.year = setYear;
    DS3231_set(t);
}