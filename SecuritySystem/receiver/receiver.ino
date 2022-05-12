#include <LiquidCrystal.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Pin definitions
int buttonPin = 4;
int buzzerPin = 6;

//Security system variables
boolean armed = false;
boolean buzzer = false;
boolean buttonPushed = false;
boolean lostConnection = true;

const uint64_t pipe = 0xE8E8F0F0E1LL; //Address of the radio

int messageCount = 0;
int lostConnectionCount = 0;

double packetLoss = 0; //Percent "lost connection" messages

boolean message[1]; //Holds the read radio message

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); //Creates the lcd object
RF24 radio(9, 10);

void updateLCD() //Updates the LCD every 0.5 seconds
{
    if (millis() % 500 < 50) //We use < 50 just in case this function isn't called when millis()%500 is 0
    {
        lcd.clear();
        lcd.print("Status: ");
        if (armed) //Armed/disarmed status
        {
            lcd.print("ARMED");
        }
        else
        {
            lcd.print("DISARMED");
        }
        lcd.setCursor(0, 1); //Line 2
        lcd.print("PIR: ");

        if (buzzer) //PIR Status
        {
            lcd.print("DETECTED");
        }
        else
        {
            if (packetLoss < 0.3)
            {
                lcd.print("CLEAR");
            }
            else
            {
                lcd.print("NO SIGNAL");
            }
        }
    }
}

void setup()
{
    Serial.begin(9600);
    radio.begin();
    radio.openReadingPipe(1, pipe);
    radio.startListening();

    lcd.begin(16, 2);
    lcd.clear();

    pinMode(buzzerPin, OUTPUT);
    pinMode(buttonPin, INPUT);
}

void loop()
{
    if (digitalRead(buttonPin) && !buttonPushed) //If the button is pushed
    {
        buttonPushed = true; //This is used so the "ready" state is only toggled once while the button is on
        buzzer = false;      //Turn off buzzer if it is on
        armed = !armed;      //Toggles the "armed" state
    }
    else if (!digitalRead(buttonPin))
    {
        buttonPushed = false; //When the button is released, allow it to be pressed again
    }

    if (buzzer) //Turn on the buzzer
    {
        if (millis() % 1000 < 500) //Between 0-499 milliseconds
        {
            tone(buzzerPin, 880); //Plays an 'A'
        }
        else //Between 500-999 milliseconds
        {
            tone(buzzerPin, 659); //Plays an 'E'
        }
    }
    else
        noTone(buzzerPin); //Play no sound

    if (radio.available()) //Message recieved
    {
        radio.read(message, 1);
        if (message[0] && armed)
            buzzer = true;
        lostConnection = false;
    }
    else
    {
        lostConnection = true;
    }

    //Calculates the percentage of lost messages vs messages
    packetLoss = lostConnectionCount / (double)(messageCount + lostConnectionCount);

    if (lostConnection)
    {
        lostConnectionCount++;
    }
    else
    {
        messageCount++;
    }

    if ((lostConnectionCount + messageCount) > 100) //Resets the messages counter once enough have been recieved
    {
        lostConnectionCount = 0;
        messageCount = 0;
    }

    updateLCD();
    delay(30); //Gives a second for the radio to catch up
}