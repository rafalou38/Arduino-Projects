#include <SevSeg.h>

SevSeg sevseg;

void setup()
{
    // Initialize Serial communications
    Serial.begin(9600);

    pinMode(A0, INPUT);

    // Configure the 7 segment display
    byte numDigits = 4;
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, false);
}
void loop()
{
    sevseg.setChars("LETI");
    // sevseg.setNumber(1234);
    sevseg.refreshDisplay();

    delay(map(analogRead(A0), 0, 1023, 0, 500));
}
