#ifndef __TRACK_H__
#define __TRACK_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"

uint8_t Track_Read(void);
void Track_Task(uint8_t Data);

#endif
