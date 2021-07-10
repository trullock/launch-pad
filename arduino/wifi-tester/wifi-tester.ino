void setup()
{
	Serial.begin(115200);
	Serial.println();

	


}

void loop()
{

	float val = analogRead(A0);
	float v = val / 225.0 + 10.6;

	Serial.print("V: ");
	Serial.println(v);

}