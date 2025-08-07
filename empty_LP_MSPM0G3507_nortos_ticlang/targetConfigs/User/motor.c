#include "motor.h"
#include "ti_msp_dl_config.h"

/*暂时定义B左A右 2前1后*/

/*左电机向前*/
void Right_Forward(void)
{
    DL_GPIO_clearPins(Direction_PORT, Direction_BIN1_PIN);
    DL_GPIO_setPins(Direction_PORT, Direction_BIN2_PIN);
}

/*左电机向后*/
void Right_Behind(void)
{
    DL_GPIO_setPins(Direction_PORT, Direction_BIN1_PIN);
    DL_GPIO_clearPins(Direction_PORT, Direction_BIN2_PIN);
}

/*右电机向前*/
void Left_Forward(void)
{
    DL_GPIO_setPins(Direction_PORT, Direction_AIN1_PIN);
    DL_GPIO_clearPins(Direction_PORT, Direction_AIN2_PIN);
}

/*右电机向后*/
void Left_Behind(void)
{
    DL_GPIO_clearPins(Direction_PORT, Direction_AIN1_PIN);
    DL_GPIO_setPins(Direction_PORT, Direction_AIN2_PIN);
}

void Moving_Forward(int left_speed, int right_speed)
{
    Left_Forward();
    Right_Forward();
    /*速度设置*/
    DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,left_speed,GPIO_PWM_MOTOR_C0_IDX);//PWMA    
    DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,right_speed,GPIO_PWM_MOTOR_C1_IDX);//PWMB
}

/*预留方案：左电机不动 右电机向前*/
void Moving_Left(int left_speed, int right_speed)
{
    Left_Behind();
    Right_Forward();
    /*速度设置*/
    DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,left_speed,GPIO_PWM_MOTOR_C0_IDX);//PWMA    
    DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,right_speed,GPIO_PWM_MOTOR_C1_IDX);//PWMB
}

void Moving_Right(int left_speed, int right_speed)
{
    Left_Forward();
    Right_Behind();
    /*速度设置*/
    DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,left_speed,GPIO_PWM_MOTOR_C0_IDX);//PWMA    
    DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,right_speed,GPIO_PWM_MOTOR_C1_IDX);//PWMB
}

/*预防出线*/
void Moving_Behind(int left_speed, int right_speed)
{
    Left_Behind();
    Right_Behind();
    /*速度设置*/
    DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,left_speed,GPIO_PWM_MOTOR_C0_IDX);//PWMA    
    DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,right_speed,GPIO_PWM_MOTOR_C1_IDX);//PWMB
}

/*右电机不动*/
void Left_Stay(void)
{
    DL_GPIO_clearPins(Direction_PORT, Direction_AIN1_PIN);
    DL_GPIO_clearPins(Direction_PORT, Direction_AIN2_PIN);
    DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,0,GPIO_PWM_MOTOR_C0_IDX);//PWMA    
    DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,0,GPIO_PWM_MOTOR_C1_IDX);//PWMB
}

/*左电机不动*/
void Right_Stay(void)
{
    DL_GPIO_clearPins(Direction_PORT, Direction_BIN1_PIN);
    DL_GPIO_clearPins(Direction_PORT, Direction_BIN2_PIN);
    DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,0,GPIO_PWM_MOTOR_C0_IDX);//PWMA    
    DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,0,GPIO_PWM_MOTOR_C1_IDX);//PWMB
}