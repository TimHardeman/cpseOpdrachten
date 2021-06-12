#ifndef SERVOANDULTRASONIC_HPP
#define SERVOANDULTRASONIC_HPP

#include "hwlib.hpp"

class servoAndUltrasonic{
private:

	hwlib::pin_out & trigger;
	hwlib::pin_in & echo;
	hwlib::pin_out & servo;
	int pulseUS = 1000;
	
	double distanceCM(int timeoutUS){
	
		unsigned int startOfFunction = hwlib::now_us();
	
		trigger.write(0);
		trigger.flush();
		hwlib::wait_us(2);
		
		trigger.write(1);
		trigger.flush(); 
		hwlib::wait_us(10);
		
		trigger.write(0);
		trigger.flush();
		
		while(echo.read() == 0){}
		int begin = hwlib::now_us();
		
		while(echo.read() == 1){ if((startOfFunction + timeoutUS) <= hwlib::now_us()){hwlib::cout << -1 << '\n'; return -1;} }
		int end = hwlib::now_us();
		
		
		int timeUS = end - begin;
		double distance = (0.034 * timeUS) / 2;
		
		return distance;
	}
	
public:

	servoAndUltrasonic(hwlib::pin_out & trigger, hwlib::pin_in & echo, hwlib::pin_out & servo):
		trigger(trigger),
		echo(echo),
		servo(servo)
		{}

	void setAngle(int angle){
		if(angle < 0){
			angle = 0;
		}
		else if(angle > 180){
			angle = 180;
		}
		
		double usPerDegree = 1000 / 180;
		pulseUS = 1000 + (usPerDegree * angle);
	}
		
	void setPulse(int pulse){
		if(pulse < 1000){
			pulse = 1000;
		}
		else if(pulse > 2000){
			pulse = 2000;
		}
		pulseUS = pulse;
	}
	
	double pulse(){
		unsigned int start = hwlib::now_us();
		servo.write(1);
		hwlib::wait_us(pulseUS);
		servo.write(0);
		int timeout = 20000 - pulseUS;
		double distance = distanceCM(timeout);

		if(distance != -1){
			hwlib::wait_us(timeout - (hwlib::now_us() - start));
		}
		
		return distance;
	}
};

#endif