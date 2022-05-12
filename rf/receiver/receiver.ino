#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"
RF24 radio(7, 8); // CE, CSN

#define tunnel1 "PIPE1" // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre
#define tunnel2 "PIPE2"
#define tunnel3 "PIPE3"
#define tunnel4 "PIPE4"
#define tunnel5 "PIPE5"
#define tunnel6 "PIPE6"

const byte adresses[][6] = {tunnel1, tunnel2, tunnel3, tunnel4, tunnel5, tunnel6}; // Tableau contenant les adresses de tunnel, au format "byte array"

boolean button_state = 0;
int led_pin = 3;
void setup()
{
    pinMode(6, OUTPUT);
    Serial.begin(9600);
    printf_begin();
    Serial.println("Starting");
    if (!radio.begin())
    {
        Serial.println(F("radio hardware not responding!"));
        while (1)
        {
        }
    }
    radio.setChannel(5);
    radio.setPALevel(RF24_PA_MIN); //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
    radio.setDataRate(RF24_250KBPS);

    radio.openReadingPipe(1, adresses[1]); // Ouverture du "tunnel2" en LECTURE (réception radio)
    radio.openReadingPipe(2, adresses[2]); // Ouverture du "tunnel3" en LECTURE (réception radio)
    radio.openReadingPipe(3, adresses[3]); // Ouverture du "tunnel4" en LECTURE (réception radio)
    radio.openReadingPipe(4, adresses[4]); // Ouverture du "tunnel5" en LECTURE (réception radio)
    radio.openReadingPipe(5, adresses[5]); // Ouverture du "tunnel6" en LECTURE (réception radio)

    radio.startListening(); //This sets the module as receiver
    radio.printDetails();
    Serial.println("Started Listening");
}
void loop()
{
    if (radio.available()) //Looking for the data.
    {
        char text[32];                   //Saving the incoming data
        radio.read(&text, sizeof(text)); //Reading the data
        // radio.read(&button_state, sizeof(button_state)); //Reading the data
        Serial.print("Received: ");
        Serial.println(text);
        // if (button_state == HIGH)
        // {
        //     digitalWrite(6, HIGH);
        //     Serial.println(text);
        // }
        // else
        // {
        //     digitalWrite(6, LOW);
        //     Serial.println(text);
        // }
    }
    else
    {
        // Serial.println("No Data");
    }

    delay(5);
}