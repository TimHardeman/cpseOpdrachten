#ifndef PID_HPP
#define PID_HPP

class PID{
private:

	double P, I, D, dt;
	double summation;
	double previousError;
	
	
public:

	PID(double P, double I, double D, double dt):
		P(P),
		I(I),
		D(D),
		dt(dt)
		{}
			
	double getPIDOutput(double distance, double setpoint){
		double error = setpoint - distance;
		summation += (error * dt);
 		double delta = (error - previousError) / dt;
		previousError = error;
		
		double Poutput = P * error;
		double Ioutput = I * summation;
		double Doutput = D * delta;
		
		return (Poutput + Ioutput + Doutput);
	}
};

#endif