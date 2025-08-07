/*Include*/
#include "track.h"
#include "motor.h"
#include "ti_msp_dl_config.h"
#include <stdint.h>
/*PV*/
int Data[8];
uint8_t Track_Data;
int target_speed = 1;
/*调参区*/
float left_kp = 0.1f;
float left_ki = 0.001f;
float left_kd = 0.01f;
float right_kp = 0.1f;
float right_ki = 0.001f;
float right_kd = 0.01f;
/*调参区*/
/*八路循迹  探测到黑线输出高电平  探测到白为低电平  白0黑1*/
void Track_Read(void)
{
    Data[0] = ((DL_GPIO_readPins(INPUTA_PORT, INPUTA_IN1_PIN)==INPUTA_IN1_PIN)?1:0);
    Data[1] = ((DL_GPIO_readPins(INPUTA_PORT, INPUTA_IN2_PIN)==INPUTA_IN2_PIN)?1:0);
    Data[2] = ((DL_GPIO_readPins(INPUTB_PORT, INPUTB_IN3_PIN)==INPUTB_IN3_PIN)?1:0);
    Data[3] = ((DL_GPIO_readPins(INPUTB_PORT, INPUTB_IN4_PIN)==INPUTB_IN4_PIN)?1:0);
    Data[4] = ((DL_GPIO_readPins(INPUTA_PORT, INPUTA_IN5_PIN)==INPUTA_IN5_PIN)?1:0);
    Data[5] = ((DL_GPIO_readPins(INPUTB_PORT, INPUTB_IN6_PIN)==INPUTB_IN6_PIN)?1:0);
    Data[6] = ((DL_GPIO_readPins(INPUTB_PORT, INPUTB_IN7_PIN)==INPUTB_IN7_PIN)?1:0);
    Data[7] = ((DL_GPIO_readPins(INPUTB_PORT, INPUTB_IN8_PIN)==INPUTB_IN8_PIN)?1:0);
    Track_Data = (Data[7]<<7)|(Data[6]<<6)|(Data[5]<<5)|(Data[4]<<4)|(Data[3]<<3)|(Data[2]<<2)|(Data[1]<<1)|Data[0];
}

void Track_Task(void)
{
    pid_init(&left_pid, left_kp, left_ki, left_kd);
    pid_init(&right_pid, right_kp, right_ki, right_kd);
    /*拧电位器用 静止不动*/
    if(Track_Data == 0x00 || Track_Data == 0xFF)
    {
        Left_Stay();
        Right_Stay();
        return;
    }
    /*左转*/
    if(Turn(Track_Data))
    {
        Moving_Left(500, 500);
        Moving_Left(500, 500);
        Moving_Left(500, 500);
        Moving_Left(500, 500);
        Moving_Left(500, 500);
        Moving_Left(500, 500);
        Moving_Left(500, 500);
        Moving_Left(500, 500);
        Moving_Left(500, 500);
        return;
    }
    float position_error = calculate_position_error(Track_Data);  // 计算位置偏差
    float steering_adjust = position_error * 1.0f + error1 * 1.0f;  // 转向调整量
    /*中心巡线*/
    //更新PID（目标速度±转向调整）
    pid_calculate(&left_pid, target_speed + steering_adjust, left_encoder.speed);
    pid_calculate(&right_pid, target_speed - steering_adjust, right_encoder.speed);
    Moving_Forward((int)left_pid.out, (int)right_pid.out);
}

//判断左转的灵活条件（允许部分传感器触发）
bool Turn(uint8_t sensor_data)
{
    // 方法1：至少连续2个最左侧传感器触发
    if ((sensor_data & 0xC0) == 0xC0) return true;  // 最左2个（bit6+bit7）
    // 方法2：加权判断（推荐）
    uint8_t left_sensors = (sensor_data & 0xE0) >> 5;  // 提取bit5-7
    uint8_t right_sensors = sensor_data & 0x07;        // 提取bit0-2
    return (__builtin_popcount(left_sensors) > __builtin_popcount(right_sensors) + 1);
}

// 计算位置偏差（-3.5~+3.5，左负右正）
float calculate_position_error(uint8_t sensors)
{
    float weighted_sum = 0;
    uint8_t active_count = 0;
    
    for (uint8_t i = 0; i < 8; i++)
    {
        if (sensors & (1 << i))
        {
            weighted_sum += (i - 3.5f);  // 中心对称加权
            active_count++;
        }
    }
    //权重补偿
    if (active_count == 1)
    {
        weighted_sum *= 2.0f;  // 增强单个传感器的权重
    }
    return (active_count > 0) ? (weighted_sum / active_count) : 0;
}