#include <LiquidCrystal.h>
#include <Wire.h>
#include <TEA5767N.h>
#include <encoder.h>

const int
    rs = 11,
    en = 12,
    d4 = 4,
    d5 = 5,
    d6 = 6,
    d7 = 7;

#define BTN_NEXT 2
#define BTN_PREV 3
#define BTN_ROUND 10
#define DELAY 5000

byte btn_next = 0;
byte btn_prev = 0;
unsigned long last_pressed = 0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
TEA5767N radio = TEA5767N();
encoder enc(8, 9);

float targetFreq = (88.0);

void setup()
{

    Serial.begin(115200);
    Wire.begin();
    lcd.begin(16, 2);

    pinMode(A2, OUTPUT);
    pinMode(BTN_ROUND, INPUT_PULLUP);

    // radio.setStereoNoiseCancellingOn();

    // Limit the amount of noise energy.
    radio.setSoftMuteOn();
    // Cut high frequencies from the audio signal.
    radio.setHighCutControlOn();

    // radio.startsSearchFromBeginning();
}

unsigned long last_loop = 0;

void rightCb()
{
    // last_loop = 0;
    targetFreq += 0.1;
    showScreen(false);
    last_loop = millis() - DELAY / 2;
}
void leftCb()
{
    // last_loop = 0;
    targetFreq -= 0.1;
    showScreen(false);
    last_loop = millis() - DELAY / 2;
}

void showScreen(bool trueFreq)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Frequency: ");
    if (trueFreq)
    {
        lcd.print(radio.readFrequencyInMHz());
        lcd.setCursor(0, 1);
        lcd.print("signal: ");
        lcd.print(radio.getSignalLevel());
    }
    else
    {
        lcd.print(targetFreq);
    }
}

void loop()
{
    enc.check(rightCb, leftCb);
    // Serial.print(">target:");
    // Serial.println(targetFreq);

    if (millis() - last_loop > DELAY)
    {
        if (targetFreq != radio.readFrequencyInMHz())
        {
            // Serial.println("set");
            // Serial.print(">target:");
            // Serial.println(targetFreq);

            radio.selectFrequency(targetFreq);
            targetFreq = radio.readFrequencyInMHz();
        }

        last_loop = millis();

        showScreen(true);
    }

    checkButtons();

    if (btn_next == 2)
    {
        last_loop = millis();
        radio.setSearchUp();
        radio.searchNext();
        last_loop = 0;
        targetFreq = radio.readFrequencyInMHz();
    }

    if (btn_prev == 2)
    {
        last_loop = millis();
        radio.setSearchDown();
        radio.searchNext();
        last_loop = 0;
        targetFreq = radio.readFrequencyInMHz();
    }

    if (digitalRead(BTN_ROUND) == HIGH)
    {
        Serial.print("before");
        Serial.println(targetFreq);

        targetFreq = ceil(targetFreq * 10) / 10;

        Serial.print("after");
        Serial.println(targetFreq);

        // showScreen(true);
        // delay(500);
        last_loop = 0;
    }

    // delay(10000);
}

void checkButtons()
{
    if (digitalRead(BTN_NEXT) and (millis() - last_pressed) > 500)
    {
        btn_next = 1;
    }
    else
    {
        if (btn_next == 1)
        {
            last_pressed = millis();
            btn_next = 2;
        }
        else
        {
            btn_next = 0;
        }
    }

    if (digitalRead(BTN_PREV) and (millis() - last_pressed) > 500)
    {
        btn_prev = 1;
    }
    else
    {
        if (btn_prev == 1)
        {
            last_pressed = millis();
            btn_prev = 2;
        }
        else
        {
            btn_prev = 0;
        }
    }
}