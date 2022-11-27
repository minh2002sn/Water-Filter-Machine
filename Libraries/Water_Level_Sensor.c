#include "Water_Level_Sensor.h"
#include "Flash_data.h"

#define DEBOUNCING_TIME			2000

#define NUMBER_OF_SENSOR		6

#define V_PLUS_PORT				GPIOA
#define V_PLUS_PIN				GPIO_PIN_0
#define V_MINUS_PORT			GPIOA
#define V_MINUS_PIN				GPIO_PIN_1

//========== btn func ==========//

static uint8_t __sensor_normal_state = 0;
static WLS_HandleTypedef __wls_sensor[NUMBER_OF_SENSOR] = {
		{0, 0, 0, 0, 0, GPIOA, GPIO_PIN_2},
		{0, 0, 0, 0, 0, GPIOA, GPIO_PIN_3},
		{0, 0, 0, 0, 0, GPIOA, GPIO_PIN_4},
		{0, 0, 0, 0, 0, GPIOA, GPIO_PIN_5},
		{0, 0, 0, 0, 0, GPIOA, GPIO_PIN_6},
		{0, 0, 0, 0, 0, GPIOA, GPIO_PIN_7},
};
static uint8_t __sensor_value_mask;

void WLS_Handle(){
	if(__sensor_normal_state != FLASH_DATA_Get_Current_Data().sensor_normal_state){
		__sensor_normal_state = FLASH_DATA_Get_Current_Data().sensor_normal_state;
		for(int i = 0; i < NUMBER_OF_SENSOR; i++){
			__wls_sensor[i].Sensor_Current_State = __sensor_normal_state;
			__wls_sensor[i].Sensor_Last_State = __sensor_normal_state;
			__wls_sensor[i].Sensor_Filter_State = __sensor_normal_state;
		}
	}
	for(int i = 0; i < 6; i++){
		// Read current logic level
		uint8_t state = HAL_GPIO_ReadPin(__wls_sensor[i].Sensor_Port, __wls_sensor[i].Sensor_Pin);
		if(state != __wls_sensor[i].Sensor_Filter_State){
			__wls_sensor[i].Sensor_Filter_State = state;
			__wls_sensor[i].is_debouncing = 1;
			__wls_sensor[i].time_debounce = HAL_GetTick();
		}

		if(__wls_sensor[i].is_debouncing && (HAL_GetTick() - __wls_sensor[i].time_debounce >= DEBOUNCING_TIME)){
			__wls_sensor[i].Sensor_Current_State = __wls_sensor[i].Sensor_Filter_State;
			__wls_sensor[i].is_debouncing = 0;
		}

		if(__wls_sensor[i].Sensor_Current_State != __wls_sensor[i].Sensor_Last_State){
			if(__wls_sensor[i].Sensor_Current_State == !__sensor_normal_state)
				__sensor_value_mask |= 1U << i;
			else
				__sensor_value_mask &= ~(1U << i);
			__wls_sensor[i].Sensor_Last_State = __wls_sensor[i].Sensor_Current_State;
		}
	}
}

void WLS_Init(){
	__sensor_value_mask = 0x00;
	HAL_GPIO_WritePin(V_PLUS_PORT, V_PLUS_PIN, 1);
	HAL_GPIO_WritePin(V_MINUS_PORT, V_MINUS_PIN, 0);
}

uint8_t WLS_Value(){
	return __sensor_value_mask;
}
