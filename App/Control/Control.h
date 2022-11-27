#ifndef CONTROL_H
#define CONTROL_H

#include "stdint.h"

typedef enum{
	DRUM_NORMAL_STATE,
	DRUM_HIGH_WATER_STATE,
	DRUM_WASHING_STATE,
	DRUM_LOW_WATER_STATE,
	DRUM_ERROR_STATE,
} DRUM_CONTROLING_STATE_t;

typedef enum{
	POOL_NORMAL_STATE,
	POOL_LOW_WATER_STATE,
} POOL_CONTROLING_STATE_t;

typedef enum{
	ERROR_IDLE_STATE,
	ERROR_WASHING_STATE,
} ERROR_RUNNING_STATE_t;

typedef struct{
	DRUM_CONTROLING_STATE_t drum_control_state;
	POOL_CONTROLING_STATE_t pool_control_state;
	ERROR_RUNNING_STATE_t error_runnign_state;
	uint32_t washing_cycle;
} CONTROL_DATA_t;

void CONTRL_Init();
void CONTROL_Handle();

extern CONTROL_DATA_t CONTROL_Data;

#endif
