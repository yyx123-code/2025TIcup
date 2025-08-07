/*Include*/
#include "encoder.h"
#include "ti_msp_dl_config.h"
#include "key.h"
/*PV*/
encoder_t left_encoder;
encoder_t right_encoder;
double total_distanceA,total_distanceB,delta_distanceA,delta_distanceB,error1,error2,distance_average;
/*初始化*/
void Encoder_Init(void)
{
    /*开启中断和计数*/
    NVIC_EnableIRQ(EncoderLA_INST_INT_IRQN);
    NVIC_EnableIRQ(EncoderRA_INST_INT_IRQN);  
    NVIC_EnableIRQ(Calculate_INST_INT_IRQN);  
    DL_TimerA_startCounter(EncoderLA_INST);
    DL_TimerA_startCounter(EncoderRA_INST);
    DL_TimerG_startCounter(Calculate_INST);
}
/*中断函数 读取+解算速度*/
/*左电机的编码器测速 TIMA1*/
void TIMA1_IRQHandler(void)
{
    switch(DL_TimerA_getPendingInterrupt(EncoderLA_INST))
    {
        case DL_TIMERA_IIDX_CC1_DN:
            left_encoder.direction = ((DL_GPIO_readPins(EncoderB_PORT, EncoderB_L_PIN) == EncoderB_L_PIN)?1:0);
            left_encoder.count = 
                left_encoder.direction ? (left_encoder.count + 1) : (left_encoder.count - 1);//旋转方向决定countnum增or减
            DL_TimerA_clearInterruptStatus(EncoderLA_INST, DL_TIMERA_IIDX_CC1_DN);
            break;
        default:
            break;
    }
}
/*右电机的编码器测速 TIMA0*/
void TIMA0_IRQHandler(void) {
  switch(DL_TimerA_getPendingInterrupt(EncoderRA_INST))
  {
    case DL_TIMERA_IIDX_CC0_DN:
        right_encoder.direction = ((DL_GPIO_readPins(EncoderB_PORT, EncoderB_R_PIN) == EncoderB_R_PIN)?1:0);
        right_encoder.count = 
            right_encoder.direction ? (right_encoder.count + 1) : (right_encoder.count - 1);
        DL_TimerA_clearInterruptStatus(EncoderRA_INST, DL_TIMERA_IIDX_CC0_DN);
        break;
    default:
        break;
  }
}
/*同步解算 TIMG0*/
void TIMG0_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(Calculate_INST))
    {
        case DL_TIMER_IIDX_ZERO:
            /*清理标志位*/
            DL_TimerG_clearInterruptStatus(Calculate_INST,DL_TIMER_IIDX_ZERO);
            /*计算速度前保存当前值*/
            int32_t left_current = left_encoder.count;
            int32_t right_current = right_encoder.count;
            /*计算速度  公式：采样时间内转过脉冲/(一圈脉冲数*采样时间)  单位：m/s*/
            left_encoder.speed=((left_current - left_encoder.lastcount) * LINE) / (PULSE * SAMPLE_TIME);
            right_encoder.speed=((right_current - right_encoder.lastcount) * LINE) / (PULSE * SAMPLE_TIME);
            //独立更新lastcount
            left_encoder.lastcount = left_current;
            right_encoder.lastcount = right_current;
            distance();
            if(distance_average >= 4)
            {
                total_distanceA = 0;
                total_distanceB = 0;
                cycles--;
            }
            break;
        default:
            DL_TimerG_clearInterruptStatus(Calculate_INST,DL_TIMER_IIDX_ZERO);
            break;
    }
}
/*计算路程*/
void distance(void)
{
    delta_distanceA = left_encoder.speed * SAMPLE_TIME;//m
    delta_distanceB = left_encoder.speed * SAMPLE_TIME;
    total_distanceA += delta_distanceA;
    total_distanceB += delta_distanceB;
    if(total_distanceA > 10000.0f){total_distanceA = 0.0f;}
    if(total_distanceB > 10000.0f){total_distanceB = 0.0f;}
    error1 = delta_distanceA - delta_distanceB;//实时路程差
    error2 = total_distanceA - total_distanceB;//累计路程差
    distance_average = (total_distanceA + total_distanceB) / 2;
}
