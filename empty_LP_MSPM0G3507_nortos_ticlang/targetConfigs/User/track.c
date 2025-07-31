#include "track.h"
#include "motor.h"
#include "ti_msp_dl_config.h"
#include <stdint.h>

/*全局变量debug*/
volatile uint8_t Read1;
volatile uint8_t Read2;
volatile uint8_t Read3;
volatile uint8_t Read4;
volatile uint8_t Read5;
volatile uint8_t Read6;
volatile uint8_t Read7;
volatile uint8_t Read8;
volatile uint8_t Data1;
volatile uint8_t Data2;
volatile uint8_t Data3;
volatile uint8_t Data4;
volatile uint8_t Data5;
volatile uint8_t Data6;
volatile uint8_t Data7;
volatile uint8_t Data8;
volatile uint8_t Data;

/*八路循迹  探测到黑线输出低电平  探测到白线为高电平*/
uint8_t Track_Read(void)
{
    Read1 = (DL_GPIO_readPins(INPUTA_PORT, INPUTA_IN1_PIN))&INPUTA_IN1_PIN;
    Read2 = (DL_GPIO_readPins(INPUTA_PORT, INPUTA_IN2_PIN))&INPUTA_IN2_PIN;
    Read3 = (DL_GPIO_readPins(INPUTB_PORT, INPUTB_IN3_PIN))&INPUTB_IN3_PIN;
    Read4 = (DL_GPIO_readPins(INPUTB_PORT, INPUTB_IN4_PIN))&INPUTB_IN4_PIN;
    Read5 = (DL_GPIO_readPins(INPUTA_PORT, INPUTA_IN5_PIN))&INPUTA_IN5_PIN;
    Read6 = (DL_GPIO_readPins(INPUTB_PORT, INPUTB_IN6_PIN))&INPUTB_IN6_PIN;
    Read7 = (DL_GPIO_readPins(INPUTB_PORT, INPUTB_IN7_PIN))&INPUTB_IN7_PIN;
    Read8 = (DL_GPIO_readPins(INPUTB_PORT, INPUTB_IN8_PIN))&INPUTB_IN8_PIN;
    if(Read1){Data1=0x80;}
    if(Read2){Data2=0x40;}
    if(Read3){Data3=0x20;}
    if(Read4){Data4=0x10;}
    if(Read5){Data5=0x08;}
    if(Read6){Data6=0x04;}
    if(Read7){Data7=0x02;}
    if(Read8){Data8=0x01;}
    Data = Data1|Data2|Data3|Data4|Data5|Data6|Data7|Data8;
    return Data;
}

void Track_Task(uint8_t Data)
{
    switch(Data)
    {
        case 0x18://0001 1000
        {
            Moving_Forward(500,500);
        }break;
        case 0x10://0001 0000
        {
            Moving_Forward(510,490);
        }break;
        case 0x30://0011 0000
        {
            Moving_Forward(515,485);
        }break;
        case 0x20://0010 0000
        {
            Moving_Forward(520,480);
        }break;
        case 0x60://0110 0000
        {
            Moving_Forward(525,475);
        }break;
        case 0x40://0100 0000
        {
            Moving_Forward(530,470);
        }break;
        case 0xC0://1100 0000
        {
            Moving_Forward(550,450);
        }break;
        case 0x80://1000 0000
        {
            Moving_Forward(600,400);
        }break;
        case 0x08://0000 1000
        {
            Moving_Forward(490,510);
        }break;
        case 0x0C://0000 1100
        {
            Moving_Forward(485,515);
        }break;
        case 0x04://0000 0100
        {
            Moving_Forward(480,520);
        }break;
        case 0x06://0000 0110
        {
            Moving_Forward(475,525);
        }break;
        case 0x02://0000 0010
        {
            Moving_Forward(470,530);
        }break;
        case 0x03://0000 0011
        {
            Moving_Forward(450,550);
        }break;
        case 0x01://0000 0001
        {
            Moving_Forward(400, 600);
        }break;
        default:
         {Moving_Forward(500, 500);}break;
    }
    if(Data == 0xF8 || Data == 0xF0 || Data == 0xE0)
    {
        /*左转调参*/
        Moving_Left(200,200);
    }
    if(Data == 0x1F || Data == 0x0F || Data == 0x07)
    {
        /*右转调参*/
        Moving_Right(200,200);
    }
    else{Moving_Forward(500, 500);}
}