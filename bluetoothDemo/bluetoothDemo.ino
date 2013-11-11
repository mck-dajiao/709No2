/*
   Testing a bluetooth module
Date :		2013/11/10
Author:		dajiao
File :		bluetoothDemo.ino

Addition:
	Only for arduino mega which has 3 serial port in the board.
	Serial for the Serial Monitor in Arduino IDE
	Serial1/2/3 for the real serial port in a arduino board

*/

const int led = 13;		// set the 13 as working light
int i, j;	// pointer for reading from Serial
char buffer[100];		// set up the buffer for reading 

void setup(){
	Serial.begin(9600);		// initialize the serial monitor with 9600
	Serial1.begin(9600);	// initialize the NO.1 serial port in board
	pinMode(led, OUTPUT);	// set a led light when working
	Serial1.println("AT+NAMEdajiao");	// set up id for bluetooth module
}

void loop(){
	if(Serial1.available()>0){

		i = j = 0;
		// read from bluetooth(Serial)
		while(Serial1.available()>0){
			buffer[i] = Serial1.read();	
			i++;
			delay(2);
			digitalWrite(led, HIGH);
		}

		buffer[i] = '\0';
		delay(1000);
		digitalWrite(led, LOW);
		// print the current string
		for(j = 0; j< i; j++){
			Serial.print(buffer[j]);
		}

		Serial.println();
	}
}
