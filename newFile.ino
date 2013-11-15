#include <Stepper.h>
#include <OneWire.h>
#include <DallasTemperature.h>

char inst = ' ';

// sensor 
char sen ;
#define ONE_WIRE_BUS 3
#define TrigPin 4
#define EchoPin 5
#define SmogPin 6
#define RedPin 7
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float temperature = 0;
float cm;
float smog;
int red;


// Stepper
Stepper stepper1(stepPer, 4, 5, 6, 7);
Stepper stepper2(stepPer, 8, 9, 10, 11);
int begin;
int i;
char direct = '\0';

void stop(){
	
	while(inst != '@'){
		if(Serial1.available()>0)
			Serial1.readBytes(&inst, 1);
	}
}

void goAhead(){
	
	while(inst != '@'){
		if(Serial1.available()>0){

			Serial1.readBytes(&inst, 1);
			stepper1.step(30);
			stepper2.step(-30);
		}
		
	}
}


void goBack(){
	
	while(inst != '@'){
		if(Serial1.available()>0){
		
			Serial1.readBytes(&inst, 1);
			stepper1.step(-30);
			stepper2.step(30);
		}
		
	}
}


void left(){
	
	while(inst != '@'){
		if(Serial1.available()>0){
		
			Serial1.readBytes(&inst, 1);
			stepper1.step(30);
		}
		
	}
}

void right(){
	
	while(inst != '@'){
		if(Serial1.available()>0){
			Serial1.readBytes(&inst, 1);
			stepper2.step(-30);
		}
		
	}
}


void motion(){
	
	Serial1.readBytes(&inst, 1);

	direct = inst;
	
	switch(direct){
		case 0 : stop();
				break;
		case 5 : goAhead();
				break;
		case 10: goBack();
				break;
		case 15: left()
				break;
		case 20: right();
				break;
		default: break;
	}
	
}

void status(){
	if(Serial1.available()>0){
		Serial1.readBytes(&inst, 1);
	}
	if(inst == "@"){
		Serial1.print("$1");
		Serial1.print(direct);
		Serial1.print("@");
	}
}


void temp(){
	
	sensors.requestTemperatures();
	temperature = sensors.getTempCByIndex(0);
	Serial1.print("$");
	Serial1.print(sen);
	//TODO
	Serial1.print();
	Serial1.print(temperature);
	Serial1.print("@");
}

void sunar(){
	
	digitalWrite(TrigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(TrigPin, HIGH);
	delayMicroseconds();
	digitalWrite(TrigPin, LOW);
	
	cm = pulseIn(EchoPin, HIGH) / 58.0;

	Serial1.print("$");
	Serial1.print(sen);
	//TODO
	Serial1.print();
	Serial1.print(cm);
	Serial1.print("@");

	delay(60);
}

void smog(){
	
	smog = analogRead(SmogPin);
	Serial1.print("$");
	Serial1.print(sen);
	//TODO
	Serial1.print();
	Serial1.print(smog);
	Serial1.print("@");
} 

void red(){
	
	red = digitalRead(RedPin);	
	Serial1.print("$");
	Serial1.print(sen);
	//TODO
	Serial1.print();
	Serial1.print(red);
	Serial1.print("@");
}

void sensor(){
	
	if(Serial1.available()>0){
		Serial1.readBytes(&inst, 1);	
	}

	while(inst != '@'){
	Serial1.readBytes(&inst, 1);
	sen = inst;
	switch(inst){
		case 0:	temp();
				break;
		case 5:	sunar();
				break;
		case 10:smog(); 
				break;
		case 15:red();
				break;
		default:	
				break;
	}		
	}
}

void setup(void){
	
	Serial.begin(9600);
	
	// Stepper
	Serial1.begin(9600);
	stepper1.setSpeed(60);
	stepper2.setSpeed(60);

	// sensor
	sensors.begin();
	pinMode(TrigPin, OUTPUT);
	pinMode(EchoPin, INPUT);

}

void loop(){
	
	if(Serial.available()>0){
		
		Serial.readBytes(&inst, 1);		
		
		if(inst == '$'){
			
			Serial.readBytes(&inst, 1);
			switch(inst){
			
				case '0' : motion();
						   break;
				case '1' : status();
						   break;
				case '2' : sensor();
							break;
				default:	
							break;
			}
			
			inst = ' ';
		}
	}
}

