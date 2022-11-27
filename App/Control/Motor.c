#include "Motor.h"

MOTOR_DATA_HandleTypeDef MOTOR_Data;

void MOTOR_Init(MOTOR_STATE_HandleTypdeDef p_move){
	MOTOR_Data.state = MOTOR_OFF;
}

void MOTOR_Set_State(MOTOR_STATE_HandleTypdeDef p_state){
	MOTOR_Data.state = p_state;
}

void MOTOR_Handle(){
	if(MOTOR_Data.state == MOTOR_ON){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	} else{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
	}
}
