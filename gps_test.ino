void setup()
{
 Serial.begin(9600);
 Serial1.begin(9600);
}

void loop()
{
 if (Serial1.available())
 {
  String data = Serial1.read();
  Serial.println(data);
 } 

delay (50);
}
