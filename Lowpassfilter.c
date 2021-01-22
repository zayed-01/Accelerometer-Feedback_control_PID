#include <stdio.h>
#include "Lowpassfilter.h"
#include <math.h>

/************************
Low pass filter
Objective : Its first order low pass filter. (expoential smoothing)
Input : Address of the low pass variable, input to the filter from ADC and time between the last filter time
Output: filtered output 
**************************/


float low_pass_filter(low_pass_f *p,float input )

{  
  float sampling_time = .0001; //10Khz sampling rate;

  const float tau = (float) (1/(2*pi*p->Fc)) ;
  const float alpha =sampling_time/(sampling_time + tau);

  float filtered_out = p->prevoutput+ alpha*(input-p->prevoutput);

  p->prevoutput = filtered_out;
  //printf("%f \t", tau);

  return filtered_out;


}
/************************
Low pass filter Initialization 
Objective : Initializing the filter paramters
Input : Address of the low pass variable
Output:None  
**************************/
void init_low_pass(low_pass_f *p){
  p->prevoutput = 0;
  p->Fc = cut_off_f;

}

/*********************************
Initializing all the paramters for moving init_moving_average
Input : moving_average filter Address
Return: None
************************************/
void init_moving_average(moving_avg_def *avg_filter ){
  avg_filter->sum =0 ;
  avg_filter->window_count = 0;
  
  for (int i = 0; i< window_size+1; i++)
  {
    avg_filter->data_history[i] =0;
  }

}
/*********************************
Computingmoving_average
Input : moving_average filter Address, ADC data
Return: filtered value
************************************/

int moving_average_filter(moving_avg_def *avg_filter , int ADC_value){
  //Summing the new value and deleting the last one
  avg_filter->sum = avg_filter->sum + ADC_value - avg_filter->data_history[avg_filter->window_count];
  //Storing it in an array for deleting the value
  avg_filter->data_history[avg_filter->window_count] = ADC_value;
  
  //indicating the number needs to be deleted from the sum ( alaways the last element of the array)
  if (avg_filter->window_count<window_size-1 )
    avg_filter->window_count++;
  else 
    avg_filter->window_count = 0;
  
  return (avg_filter->sum/window_size);
   
}


//for testing the code 



/*

float y[47]= {0,7.36E-01,
1.37E+00,
1.81E+00,
2.00E+00,
1.90E+00,
1.54E+00,
9.64E-01,
2.51E-01,
-4.97E-01,
-1.18E+00,
-1.69E+00,
-1.96E+00,
-1.96E+00,
-1.69E+00,
-1.18E+00,
-4.97E-01,
2.51E-01,
9.64E-01,
1.54E+00,
1.90E+00,
2.00E+00,
1.81E+00,
1.37E+00,
7.36E-01,
7.35E-16,
-7.36E-01,
-1.37E+00,
-1.81E+00,
-2.00E+00,
-1.90E+00,
-1.54E+00,
-9.64E-01,
-2.51E-01,
4.97E-01,
1.18E+00,
1.69E+00,
1.96E+00,
1.96E+00,
1.69E+00,
1.18E+00,
4.97E-01,
-2.51E-01,
-9.64E-01,
-1.54E+00,
-1.90E+00,
-2.00E+00};

int main(void) {
  low_pass_f filter;
 init_low_pass(&filter);

for (int i = 0; i<47; i++){
  
  
  float out =low_pass_filter(&filter,y[i]);
  printf("input = %f \t Output = %f\n",y[i], out);


}




}
*/ 