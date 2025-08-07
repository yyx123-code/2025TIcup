#ifndef __TRACK_H__
#define __TRACK_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "pid.h"
#include "encoder.h"

void Track_Read(void);
void Track_Task(void);
bool Turn(uint8_t sensor_data);
float calculate_position_error(uint8_t sensors);
#endif
