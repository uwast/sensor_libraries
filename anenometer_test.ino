#include "TimerOne.h"          // Timer Interrupt set to 2 second for read sensors
#include <math.h>

#define WindSensorPin (2)      // The pin location of the anemometer sensor
#define WindVanePin (A4)       // The pin the wind vane sensor is connected to
#define VaneOffset 0;        // define the anemometer offset from magnetic north

int VaneValue;       // raw analog value from wind vane
int Direction;       // translated 0 - 360 direction
int CalDirection;    // converted value with offset applied
int LastValue;

volatile bool IsSampleRequired;       // this is set true every 2.5s. Get wind speed
volatile unsigned int  TimerCount;    // used to determine 2.5sec timer count
volatile unsigned long Rotations;     // cup rotation counter used in interrupt routine
volatile unsigned long ContactBounceTime;  // Timer to avoid contact bounce in interrupt routine

float WindSpeed;        // speed miles per hour

void setup() {
  
  LastValue = 0;
  
  IsSampleRequired = false;
  
  TimerCount = 0;
  Rotations = 0;   // Set Rotations to 0 ready for calculations
  
  Serial.begin(9600);

  pinMode(WindSensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(WindSensorPin), isr_rotation, FALLING);

  Serial.println("Davis Anemometer Test");
  Serial.println("Speed (MPH)\tKnots\tDirection\tStrength");

  // Setup the timer intterupt
  Timer1.initialize(50000);
  Timer1.attachInterrupt(isr_timer);
}

void loop() {
  
  getWindDirection();

  // Only update the display if change greater than 5 degrees. 
  if(abs(CalDirection - LastValue) > 2)
  { 
     LastValue = CalDirection;
  }

  if(IsSampleRequired)
  {
     // convert to mp/h using the formula V=P(2.25/T)
     // V = P(2.25/2.5) = P * 0.9
     WindSpeed = Rotations * 45;
     Rotations = 0;   // Reset count for next sample
     
     IsSampleRequired = false; 
     
     Serial.print(WindSpeed);    Serial.print("\t\t");
     Serial.print(getKnots(WindSpeed));    Serial.print("\t"); 
     Serial.print(CalDirection); 
     getHeading(CalDirection);   Serial.print("\t\t"); 
     getWindStrength(WindSpeed);
  }

}

// isr routine fr timer interrupt
void isr_timer() {
  
  TimerCount++;
  
  if(TimerCount == 1)
  {
    IsSampleRequired = true;
    TimerCount = 0;
  }
}

// This is the function that the interrupt calls to increment the rotation count
void isr_rotation ()   {

  if ((millis() - ContactBounceTime) > 15 ) {  // debounce the switch contact.
    Rotations++;
    ContactBounceTime = millis();
  }

}

// Convert MPH to Knots
float getKnots(float speed) {
   return speed * 0.868976;
}

// Get Wind Direction
void getWindDirection() {
 
   VaneValue = analogRead(WindVanePin);
   Direction = map(VaneValue, 0, 1023, 0, 360);
   CalDirection = Direction + VaneOffset;
   
   if(CalDirection > 360)
     CalDirection = CalDirection - 360;
     
   if(CalDirection < 0)
     CalDirection = CalDirection + 360;
  
}

// Converts compass direction to heading
void getHeading(int direction) {
    
    if(direction < 22)
      Serial.print(" N");
    else if (direction < 67)
      Serial.print(" NE");
    else if (direction < 112)
      Serial.print(" E");
    else if (direction < 157)
      Serial.print(" SE");
    else if (direction < 212)
      Serial.print(" S");
    else if (direction < 247)
      Serial.print(" SW");
    else if (direction < 292)
      Serial.print(" W");
    else if (direction < 337)
      Serial.print(" NW");
    else
      Serial.print(" N");  
}

// converts wind speed to wind strength
void getWindStrength(float speed)
{
   
  if(speed < 2)
    Serial.println("Calm");
  else if(speed >= 2 && speed < 4)
    Serial.println("Light Air");
  else if(speed >= 4 && speed < 8)
    Serial.println("Light Breeze");
  else if(speed >= 8 && speed < 13)
    Serial.println("Gentle Breeze");
  else if(speed >= 13 && speed < 18)
    Serial.println("Moderate Breeze");
  else if(speed >= 18 && speed < 25)
    Serial.println("Fresh Breeze");
  else if(speed >= 25 && speed < 31)
    Serial.println("Strong Breeze");
  else if(speed >= 31 && speed < 39)
    Serial.println("Near Gale");
  else
    Serial.println("RUN");
}
