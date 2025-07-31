#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <stdint.h>

void Left_Forward(void);
void Left_Stay(void);
void Left_Behind(void);

void Right_Forward(void);
void Right_Stay(void);
void Right_Behind(void);

void Moving_Forward(int left_speed, int right_speed);
void Moving_Left(int left_speed, int right_speed);
void Moving_Right(int left_speed, int right_speed);
void Moving_Behind(int left_speed, int right_speed);

#endif
