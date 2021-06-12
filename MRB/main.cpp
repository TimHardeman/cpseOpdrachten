#include "hwlib.hpp"
#include "servoAndUltrasonic.hpp"
#include "medianFilter.hpp"
#include "PID.hpp"

int main(){
	
	// The used pins, d7-9 are digital pins, a0 is an analog pin.
	auto trigger = hwlib::target::pin_out(hwlib::target::pins::d9);
	auto echo = hwlib::target::pin_in(hwlib::target::pins::d8);
	
	auto servo = hwlib::target::pin_out(hwlib::target::pins::d7);
	
	auto potmeter =  hwlib::target::pin_adc(hwlib::target::ad_pins::a0);
	
	// The used classes, servoAndUltrasonic is a combined class for both the motor(using ESC servo control) and the ultrasonic sensor. 
	servoAndUltrasonic control(trigger, echo, servo);
	medianFilter filter;
	PID pid(0.002, 0.002, 0.0005, 0.020);
	

	
	// The ESC used for the motor needs to be initialized with 0 values.
	unsigned int start = hwlib::now_us();
	unsigned int timeout = 25000000; // 25 seconds.
	while(hwlib::now_us() <= (start + timeout)){
		control.setAngle(0);
		control.pulse();
	}
	
	// The ball has trouble getting off the ground, so at the start it gets a shot to start in the middle of the pipe.
	unsigned int startShot = hwlib::now_us();
	unsigned int timeoutShot = 1250000; // 1.25 seconds
	while(hwlib::now_us() <= (startShot + timeoutShot)){
		control.setAngle(40);
		control.pulse();
	}
	
	
	
	double distance, inverseDistance, filteredDistance = 0; // Original, inverted and median filtered distance variables.
	double setpoint = 0; // The distance it will try to get to.
	double motorPercentage = 0; // The percentage at which the motor should spin.
	double servoAngle; // The angle which will be sent via the ESC.
	double reading; // Potentiometer reading.
	double ratioReading = 0; // number between 0 and 1 indicating a setpoint between 0 and 60.
	control.setAngle(0); // Starts at 0 so if anything goes wrong the motor doesn't keep spinning.
	
	while(true){
		distance = control.pulse();
		inverseDistance = 60 - distance; // The distance is measured from the top, while the distance we want is from the bottom.
		if(inverseDistance < 0){ inverseDistance = 0;}
		filteredDistance = filter.applyFilter(inverseDistance );
		
		reading = potmeter.read(); // Reads the potentiometer.
		ratioReading = (reading / 4096); // The analog pin is 12 bits, so the max value is 4096 (2 ^ 12).
		setpoint = ratioReading * 60; // The pipe is 60 cm long.
		
		motorPercentage = (pid.getPIDOutput(filteredDistance, setpoint) * 100); // PID returns a number between 0 and 1 indicating motor percentage.
		servoAngle = motorPercentage * 1.8; // The ESC has a scaling from 0 to 180 degrees, so this converts the percentage to an angle.
		
		// The top of the pipe can be reached with an angle of 45, so to prevent the ball from flying out I capped it at 45.
		if(servoAngle > 45){servoAngle = 45;} 
		
		control.setAngle(servoAngle);
	}
}