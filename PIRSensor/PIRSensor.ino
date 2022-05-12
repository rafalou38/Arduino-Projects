#define INFRAREDPIN 0
#define READYLED 3
#define BUTTONPIN 4
#define ARMEDLED 5
#define BUZZERPIN 6

long readyTime = 0;
bool readyToArm = false;
bool armed = false;
bool buzzer = false;
bool buttonPushed = false;

void setup()
{
    Serial.begin(9600);
    Serial.println("===================\n== START PROGRAM ==");
    attachInterrupt(INFRAREDPIN, detection, RISING);

    pinMode(READYLED, OUTPUT);
    pinMode(BUTTONPIN, OUTPUT);
    pinMode(ARMEDLED, INPUT);
    pinMode(BUZZERPIN, OUTPUT);
}

void detection()
{
    Serial.println("WARNING! Movememetn DETECTED");
    if (armed)
    {
        buzzer = 1;
    }
}

void loop()
{
    if (digitalRead(BUTTONPIN) && !buttonPushed)
    {
        buttonPushed = 1;
        buzzer = 0;
        armed = 0;
        readyToArm = !readyToArm;
        readyTime = millis();
    }
    else if (!digitalRead(BUTTONPIN))
    {
        buttonPushed = 0;
    }

    if (readyToArm)
    {
        digitalWrite(READYLED, HIGH);
        if (millis() >= (readyTime + 5000))
        {
            armed = 1;
        }
    }
    else
    {
        digitalWrite(READYLED, LOW);
        armed = 0;
    }

    if (armed)
    {
        digitalWrite(ARMEDLED, HIGH);
    }
    else
    {
        digitalWrite(ARMEDLED, LOW);
    }

    if (buzzer)
    {
        if (millis() % 1000 < 500)
        {
            tone(BUZZERPIN, 880);
        }
        else
        {
            tone(BUZZERPIN, 659);
        }
    }
    else
    {
        noTone(BUZZERPIN);
    }
}