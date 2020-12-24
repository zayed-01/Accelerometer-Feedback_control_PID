#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "PID_acc.h"
#include"Lowpassfilter.h"
#include "data.h"

float dac_out;

#define Simulation_time 84 
#define Sample_time .0001
low_pass_f filter;
 

float system_parameter_test(PIDcontroller *p);
void simulating_controller();


float  setpoint = 0;



int main(void) {


  PIDcontroller pid = {1, 10 , 0,time_constant, Sample_time,
  In_max_lim, In_min_lim, Pid_voltage_max, Pid_voltage_min };
  PIDController_init(&pid);


  setGain(&pid, 1, 100, 0);


  simulating_controller(&pid);


  
}




void simulating_controller(PIDcontroller *p){
//simulating the function,
  for (int t=0; t<=Simulation_time; t++){

  float control_out = PIDController_update(p,setpoint,meas[t]);

  printf("Dac_out= %f\n", dac_out);

};


}