#ifndef __PID_H_
#define __PID_H_
/*Include*/
#include <stdint.h>
/*PT*/
typedef struct
{
    float kp;
	float ki;
	float kd;
	
	float target_value;//目标值
	float feedback_value;//返回值
	float err[2];//误差值
	
	float p_out;
	float i_out;
	float d_out;
	float out;
}pid_t;

void pid_init(pid_t *pid, float kp, float ki, float kd);
void pid_calculate(pid_t *pid,float target,float current);
int16_t Limit_Min_Max(int16_t output_data, int16_t min_limit, int16_t max_limit);
float Low_Pass_Filter(float new_value);

extern pid_t left_pid;
extern pid_t right_pid;

#endif
