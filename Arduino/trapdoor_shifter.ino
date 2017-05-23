#include <Servo.h>

Servo trapdoor;
int trapPin = 10;

void setup() {
  // put your setup code here, to run once:
  trapdoor.attach(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  trapdoor.write(10);
  delay(50);
  trapdoor.write(15);
  delay(50);
  trapdoor.write(3);
  delay(5000);
}
