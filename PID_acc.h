#ifndef PID_controller
#define PID_controller


//macros for constant
#define Pid_kp 1 
#define Pid_Ki 0.01 
#define Pid_kd 1 


#define In_max_lim 10
#define In_min_lim  -4
#define Pid_voltage_max 20
#define Pid_voltage_min  0.001
#define time_constant 0.01

typedef struct {
	//PID gains
	float Kp;
	float Ki;
	float Kd;
	//Sample time and time constant of low pass filter
	float tau;
	float T;	
	
	//intergral windup: saturation limit has to be defined
	float integral_min;
	float integral_max;
	//Actuator  voltage limitation
	float voltage_max;
	float voltage_min;

  //control variable
	float integrator;
	float prev_error;
	float diff;
	float prev_meas;
	float error;

  //output voltage
	float voltage_out;

} PIDcontroller;

void PIDController_init(PIDcontroller *pid);
float PIDController_update(PIDcontroller *pid, float sp, float measured_value);

void setGain(PIDcontroller *pid, float kp, float ki, float kd);

#endif


