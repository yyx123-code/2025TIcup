/*Include*/
#include "ti_msp_dl_config.h"
#include "motor.h"
#include "track.h"
/*PV*/
uint8_t Data;
/*PD*/
#define SPEED_MAX 1000
#define SPEED_MEDIUM 500
#define SPEED_MIN 0

int main(void)
{
    /*Init*/
    SYSCFG_DL_init();

    while (1)
    {
        /*Infinite Loop*/
        Data = Track_Read();
        Track_Task(Data);
    }
}
