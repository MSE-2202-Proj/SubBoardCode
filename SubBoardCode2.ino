#include <SoftwareSerial.h> //Not sure where to get this if you don't already have it.

SoftwareSerial IRSensor(A3, A3);
int lightSensor_int = 0;
int lightCorrectCounter = 0;
int lightTotalCounter = 0;

bool vowelCondition = 0; // 0:A,E. 1:I,O.

void setup() {
  // put your setup code here, to run once:
  
Serial.begin(9600);


IRSensor.begin(2400);
pinMode(A0, OUTPUT); //Use these in set up. It's important
pinMode(A3, INPUT);
pinMode(3, INPUT);

digitalWrite(3, HIGH);

}

void loop() {


//This is what should be used for just sensing the light source. IRSensor.read() will return a value of -1 in all cases where it is not looking at a light.
//If it is looking a light, IRSensor.read() will return a diffrent value depending on how long it has been looking at the light. 
//This has something to do with the message the light is outputing. 
//If you just convert each value returned by IRSensor.read() at 2400 baud, you just get capital As. Which kinda makes sense?
//If it turns out you actually have to read the message, I can figure out this a little more. 

lightSensor_int = IRSensor.read();

vowelCondition = digitalRead(3);

//Serial.print(lightSensor_int);    
//Serial.print("\n");

Serial.print("\n");
Serial.print(lightTotalCounter);

Serial.print("                    ");
Serial.print(lightCorrectCounter);

Serial.print("                    ");
Serial.print(vowelCondition);



if (lightTotalCounter != 0) {
  

  if((lightSensor_int == 65 || lightSensor_int == 69) && vowelCondition) {
  lightCorrectCounter += 1;

  Serial.print("                    ");
Serial.print("1");
  }

  if((lightSensor_int == 79 || lightSensor_int == 73) && !vowelCondition) {
   lightCorrectCounter  += 1; 

     Serial.print("                    ");
Serial.print("2");
  }

  lightTotalCounter += 1;
  
}

if(lightSensor_int != (-1) && lightTotalCounter == 0) {
  analogWrite(A0, 1023);
  lightTotalCounter += 1; 
  }


if(lightTotalCounter == 100) {
  
  if (lightCorrectCounter >= 5) {
    analogWrite(A0, 1023);
    Serial.print("CORRECT LIGHT DETECTED");
  lightTotalCounter += 1; 
  }

  if (lightCorrectCounter < 5) {
    lightTotalCounter = 0; 
    lightCorrectCounter = 0;
    analogWrite(A0, 0);
    }
  



}



}


