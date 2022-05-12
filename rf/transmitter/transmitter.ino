#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN

#define tunnel1 "PIPE1" // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre
#define tunnel2 "PIPE2"
#define tunnel3 "PIPE3"
#define tunnel4 "PIPE4"
#define tunnel5 "PIPE5"
#define tunnel6 "PIPE6"

const byte adresses[][6] = {tunnel1, tunnel2, tunnel3, tunnel4, tunnel5, tunnel6}; // Tableau contenant les adresses de tunnel, au format "byte array"

int button_pin = 2;
boolean button_state = 0;
void setup()
{
    Serial.begin(9600);
    Serial.println("Starting");
    pinMode(button_pin, INPUT);
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

    radio.openWritingPipe(adresses[0]); //Setting the address where we will send the data

    radio.stopListening(); //This sets the module as transmitter
}
void loop()
{

    const char message[32] = "Mon message à envoyer !";
    radio.write(&message, sizeof(message));

    delay(1000);
}