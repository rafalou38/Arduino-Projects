float oldTime = 0;

float CalculateDeltaTime()
{
	float currentTime = millis();
	float deltaTime = currentTime - oldTime;
	oldTime = currentTime;
	return deltaTime;
}