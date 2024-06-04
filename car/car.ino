#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include <IRremote.h>


#define DECODE_NEC  //defines the type of IR transmission to decode based on the remote. See IRremote library for examples on how to decode other types of remote

/*
** if you want to add other remotes (as long as they're on the same protocol above):
** press the desired button and look for a hex code similar to those below (ex: 0x11)
** then add a new line to #define newCmdName 0x11,
** and add a case to the switch statement like case newCmdName: 
** this will let you add new functions to buttons on other remotes!
** the best remotes to try are cheap LED remotes, some TV remotes, and some garage door openers
*/

//defines the specific command code for each button on the remote
#define left 0x8
#define right 0x5A
#define down 0x52
#define up 0x18
#define ok 0x1C
#define cmd1 0x45
#define cmd2 0x46
#define cmd3 0x47
#define cmd4 0x44
#define cmd5 0x40
#define cmd6 0x43
#define cmd7 0x7
#define cmd8 0x15
#define cmd9 0x9
#define cmd0 0x19
#define star 0x16
#define hashtag 0xD


const int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);
decode_results results;

// Motor pins
const int enA = 9;
const int in1 = 8;
const int in2 = 7;
const int enB = 3;
const int in3 = 4;
const int in4 = 5;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);
}

void loop() {
  if (irrecv.decode(&results)) {
    unsigned int value = results.value;
    Serial.println(value);

    switch (value) {
      case up: // UP button
        forward();
        break;
      case down: // DOWN button
        backward();
        break;
      case left: // LEFT button
        turnLeft();
        break;
      case right: // RIGHT button
        turnRight();
        break;
      case ok: // OK button (Stop)
        stopMotors();
        break;
    }
    irrecv.resume();
  }
}

void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}

void backward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}

void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}

void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}