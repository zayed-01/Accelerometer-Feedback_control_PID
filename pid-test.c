#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "PID_acc.h"

#define Simulation_time 10 
#define Sample_time 100

float system_parameter_test(PIDcontroller *p);
void simulating_controller();

float meas[10] ={2, 2.5, 6, 5, 7, 8,9,5,4,3};
float  setpoint = 1.5;



int main(void) {

PIDcontroller pid = {Pid_kp, Pid_Ki , Pid_kd,time_constant, Sample_time,
In_max_lim, In_min_lim, Pid_voltage_max, Pid_voltage_min };
  
PIDController_init(&pid);



printf("Time (s)\tSystem Output\tControllerOutput\r\n");
float testing2 = system_parameter_test(&pid);
printf("Testing parameters of the controller = %f", testing2);
printf("Two fo the functions are tested, testing set gain fucntion \n");
setGain(&pid, 4, 10, 3);
float testing3 = system_parameter_test(&pid);
printf("3rd function is working fine");

simulating_controller(&pid);


  
}


float system_parameter_test(PIDcontroller *p){
  float output = p->T +  p->Kp*p->tau + p->Ki*time_constant*(p->integral_max - p->integral_min) + p->Kd*(p->voltage_max-p->voltage_min) ;
  printf("%f \n", output);
  float output2= p->integrator+ p->diff + p->prev_error +p->voltage_out  ;
  return output2;
}

void simulating_controller(PIDcontroller *p){
//simulating the function,
for (int t=0; t<=Simulation_time; t++){

float control_out = PIDController_update(p,setpoint,meas[t]);

printf("%d \t %f \t %f\n", t, meas[t], control_out);

};


}