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

Servo platform;
Servo trapdoor;

int switchPin2 = 6;
int switchPin1 = 7;
int powerControl = 8;
int platPin= 9;
int trapPin = 10;
int incomingByte = 0; // for incoming serial data
//int posplat = 0; //for switch statement
int postrap = 0; //for trapdoor position
int switchStatus = 0;
int shutoff = 0;
int spin = 0;
int binNum = 0;

void setup() {
    //Debug
  Serial.begin(9600);
    // pin 6 to switch
    //pinMode(switchPin2, INPUT);

    // pin 7 to switch
    pinMode(switchPin1, INPUT);
    
    // pin 8 to base of Transistor
    pinMode(powerControl, OUTPUT);
    Serial.println("Transistor base set to pin " + String(powerControl, DEC));
    
    //pin 9 to Servo signal line
    pinMode(platPin, OUTPUT);
    Serial.println("Servo signal set to pin " + String(servoPin, DEC));

    //pin 10 to trapdoor 
    trapdoor.attach(trapPin); 
    trapdoor.write(0);
    
    //pin 13 to light
    pinMode(13, OUTPUT);

    Serial.println("Ready");

}

void loop() {
      if (Serial.available() > 0) {
      binNum = Serial.read();
  
      Serial.print("I received: ");
      Serial.println(binNum, DEC);   // display received value as decimal
    }
    
    switch(binNum){
      
      case 49://(binNum == 1)
        bin1();
        break;
      case 50://(binNum == 2)
        bin2();
        break;
      case 51://(binNum == 3)
        bin3();
        break;
      case 52://(binNum == 4)
        bin4();
        break;
    }
}

void bin1() {
    while(spin == 0)
    {
      switchStatus = digitalRead(switchPin1);
      Serial.println(switchStatus);
      //Serial.println("Servo attached");
      servo.attach(servoPin);
      digitalWrite(powerControl, HIGH);
      servo.write(95);
      if(switchStatus == HIGH)
      {
        Serial.println("Servo detached");
        digitalWrite(13, HIGH);
        digitalWrite(powerControl, LOW);
        servo.detach();
        spin = 1;
      }
    }
}

void bin3() {
  while(spin == 0)
    {
      switchStatus2 = digitalRead(switchPin12);
      Serial.println(switchStatus);
      //Serial.println("Servo attached");
      platform.attach(servoPin);
      digitalWrite(powerControl, HIGH);
      platform.write(95);
      if(switchStatus2 == HIGH)
      {
        Serial.println("Servo detached");
        digitalWrite(13, HIGH);
        digitalWrite(powerControl, LOW);
        platform.detach();
        spin = 1;
      }
    }
}

