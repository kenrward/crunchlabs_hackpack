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
const int in3 = 5;
const int in4 = 4;

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

    /*
    * Check if received data is available and if yes, try to decode it.
    */
    if (IrReceiver.decode()) {

        /*
        * Print a short summary of received data
        */
        IrReceiver.printIRResultShort(&Serial);
        IrReceiver.printIRSendUsage(&Serial);
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) { //command garbled or not recognized
            Serial.println(F("Received noise or an unknown (or not yet enabled) protocol - if you wish to add this command, define it at the top of the file with the hex code printed below (ex: 0x8)"));
            // We have an unknown protocol here, print more info
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        }
        Serial.println();

        /*
        * !!!Important!!! Enable receiving of the next value,
        * since receiving has stopped after the end of the current received data packet.
        */
        IrReceiver.resume(); // Enable receiving of the next value

         /*
        * Finally, check the received data and perform actions according to the received command
        */

        switch(IrReceiver.decodedIRData.command){ //this is where the commands are handled


          case up: // UP button
            //Serial.print(F("up"));
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


// This function lets you control spinning direction of motors
void directionControl() {
	// Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
	analogWrite(enA, 255);
	analogWrite(enB, 255);

	// Turn on motor A & B
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
	delay(2000);
	
	// Now change motor directions
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	delay(2000);
	
	// Turn off motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

// This function lets you control speed of the motors
void speedControl() {
	// Turn on motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	
	// Accelerate from zero to maximum speed
	for (int i = 0; i < 256; i++) {
		analogWrite(enA, i);
		analogWrite(enB, i);
		delay(20);
	}
	
	// Decelerate from maximum speed to zero
	for (int i = 255; i >= 0; --i) {
		analogWrite(enA, i);
		analogWrite(enB, i);
		delay(20);
	}
	
	// Now turn off motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}