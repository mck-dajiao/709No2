/*
   test serial connect with raspberry pi
Note:		only for arduino mega
Date:		2013/11/12
Author:		dajiao

*/

byte num = 0;

void setup(){

	Serial.begin(9600);		// set up serial monitor in computer
	Serial1.begin(9600);	// set up first serial port in arduino mega
}

void setup(){
	if(Serial1.available()>0){
		num = Serial.read();

		Serial.print("recieved: ");
		Serial.println(num, DEC);
		Serial1.println("get it");

	}
}
