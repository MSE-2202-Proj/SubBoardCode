#include <SoftwareSerial.h> //Not sure where to get this if you don't already have it.

SoftwareSerial IRSensor(A3, A3);
int lightSensor_int = 0;
int lightCorrectCounter = 0;
int lightTotalCounter = 0;
bool vowelCondition = 0; // 0:A,E. 1:I,O.

//Check vowel types
bool AE = false;
bool IO = false;
bool doOnce = false;
unsigned long oldMillis = 0;
void setup() {
  // put your setup code here, to run once:
  
Serial.begin(9600);


IRSensor.begin(2400);
pinMode(2, OUTPUT); //Use these in set up. It's important
pinMode(A3, INPUT);
pinMode(3, INPUT);

digitalWrite(3, HIGH);
digitalWrite(2, LOW);

}

void loop() {


//This is what should be used for just sensing the light source. IRSensor.read() will return a value of -1 in all cases where it is not looking at a light.
//If it is looking a light, IRSensor.read() will return a diffrent value depending on how long it has been looking at the light. 
//This has something to do with the message the light is outputing. 
//If you just convert each value returned by IRSensor.read() at 2400 baud, you just get capital As. Which kinda makes sense?
//If it turns out you actually have to read the message, I can figure out this a little more. 

lightSensor_int = IRSensor.read();
//Serial.println(lightSensor_int);
vowelCondition = digitalRead(3);
/*
//Serial.print(lightSensor_int);    
//Serial.print("\n");

Serial.print("\n");
Serial.print(lightTotalCounter);

Serial.print("                    ");
Serial.print(lightCorrectCounter);

Serial.print("                    ");
Serial.print(vowelCondition);
*/


//if (lightTotalCounter != 0) {
  

  if(((lightSensor_int == 65) || (lightSensor_int == 69)) && vowelCondition) {
  AE = true;
  IO = false;
  //Serial.println("-AE");
   /*
  Serial.print("                    ");
Serial.print("1");
  */
  }

  if((lightSensor_int == 79 || lightSensor_int == 73) && !vowelCondition) {
    AE = false;
    IO = true;
    //Serial.println("-IO");
   /*
   /ightCorrectCounter  += 1; 
     Serial.print("                    ");
     Serial.print("2");
  */
  }

  //lightTotalCounter += 1;
  
//}

  if((lightSensor_int != (-1))&&(!doOnce)) {
    digitalWrite(2, HIGH);
    //Serial.println("ONCE");
    //Serial.println(vowelCondition);
    doOnce = true;
  }
  if(lightSensor_int != (-1)){
    if((vowelCondition)&&(AE)){
      digitalWrite(2, HIGH);
      //Serial.println("FOUND");
      oldMillis = millis();
    }
      else if ((!vowelCondition)&&(IO)){
        digitalWrite(2, HIGH);
        //Serial.println("FOUND");
        oldMillis = millis();
      }
      else{
        digitalWrite(2, LOW);
        //Serial.println("LOST");
        doOnce = false;
      }
  }
  else{
    if(millis()-oldMillis >= 1000){
      digitalWrite(2,LOW);
      //Serial.println("LOST");
    }
  }

/*
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
*/

}


