#ifndef FLASH_DATA_H
#define FLASH_DATA_H

#include "stdint.h"

#define MIN_WASHING_CYCLE		2						// in minute
#define MAX_WASHING_CYCLE		1440					// in minute
#define MIN_WASHING_TIME		10						// in second
#define MAX_WASHING_TIME		9999					// in second

typedef struct{
	uint32_t washing_cycle;				// in minute
	uint32_t washing_time;				// in second
	uint8_t sensor_normal_state;
} __attribute__((packed)) FLASH_DATA_t;

void FLASH_DATA_Init();
void FLASH_DATA_Update(FLASH_DATA_t *p_new_data);
void FLASH_DATA_Store();
FLASH_DATA_t FLASH_DATA_Get_Current_Data();

#endif
