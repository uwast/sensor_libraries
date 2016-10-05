# sensor_libraries
custom arduino libraries for load testing raspberry pi 3 


# Guidelines for sensor_libraries: 
### 1. Name all files: 

    <sensorname>_test.ino 
### 2. Get the sensors to communicate at 9600 baud.
    
    Serial.Begin(9600);  
### 3. Output relevant data every 10 ms.
    
    Serial.println(relevantData);   
### 4. Output all the relevant data that we would need from your sensor (compass heading, gyro rates, acceleration vectors etc.)


