int val = 0;
int ledPin = 13;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = Serial.read();
  if (-1 != val) {
    if ('A' == val || 'a' == val)
    {
      Serial.println("Hello from Arduino");
    }
    else if ('B' == val || 'b' == val)
    {
      digitalWrite(ledPin,HIGH);
      delay(500);
      digitalWrite(ledPin,LOW);
    }
}
}

