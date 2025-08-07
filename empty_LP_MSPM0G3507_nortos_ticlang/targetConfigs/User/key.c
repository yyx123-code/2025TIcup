/*Include*/
#include "ti_msp_dl_config.h"
/*PV*/
int Key[3];
uint8_t cycles;
int state = 0;
/*拨码开关拨下接地 返回1*/
void Key_Read(void)
{
    Key[0] = ((DL_GPIO_readPins(KEYA_PORT, KEYA_KEY2_PIN)==INPUTA_IN2_PIN)?1:0);
    Key[1] = ((DL_GPIO_readPins(KEYB_PORT, KEYB_KEY3_PIN)==INPUTB_IN3_PIN)?1:0);
    Key[2] = ((DL_GPIO_readPins(KEYA_PORT, KEYA_KEY4_PIN)==INPUTB_IN4_PIN)?1:0);//启动
    cycles = (Key[2]<<2)|(Key[1]<<1)|Key[0];
}
