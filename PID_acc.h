
//#define MICROCONTROLLER ( for running into microcontroller)

#ifdef MICROCONTROLLER
#include <dsplib_dsp.h>
#define var32type int32
#else
#define var32type float
#endif
#ifndef PID_controller
#define PID_controller

//macros for constant


#define In_max_lim 10
#define In_min_lim -10
#define Pid_voltage_max 10
#define Pid_voltage_min 0
#define time_constant 0.01

typedef struct
{
	//PID gains
	var32type Kp;
	var32type Ki;
	var32type Kd;
	//Sample time and time constant of low pass filter
	var32type tau;
	var32type T;

	//intergral windup: saturation limit has to be defined
	var32type integral_min;
	var32type integral_max;
	//Actuator  voltage limitation
	var32type voltage_max;
	var32type voltage_min;

	//control variable
	var32type integrator;
	var32type prev_error;
	var32type diff;
	var32type prev_meas;
	var32type error;

	//output voltage
	var32type voltage_out;

} PIDcontroller;

void PIDController_init(PIDcontroller *pid);
float PIDController_update(PIDcontroller *pid, var32type sp, var32type measured_value);

void setGain(PIDcontroller *pid, var32type kp, var32type ki, var32type kd);

#endif
