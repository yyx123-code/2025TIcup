/*Include*/
#include "ti_msp_dl_config.h"
#include "motor.h"
#include "track.h"
#include "encoder.h"
#include "pid.h"
#include "key.h"
int flag = 1;
int main(void)
{
    /*Init*/
    SYSCFG_DL_init();
    Encoder_Init();
    while (1)
    {
        /*Infinite Loop*/
        Key_Read();//只读取一次
        Track_Read();//读取循迹
        Track_Task();//循迹
    }
}
