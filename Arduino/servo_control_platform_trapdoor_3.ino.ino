/* 
    - in setup(), 
        -rotate lazy susan until switch is pressed. That will be the initial position
  - in loop(),
    - read serial input
    - process serial input and decide what to do based on cmd, then run sequence...
        processSerial(){
          if cmd is a bin#, assing time delay depending on bin# chosen
          if cmd is something else (turn transistor on/off), digitalWrite low/high
        }
    - rotate lazy susan based on selected time delay, open platform, close platform and 
    rotate until position is back to zero
    - reset variables if needed
*/

#include <Servo.h> 
//#include <Timer.h>
 
Servo platform;  
Servo trapdoor;

int switchPin = 7;
int powerControl = 8;
int platPin = 9;
int trapPin = 10;
int incomingByte = 0;   // for incoming serial data
int posplat = 0;      //for location of platform to drop
int postrap = 0;    // variable to store the servo position  
int switchStatus = 0;
bool absolutePos = false;
bool susanMoved = false;
long timePassed = 0;
 
void setup() 
{ 
  Serial.begin(9600);

  //pin 7 for location switch
  pinMode(switchPin, INPUT); //this will allow the switch to deliver a signal to the Arduino about when the turntable is at the "0" position
  digitalWrite(switchPin, LOW);

  // pin 8 to base of Transistor
  pinMode(powerControl, OUTPUT);
  digitalWrite(powerControl,LOW);
  Serial.println("Transistor base set to pin " + String(powerControl));

  //pin 9 to platform signal line
  pinMode(platPin, OUTPUT);
  Serial.println("Servo signal set to pin " + String(platPin));     
  platform.attach(platPin);  // attaches the servo on pin 9 to the servo object 
  platform.write(95);

  /*
   * At platform.write(91); time per rotation is about 7 seconds
   * At platform.write(93); time per rotation is about 4.2 seconds THEREFORE time per quarter is 1.05 seconds
   * At platform.write(100); time per rotation is about 3 seconds
   */
  
  trapdoor.attach(trapPin); //trapdoor to pin 10
  trapdoor.write(0);
  
 // platform.writeMicroseconds(500); //set servo to midpoint as default
  trapdoor.write(0);
 
   /*digitalWrite(powerControl, HIGH);
   Serial.println(switchStatus);
   if(switchStatus != 0){
      digitalWrite(powerControl, LOW);  
   }

  Serial.println(switchStatus);
  digitalWrite(powerControl, LOW);  
  */

    switchStatus = digitalRead(switchPin);
    if(switchStatus == HIGH){
      //turn off servo power
      digitalWrite(powerControl, LOW);
      Serial.println("Servo power is OFF");
    
        //turn off the pwm signal to the servo
      platform.detach();
      Serial.println("Servo detached and at absolute position");
    }

    else{
       // turn on the pwm signal to the servo
      platform.attach(platPin);
      Serial.println("Servo attached to " + String(platPin, DEC));
    
        // turn on servo power
      digitalWrite(powerControl, HIGH);
      Serial.println("Servo Power is ON");
    
      platform.write(95);
    }

    /**while(switchStatus == LOW){
      platform.attach(platPin);
      Serial.println("Servo attached to " + String(platPin, DEC));
    
        // turn on servo power
      digitalWrite(powerControl, HIGH);
      Serial.println("Servo Power is ON");
      platform.write(95);  

      if(switchStatus == HIGH){
        break;
        }
    }
    
    //turn off servo power
    digitalWrite(powerControl, LOW);
    Serial.println("Servo power is OFF");
      
    //turn off the pwm signal to the servo
    platform.detach();
    Serial.println("Servo detached");
    **/
      
  Serial.println("Ready");
} 

// Main Loop. This runs continuously 
void loop() 
{ 

  /*--------------------------------
  ATTACH servo signal to pin 9, turn
    ON servo power and MOVE (0 to 180)
    --------------------------------*/
    // turn on the pwm signal to the servo
  // platform.attach(platPin);
    //Serial.println("Servo attached to " + String(platPin, DEC));

    // turn on servo power
//    digitalWrite(powerControl, HIGH);
//    Serial.println("Servo Power is ON");
    
//  boolean platwritten = false; // resets every time through the loop 
  if (Serial.available() > 0) {
    posplat = Serial.read();

    Serial.print("I received: ");
    Serial.println(posplat, DEC);   // display received value as decimal
  }
  digitalWrite(powerControl, HIGH);
  switchStatus = digitalRead(switchPin);
  //if(switchStatus = 1){
  //  absolutePos = true;
  //  Serial.println("Absolute Position is true");
        
    switch(posplat){
      case 49: //1
        //posplat=0;
        susanMoved=true;
        delay(1050);
        break;
      case 50://2
        //posplat=90;
        susanMoved=true;
        delay(2100);
        break;
      case 51://3
        //posplat=180;
        susanMoved=true;
        delay(3150);
        break;
      case 52://4
        //posplat=270;
        susanMoved=true;
        delay(4200);
        digitalWrite(powerControl, LOW);
        break;
      /*case 53://5
        //posplat=0;
        susanMoved=true;
        delay(1050);
        digitalWrite(powerControl, LOW);
         }
        break;*/
        
      case 79: //O
        digitalWrite(powerControl, HIGH);
        //Serial.println("transistor on");
        break;
      case 83:// S
        digitalWrite(powerControl, LOW);
        //Serial.println("transistor off");
        break;
      default:
        //posplat=135;
        susanMoved=false;
        //Serial.println("Nothing happened");
        break;  
 //   }
  }
  digitalWrite(powerControl, LOW);
//  else{
//    Serial.println("nothing yet");
//  }
  // runs once after susanMoved is set to true
  if(susanMoved){
    
    Serial.println("The lazy susan moved! Drop the item");
    Serial.println("Position: " + String(posplat, DEC));
    //platform.write(posplat);
    
     /*--------------------------------
  Turn OFF servo, DETACH pin 10 and
    WAIT for 1 second
    --------------------------------*/  
  
    // turn off servo power
//    digitalWrite(powerControl, LOW);
//    Serial.println("Servo Power is OFF");
  
  //turn off the pwm signal to the servo
//    platform.detach();
//    Serial.println("Servo detached");
//    

    //Wait, then open trap door
    delay(2000);
    trapdoor.write(90);
    delay(3000);
    
    // Close trapdoor slowly. Reset to trapdoor to pos 0. 
    for(int i = 60; i > 0; i--){
      trapdoor.write(i);
      delay(10);
  
    susanMoved = false; 
    // *lazy susan servo does not need to reset to it's original position 
    }  
    
    timePassed = 0;  
    
    //wait for 1 second
    Serial.println("Waiting for 1 sec...");
    delay(1000);
    Serial.println("Ready again!");

  }
} 
