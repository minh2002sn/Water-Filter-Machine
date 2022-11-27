#ifndef WATER_LEVEL_SENSOR_H
#define WATER_LEVEL_SENSOR_H

#include "main.h"

typedef struct{
	uint8_t Sensor_Current_State;
	uint8_t Sensor_Last_State;
	uint8_t Sensor_Filter_State;
	uint8_t is_debouncing;
	uint32_t time_debounce;
	GPIO_TypeDef *Sensor_Port;
	uint16_t Sensor_Pin;
} WLS_HandleTypedef;

void WLS_Handle();
void WLS_Init();
uint8_t WLS_Value();

#endif
