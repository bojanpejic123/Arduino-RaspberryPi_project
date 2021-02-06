//code write by Moz for YouTube changel LogMaker360, 21-9-2015
//code belongs to this video: https://www.youtube.com/watch?v=XBC6pjXSkx0
#include <math.h>    // (no semicolon)

int sensorPin = A0; // select the input pin for the potentiometer

int sensorValue = 0; // variable to store the value coming from the sensor


float i = 0;
float fixtemp = 20.;
int fixInput = 560;
float fixedDegreeValue = 5.5;
double percentage;


 
void setup () 
{
  Serial.begin (9600);
    pinMode(A1, INPUT);
 // Serial.print(",");

}
 
void loop () 
{

 sensorValue = analogRead(sensorPin);  
  if (sensorValue > fixInput ){ // ice cube
    
    i = sensorValue - fixInput;
    i = i /fixedDegreeValue; 
  //  Serial.print("Temperature = ");
    fixtemp = fixtemp - i;
  Serial.print(",");

    Serial.print(fixtemp);
  Serial.print(",");

   // Serial.println(" C");
  }  
  else if(sensorValue < fixInput) //thea cup
  {
     i =  fixInput - sensorValue;
    i = i /fixedDegreeValue; 
    //Serial.print("Temperature = ");
    fixtemp = fixtemp + i;
  
  Serial.print(",");

    Serial.print(fixtemp);
  Serial.print(",");

  //  Serial.println(" C");
  }
  else if(sensorValue == fixInput ){  
 Serial.print(",");

    Serial.print(fixtemp);
 Serial.print(",");

  }
  fixtemp = 20;



double SensorValue = analogRead(A1); //take a sample
      Serial.print(",");

  Serial.println(SensorValue);
      Serial.println(",");


  if(SensorValue >= 1000) {
  // Serial.println("Sensor is not in the Soil or DISCONNECTED");
  }
  if(SensorValue < 1000 && SensorValue >= 600) { 
  // Serial.println("Soil is DRY");
  }
  if(SensorValue < 600 && SensorValue >= 370) {
  // Serial.println("Soil is HUMID"); 
  }
  if(SensorValue < 370) {
  // Serial.println("Sensor in WATER");
  }
  delay(5000);
  
}
