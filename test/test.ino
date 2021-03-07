#define POTPIN A3

void setup()
{
	Serial.begin(9600);
	pinMode(POTPIN, INPUT);
}

void loop()
{
	Serial.println(analogRead(POTPIN));
}
