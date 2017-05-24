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
int platPin = 9;
int trapPin = 10;
int incomingByte = 0; // for incoming serial data
//int posplat = 0; //for switch statement
int postrap = 0; //for trapdoor position
int switchStatus = 0;
int switchStatus2 = 0;
int shutoff = 0;
int spin = 0;
int binNum = 0;
bool susanMoved = false;

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
   switch (binNum) {
    case 49://(binNum == 1)
      bin1();
      susanMoved = true;
      break;
    case 50://(binNum == 2)
      bin2();
      susanMoved = true;
      break;
    case 51://(binNum == 3)
      bin3();
      susanMoved = true;
      break;
    case 52://(binNum == 4)
      bin4();
      susanMoved = true;
      break;
    case 53:
      trapDoor();
      break;
    case 54:
      rotateContinous();
      break;
    case 55:
      rotateStop();
      break;
    case 111: //o
      digitalWrite(powerControl, HIGH);
      //Serial.println("transistor on");
      break;
    case 115://s
      digitalWrite(powerControl, LOW);
      //Serial.println("transistor off");
      break;
    default:
      //posplat=135;
      susanMoved=false;
      //Serial.println("Nothing happened");
      break; 
    }
    if (susanMoved) {
      rotateTrapDoor();
    }
}

void bin1() {
  Serial.println("Spinning to bin 1");
  //start spinning servo
  platform.attach(servoPin);
  digitalWrite(powerControl, HIGH);
  platform.write(94);
  
  //stop when servo reaches first switch
  switchStatus = digitalRead(switchPin1);
  //Serial.println(switchStatus); // print switch status
  if(switchStatus == HIGH)
  {
    delay(200);
    digitalWrite(powerControl, LOW);
    platform.detach();
    binNum = 0;
    Serial.println("Positioned");
  }

}

void bin2() {
  Serial.println("Spinning to bin 2");
  //start spinning servo
  platform.attach(servoPin);
  digitalWrite(powerControl, HIGH);
  platform.write(94);
  
  //stop when servo reaches first switch
  switchStatus = digitalRead(switchPin1);
  //Serial.println(switchStatus); // print switch status
  if(switchStatus == HIGH)
  {
    delay(975);
    digitalWrite(powerControl, LOW);
    platform.detach();
    binNum = 0;
    Serial.println("Positioned");
  }
}

void bin3() {
  Serial.println("Spinning to bin 3");
  //start spinning servo
  platform.attach(servoPin);
  digitalWrite(powerControl, HIGH);
  platform.write(94);
  
  //stop when servo reaches first switch
  switchStatus = digitalRead(switchPin2);
  //Serial.println(switchStatus); // print switch status
  if(switchStatus == LOW)
  {
    delay(800);
    digitalWrite(powerControl, LOW);
    platform.detach();
    binNum = 0;
    Serial.println("Positioned");
  }
}

void bin4() {
  Serial.println("Spinning to bin 4");
  //start spinning servo
  platform.attach(servoPin);
  digitalWrite(powerControl, HIGH);
  platform.write(94);
  
  //stop when servo reaches first switch
  switchStatus = digitalRead(switchPin2);
  //Serial.println(switchStatus); // print switch status
  if(switchStatus == LOW)
  {
    delay(1375);
    digitalWrite(powerControl, LOW);
    platform.detach();
    binNum = 0;
    Serial.println("Positioned");
  }
}

void trapDoor() {
  Serial.println("Nudging Trapdoor");
  trapdoor.write(10);
  delay(50);
  trapdoor.write(15);
  delay(50);
  trapdoor.write(4);
  delay(2000);
}

void rotateContinous() {
  Serial.println("Rotating Continuously");
  platform.attach(servoPin);
  digitalWrite(powerControl, HIGH);
  platform.write(94);
}

void rotateStop() {
    Serial.println("Powered down");
    digitalWrite(powerControl, LOW);
    platform.detach();
    binNum = 0;

}

void rotateTrapDoor(){

    Serial.println("The lazy susan moved! Drop the item");
    Serial.println("Position: " + String(binNum, DEC));

    //Wait, then open trap door
    delay(2000);
    trapdoor.write(90);
    delay(3000);

    // Close trapdoor slowly. Reset to trapdoor to pos 0.
    for (int i = 60; i > 0; i--) {
      trapdoor.write(i);
      delay(10);
    }
    susanMoved = false;
    // *lazy susan servo does not need to reset to it's original position
}

