#define pi 3.1415
#define cut_off_f 1200


typedef struct {
  float prevoutput, Fc ;
} low_pass_f;

float low_pass_filter(low_pass_f *p,float input );
void init_low_pass(low_pass_f *p) ;