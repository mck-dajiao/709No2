/*
   Raspberry Pi with arduino mage
Note: 		Only for arduino mage
Date:		2013/11/12	
Author:		dajiao

*/

#include <Stepper.h>

const int stepPer = 200;
const int led = 13;
int i;
int begin;
char ins;


Stepper stepper1(stepPer, 4, 5, 6, 7);
Stepper stepper2(stepPer, 8, 9, 10, 11);

void goAhead(){
  
	digitalWrite(led, HIGH);
	for(i = 1; i<4; i++){
    	stepper1.step(4);
		stepper2.step(4);
	}
	// Serial.println("Go Ahead");
	digitalWrite(led, LOW);
}

void goBack(){

	stepper1.step(-16);
	stepper2.step(-16);
	// Serial.println("Go Back");
}

void turnLeft(){

	stepper1.step(-8);
	stepper2.step(8);
	// Serial.println("Turn Left");

}

void turnRight(){

	stepper1.step(8);
	stepper2.step(-8);
	// Serial.println("Turn Right");
}

void stepControl(){

	char inst = '0';

	while(inst != '@'){

		inst = Serial1.readBytes(&inst, 1);
	
		switch(inst){
			// go ahead 
			case '1': goAhead();
					  inst = '0';
						break;
			// go back 
			case '2': goBack();
					  inst = '0';
						break;
			// turn left
			case '3': turnLeft();
					  inst = '0';
						break;
			// turn right
			case '4': turnRight();
					  inst = '0';
						break;
			default:
				Serial.println("Error");

		}
	}
}

void test(){
	char step = '0';

	Serial.println("test mode");
	while(step != '$'){

		Serial1.readBytes(&step, 1);

		switch(step){
			case '1':	
				stepper1.step(4);
				stepper2.step(4);
                                Serial.println("step 1");
                                break;
			case '2':
				stepper2.step(4);
				stepper1.step(4);
                                Serial.println("step 2");
				break;
			case '3':
				stepper1.step(8);
				stepper2.step(8);
                                Serial.println("step 3");
				break;
			case '4':
				stepper2.step(8);
				stepper1.step(8);
                                Serial.println("step 4");
				break;
            case '5':	
				stepper1.step(4);
				stepper2.step(4);
                                Serial.println("step 1");
                                step = '0';
                                break;
			case '6':
				stepper2.step(4);
				stepper1.step(4);
                                Serial.println("step 2");
                                step = '0';
				break;
			case '7':
				stepper1.step(8);
				stepper2.step(8);
                                Serial.println("step 3");
                                step = '0';
				break;
			case '8':
				stepper2.step(8);
				stepper1.step(8);
                                Serial.println("step 4");
                                step = '0';
				break;
			default:
				Serial.println("waiting for input...");
				break;

		}
	}

        Serial.println("end of test");
}

void debug(){
	
}

void setup(){
	pinMode(led, OUTPUT);

	stepper1.setSpeed(60);
	stepper2.setSpeed(60);

	Serial.begin(9600);		// set up the serial monitor on a computer
	Serial1.begin(9600);	// set up the first serial port in arduino mega
}

void loop(){

	if(Serial1.available()){

		begin = Serial1.read();
		
		if(begin==35){
	 		Serial1.readBytes(&ins, 1);
			switch(ins){
				case '1': 
					stepControl();
					break;
				case '2': 
					test();
					break;
				default: 
					break;
			}
			begin = 0;
		}
	}
}

