#define LASER_PIN 2
#define LDR_PIN A0
#define TRIP_LEVEL 700

void setup()
{
    Serial.begin(9600);
    pinMode(LASER_PIN, OUTPUT);
    pinMode(LDR_PIN, INPUT);

    digitalWrite(LASER_PIN, HIGH);
    Serial.println("###############");
    Serial.println("#### START ####");
    Serial.println("#### laser ####");
    Serial.println("###############");
}

void loop()
{
    Serial.print(">ldr:");
    Serial.println(analogRead(LDR_PIN));
}