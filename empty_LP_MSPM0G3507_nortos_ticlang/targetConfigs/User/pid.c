/*Include*/
#include "pid.h"
/*PV*/
pid_t left_pid;
pid_t right_pid;
/*PD*/
#define FILTER_ALPHA 0.1f // 滤波系数，取值范围0到1
/*pid参数初始化*/
void pid_init(pid_t *pid, float kp, float ki, float kd)
{
	pid->kp=kp;
	pid->ki=ki;
 	pid->kd=kd;
}
/*速度环*/
void pid_calculate(pid_t *pid,float target,float current)
{
    pid->target_value = target;
	pid->feedback_value = current;
	pid->err[1] = pid->err[0]; //上次误差
	pid->err[0] = pid->target_value - pid->feedback_value; //这次误差
	
	pid->p_out = pid->kp * pid->err[0]; //比例
	pid->i_out += pid->ki * pid->err[0]; //积分

	Limit_Min_Max(pid->i_out, -10, 10);

	pid->d_out = pid->kd * (pid->err[0]-pid->err[1]);  //微分
	pid->out = pid->p_out + pid->i_out + pid->d_out;
	
    Limit_Min_Max(pid->out, -500,500); //输出限幅
	
}
/*限幅函数*/
int16_t Limit_Min_Max(int16_t output_data, int16_t min_limit, int16_t max_limit)
{
    if(output_data < min_limit){return min_limit;}
    else if(output_data > max_limit){return max_limit;}
    else{return output_data;}
}
/*低通滤波*/
static float filter_value = 0;
float Low_Pass_Filter(float new_value)
{
    filter_value = FILTER_ALPHA * new_value + (1 - FILTER_ALPHA) * filter_value;
    return filter_value;
}