#include "PID_acc.h"
#include<math.h>
#include <stdbool.h> 
#include "Lowpassfilter.h"
float dac_out;
bool  integral_switch;

extern low_pass_f filter;
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
  init_low_pass(&filter);

}

void setGain(PIDcontroller *pid, var32type kp, var32type ki, var32type kd){
  /* 
  Input : Address of the controller, PID gains
  Output: Null
  Function: Setting controller gains for computations
  */
	pid->Kp = kp;
	pid->Ki = ki;
	pid->Kd = kd;

}

var32type PIDController_update(PIDcontroller *pid, float sp, var32type measured_value){
  /* 
  Input : Address of the controller, set point, value from ADC
  Output: Output control voltage
  Function: This functions calculates the controller output 
  */
  //measured_value: -2^23 -> 2^23
  integral_switch = true;

  float measured_voltage = measured_value / pow(2, 23) * 2.4; // -2.4 -> 2.4

	float error = measured_voltage;

	float propotional = pid->Kp * error;

	pid->integrator = pid->integrator + pid->Ki*pid->T*0.5*(error+ pid->prev_error);

	//integral windup

	if (pid->integrator > pid->integral_max){
		pid->integrator = pid->integral_max;
    if (error>0)
      integral_switch = false;


	} else if (pid->integrator < pid->integral_min){
		pid->integrator = pid->integral_min;
    if(error<0)
      integral_switch= false;
	} 
  else 
    pid->integrator = pid->integrator; 


  
	//windup checking 
//printf("PID integrator  = %f \t", pid->integrator);


//dfferential part

	//pid->diff = ((2*pid->Kd)/(2*tau + T))*(measured_value-pid->prev_meas) + ((2*tau - T)/(2*tau+T))*pid->diff ; 
  pid->diff = (measured_value-pid->prev_meas)/ (pow(2, 23) * 2.4*pid->T); 
  
  float differn = low_pass_filter(&filter, pid->diff);

	pid->voltage_out = pid->diff + propotional + pid->integrator; 
 

	if (pid->voltage_out> pid->voltage_max){
		pid->voltage_out = pid->voltage_max;
	}else if (pid->voltage_out < pid->voltage_min){
		pid->voltage_out = pid->voltage_min ;
	}

  //printf("voltage out  = %f \t", pid->voltage_out);
  //printf("Measured value  = %f \t",  measured_value);
  //printf("Integrator  = %f \t", pid->integrator);


	pid->prev_error = error;
	pid->prev_meas = measured_value;

  dac_out = (pid->voltage_out * pow(2, 12) / 10);


	return dac_out ;

}

