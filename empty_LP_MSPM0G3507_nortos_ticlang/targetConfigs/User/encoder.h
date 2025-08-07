#ifndef __ENCODER_H__
#define __ENCODER_H__
/*Include*/
#include <stdint.h>
#include "pid.h"
/*PD*/
#define MOTOR_GEAR_RATIO    20                                               //减速比1:20
#define ENCODER_PPR         13                                               //编码器线数13PPR
#define QUAD_ENCODING       1                                                //一倍频
#define RADIUS              24                                               //轮子半径24mm
#define PI                  3.14                                             //圆周率
#define LINE                2 * PI * RADIUS                                  //轮子周长
#define PULSE               (MOTOR_GEAR_RATIO * ENCODER_PPR * QUAD_ENCODING) //总脉冲
#define SAMPLE_TIME         0.01                                             //秒        
/*PT*/
typedef struct
{
    uint8_t direction;      //方向
    int32_t count;          //总计数值
    int32_t lastcount;      //上一次计数值
    float speed;            //电机速度
}encoder_t;

void Encoder_Init(void);
void distance(void);

extern encoder_t left_encoder;
extern encoder_t right_encoder;
extern double total_distanceA,total_distanceB,delta_distanceA,delta_distanceB,error1,error2,distance_average;
#endif
