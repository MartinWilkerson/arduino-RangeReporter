/*
 Name:		RangeReporter.ino
 Created:	3/14/2017 9:27:16 PM
 Author:	drwil_000
*/
const byte triggerPin = 4;
const byte echoPin = 3;
volatile unsigned long start = 0, end = 0, temp;
unsigned long runFromMillis = 0;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(triggerPin, OUTPUT);
	digitalWrite(triggerPin, LOW);
	pinMode(echoPin, INPUT);

	Serial.begin(9600);

	attachInterrupt(digitalPinToInterrupt(echoPin), pinChange, CHANGE);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (runFromMillis == 0) {
		runFromMillis = millis();
		start = 0;
		end = 0;
		trigger();
	}
	else if (start != 0 && end != 0) {
		runFromMillis = 0;
		//write out result
		unsigned long duration = end - start;
		/*Serial.print("Time: ");
		Serial.print(duration);
		Serial.println("us");*/
		float cm = (duration) / 58.0;
		Serial.print("Distance: ");
		Serial.print(cm);
		Serial.println("cm");
	}
	else if (millis() - runFromMillis > 25) {
		//timeout, reset
		runFromMillis = 0;
		Serial.println("Out of range");
	}

}

void trigger() {
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);
}

void pinChange() {
	temp = micros();
	if (start == 0) {
		start = temp;
	}
	else {
		end = temp;
	}
}