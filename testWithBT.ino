/*
   test driver servo with bluetooth in arduino mega
Date :		2013/11/11
Author:		dajiao

*/

#include <Stepper.h>

const int stepPer = 200;
int led = 13;
int begin;
int i, j, k; 
char buffer[100];
char ins;

Stepper stepper1(stepPer, 4, 5, 6, 7);
Stepper stepper2(stepPer, 8, 9, 10, 11);

void goAhead(){
  
  for(i = 0; i < 50; i++){
        stepper1.step(4);
	stepper2.step(4);
  }
	

	Serial.println("Go ahead");
}

void goBack(){

	stepper1.step(-stepPer);
	stepper2.step(-stepPer);
	Serial.println("Go Back");
}

void turnLeft(){

	stepper1.step(-stepPer);
	stepper2.step(stepPer);
	Serial.println("Turn Left");

}

void turnRight(){

	stepper1.step(stepPer);
	stepper2.step(-stepPer);
	Serial.println("Turn Right");
}

void stepControl(){

	char inst = '0';

	Serial.println("contrl");
	
	while(inst != '$'){
		Serial.readBytes(&inst, 1);
	switch(inst){
		// go ahead 
		case '1': goAhead();
			break;
		// go back 
		case '2': goBack();
			break;
		// turn left
		case '3': turnLeft();
			break;
		// turn right
		case '4': turnRight();
			break;
		default:
			Serial.println("Error");
	}

	}

        Serial.println("end of contrl");

}

void other(){

}

void test1(char inst){
	int l;
	for(l = 0; l <inst; l++){
		stepper1.step(4);
		stepper2.step(4);
	}
}

void test2(char inst){
	int l;
	for(l = 0; l <inst; l++){
		stepper2.step(4);
		stepper1.step(4);
	}
}

void testStep(){
	char step = '0';

	Serial.println("test");
	while(step != '$'){

		Serial.readBytes(&step, 1);

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
                                Serial.print("test: ");
                                Serial.print("waiting ");
                                Serial.println("for input");
				break;

		}
	}

        Serial.println("end of test");
}

void setup(){
	stepper1.setSpeed(60);
	stepper2.setSpeed(60);

	Serial.begin(9600);
	// Serial1.begin(9600);
	// Serial1.println("AT+NAMEdajiao");	// set up the id for bluetooth
}

void loop(){


	if(Serial.available()){

		// Serial.println("loop step1");

		begin = Serial.read();
		
		Serial.println("loop step2");
                // Serial.println(begin);
		if(begin==35){
                       
		Serial.println("loop step3");
	 	        Serial.readBytes(&ins, 1);
			switch(ins){
				case '1': 
					// Serial.println("switch step1");
					stepControl();
					break;
				case '2': 
					// Serial.println("switch step2");
					testStep();
					break;
				case '3':
					// Serial.println("switch step3");
					other();
				default: 
					break;
			}
                        
                        // Serial.println("end of if #");
			begin = 0;
		}
                
                // Serial.println("end of available");

	}
}

