/*
 * Hcsr04 ultrasonic distance sensor test.
 * 2 sensors and piezo buzzer for output.
 * 
 * Saul C. 4/7/23
 */

/*
 * oled stuff
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 


//draw oled/ 2 lines
void testdrawoled( String currentTime, String line2) {
  display.clearDisplay();

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(currentTime); 
//  display.println(currentTime.substring(0,4) ); //only 4 chars wide on the main line...
    
  display.setTextSize(2); 
  display.setCursor(0,17);             // Start at top-left corner
  display.println(line2);
  //add day/date in the empty space
  display.display(); 
}


#include <HCSR04.h>

HCSR04 hc(2, new int[6]{4, 3 }, 2); //initialisation class HCSR04 (trig pin , echo pin, number of sensor)
int buzzer = 25;
int bzs = 0;
void setup()
{
    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);
    
    Wire.setSDA(20);
    Wire.setSCL(21);
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
//    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(100); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  testdrawoled("ACME", "MicroRF"); //CALLS DISPLAY()
   
  delay(1000);
  display.clearDisplay();  
}
void beep(int v, int s){
  bool b = false;
  if(s==0 and v < 66) b = true;
  else if(s == 1 and v < 33) b = true;
  
    if(b){  
    if(s==0)  analogWrite(buzzer, 102);
    else  analogWrite(buzzer, 252); 
      bzs = micros();
    }else
    if(bzs - micros() > 2000+v*11){
      
    analogWrite(buzzer, 0);
    }
    
    
  
}
void loop()
{   
    int a, b;
    for (int i = 0; i < 2; i++){
      int v = hc.dist(i);
      if(i == 0) a = v;
      else if(i ==1) b = v;
//      beep(v, i);
        Serial.print(v); //return curent distance in serial for sensor 1 to 6
     Serial.print(" ... ");
    }   
      Serial.println();
    char l1[12];
    sprintf(l1,"%03d   %03d", a, b);  
    testdrawoled(l1, "Acme Test");
    delay(60);                      // we suggest to use over 60ms measurement cycle, in order to prevent trigger signal to the echo signal.
}
