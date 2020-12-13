#include "PID_acc.h"


void PIDController_init(PIDcontroller *pid) {
	/* 
  Input : Address of the controller 
  Output: Null
  Function: Intilization of the controller parameters for computations
  Clear controller variables 
  */

	pid->integrator = 0;
	pid->prev_error  = 0;

	pid->diff  = 0;
	pid->prev_meas = 0;

	pid->voltage_out = 0;

}

void setGain(PIDcontroller *pid, float kp, float ki, float kd){
  /* 
  Input : Address of the controller, PID gains
  Output: Null
  Function: Setting controller gains for computations
  */
	pid->Kp = kp;
	pid->Ki = ki;
	pid->Kd = kd;

}

float PIDController_update(PIDcontroller *pid, float sp, float measured_value){
  /* 
  Input : Address of the controller, set point, value from ADC
  Output: Output control voltage
  Function: This functions calculates the controller output 
  */

	float error = sp - measured_value;

	float propotional = pid->Kp * error;

	pid->integrator = pid->integrator + pid->Ki*pid->T*0.5*(error+ pid->prev_error);

	//integral windup

	if (pid->integrator > pid->integral_max){
		pid->integrator = pid->integral_max;
	} else if (pid->integrator < pid->integral_min){
		pid->integrator = pid->integral_min;
	}
	//windup checking 



//dfferential part

	//pid->diff = ((2*pid->Kd)/(2*tau + T))*(measured_value-pid->prev_meas) + ((2*tau - T)/(2*tau+T))*pid->diff ; 

	pid->voltage_out = propotional+ pid->integrator + pid->diff ;

	if (pid->voltage_out> pid->voltage_max){
		pid->voltage_out = pid->voltage_max;
	}else if (pid->voltage_out < pid->voltage_min){
		pid->voltage_out = pid->voltage_min ;
	}


	pid->prev_error = error;
	pid->prev_meas = measured_value;

	return pid->voltage_out;

}

