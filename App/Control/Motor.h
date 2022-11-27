#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"
#include "stdint.h"

typedef enum{
	MOTOR_OFF,
	MOTOR_ON,
}MOTOR_STATE_HandleTypdeDef;

typedef struct{
	MOTOR_STATE_HandleTypdeDef state;
}MOTOR_DATA_HandleTypeDef;

void MOTOR_Init(MOTOR_STATE_HandleTypdeDef p_move);
void MOTOR_Set_State(MOTOR_STATE_HandleTypdeDef p_state);
void MOTOR_Handle();

extern MOTOR_DATA_HandleTypeDef MOTOR_Data;

#endif
