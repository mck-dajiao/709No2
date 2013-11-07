#include <DStepper.h>

const int stepPer = 200;

DStepper stepper1(stepPer, 4, 5, 6, 7);
DStepper stepper2(stepPer, 8, 9, 10, 11);

int begin;
char ins[2];
int i;
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

void stepControl(char inst){

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

void other(char inst){

}

void setup(){
	stepper1.setSpeed(60);
	stepper2.setSpeed(60);

	Serial.begin(9600);
}

void loop(){


	if(Serial.available()){

		Serial.println("loop step1");

		begin = Serial.read();
		
		Serial.println("loop step2");
                Serial.println(begin);
		if(begin==35){
                       
		Serial.println("loop step3");
	 		Serial.readBytes(ins, 2);
			switch(ins[0]){
				case '1': 
					Serial.println("switch step1");
					stepControl(ins[1]);
					break;
				case '2': 
					Serial.println("switch step2");
					other(ins[1]);
					break;
				default: 
					break;
			}
                        
                        Serial.println("end of if #");
			begin = 0;
		}
                
                Serial.println("end of available");

	}
}

