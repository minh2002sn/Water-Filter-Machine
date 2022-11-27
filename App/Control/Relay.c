#include "Relay.h"

#define NUM_OF_RELAY			5

RELAY_DATA_HandleTypeDef RELAY_Data;

static GPIO_TypeDef *RELAY_Port[NUM_OF_RELAY] = {GPIOB, GPIOB, GPIOB, GPIOB, GPIOB};
static uint16_t RELAY_Pin[NUM_OF_RELAY] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_10,
#ifdef __STM32F0xx_HAL_H
		GPIO_PIN_11
#endif
#ifdef __STM32F1xx_HAL_H
		GPIO_PIN_11
#endif
#ifdef __STM32F4xx_HAL_H
		GPIO_PIN_9
#endif
};

void RELAY_Init(){
	RELAY_Data.relay_mask = 0x00;
}

void RELAY_Set_State(uint8_t p_relay_mask){
	RELAY_Data.relay_mask = p_relay_mask;
}

uint8_t RELAY_Current_Relay_Mask(){
	return RELAY_Data.relay_mask;
}

void RELAY_Handle(){
	for(int i = 0; i < NUM_OF_RELAY; i++){
		uint8_t t_relay_state = (RELAY_Data.relay_mask & (0x01 << i)) ? 1 : 0;
		HAL_GPIO_WritePin(RELAY_Port[i], RELAY_Pin[i], t_relay_state);
	}
}
