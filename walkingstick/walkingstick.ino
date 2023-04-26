/*
 * Hcsr04 ultrasonic distance sensor test.
 * 2 sensors and piezo buzzer for output.
 * 
 * Saul C. 4/7/23
 */

#include <HCSR04.h>

HCSR04 hc(2, new int[6]{4, 3 }, 2); //initialisation class HCSR04 (trig pin , echo pin, number of sensor)
int buzzer = 25;
int bzs = 0;
void setup()
{
    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);
}
void beep(int v, int s){
  bool b = false;
  if(s==0 and v < 66) b = true;
  else if(s == 1 and v < 33) b = true;
  
    if(b){  
    if(s==0)  analogWrite(buzzer, 1 02);
    else  analogWrite(buzzer, 252); 
      bzs = micros();
    }else
    if(bzs - micros() > 2000+v*11){
      
    analogWrite(buzzer, 0);
    }
    
    
  
}
void loop()
{
    for (int i = 0; i < 2; i++){
      int v = hc.dist(i);
      beep(v, i);
        Serial.print(v); //return curent distance in serial for sensor 1 to 6
     Serial.print(" ... ");
    }
      Serial.println();
    delay(60);                      // we suggest to use over 60ms measurement cycle, in order to prevent trigger signal to the echo signal.
}
