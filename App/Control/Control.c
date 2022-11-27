#include "Control.h"
#include "Motor.h"
#include "Relay.h"
#include "Water_Level_Sensor.h"
#include "Menu.h"
#include "Flash_data.h"

#define AUTO_WASHING_TIME		1		// in minute

CONTROL_DATA_t CONTROL_Data;

static uint16_t __last_drum_state = 0;
static uint16_t __last_pool_state = 0;
static uint32_t __auto_mode_timer = 0;
static uint32_t	__counter_timer = 0;
static uint8_t __relay_mask = 0x00;

// Level of drum sensors group
enum{
	WLS1_LEVEL_0		= 0x01,
	WLS1_LEVEL_1		= 0x02,
	WLS1_LEVEL_2		= 0x04,
	WLS1_LEVEL_3		= 0x08,
};

// Level of pool sensors group
enum{
	WLS2_LEVEL_0		= 0x10,
	WLS2_LEVEL_1		= 0x20,
};

static void error_behavior(){
	switch(CONTROL_Data.error_runnign_state){
		case ERROR_IDLE_STATE:
		{
			MOTOR_Set_State(MOTOR_OFF);
			RELAY_Set_State(TURN_OFF_ALL);
			uint32_t t_time = (HAL_GetTick() - __auto_mode_timer) / 60000;
			if(t_time >= FLASH_DATA_Get_Current_Data().washing_cycle / 2){
				CONTROL_Data.error_runnign_state = ERROR_WASHING_STATE;
				__auto_mode_timer = HAL_GetTick();
			}
			break;
		}
		case ERROR_WASHING_STATE:
		{
			MOTOR_Set_State(MOTOR_ON);
			RELAY_Set_State(TURN_ON_RELAY_1);
			uint32_t t_time = HAL_GetTick() - __auto_mode_timer;
			if(t_time > FLASH_DATA_Get_Current_Data().washing_time * 1000){
				CONTROL_Data.error_runnign_state = ERROR_IDLE_STATE;
				__auto_mode_timer = HAL_GetTick();
			}
			break;
		}
		default:
			break;
	}

}

void WLS1_Control(){
	uint8_t t_value_mask = WLS_Value();
	if(HAL_GetTick() > 3000){
		if((t_value_mask & WLS1_LEVEL_0) != 0){
			CONTROL_Data.drum_control_state = DRUM_HIGH_WATER_STATE;
		} else if((t_value_mask & WLS1_LEVEL_1) != 0){
			CONTROL_Data.drum_control_state = DRUM_NORMAL_STATE;
		} else if((t_value_mask & WLS1_LEVEL_2) != 0){
			if(__last_drum_state == DRUM_NORMAL_STATE){
				CONTROL_Data.drum_control_state = DRUM_WASHING_STATE;
				__counter_timer = HAL_GetTick();
				FLASH_DATA_t t_data = FLASH_DATA_Get_Current_Data();
				t_data.washing_cycle = (HAL_GetTick() - __counter_timer) / 60;
				FLASH_DATA_Update(&t_data);
			}
		} else if((t_value_mask & WLS1_LEVEL_3) != 0){
			if(__last_drum_state == DRUM_WASHING_STATE){
				CONTROL_Data.drum_control_state = DRUM_LOW_WATER_STATE;
			}
		} else{
			CONTROL_Data.drum_control_state = DRUM_ERROR_STATE;
		}
		if(CONTROL_Data.drum_control_state != __last_drum_state){
			MENU_Data.changed = 0;
			__last_drum_state = CONTROL_Data.drum_control_state;
		}
	}
}

void WLS2_Control(){
	uint8_t t_value_mask = WLS_Value();
	if(HAL_GetTick() > 3000){
		if((t_value_mask & WLS2_LEVEL_0) != 0){
			CONTROL_Data.pool_control_state = POOL_NORMAL_STATE;
		} else if((t_value_mask & WLS2_LEVEL_1) != 0){
			;
		} else{
			CONTROL_Data.pool_control_state = POOL_LOW_WATER_STATE;
		}
	}
	if(CONTROL_Data.pool_control_state != __last_pool_state){
		MENU_Data.changed = 0;
		__last_pool_state = CONTROL_Data.pool_control_state;
	}
}

void CONTRL_Init(){
	CONTROL_Data.drum_control_state = DRUM_NORMAL_STATE;
	CONTROL_Data.pool_control_state = POOL_NORMAL_STATE;
	__last_drum_state = DRUM_NORMAL_STATE;
	__last_pool_state = POOL_NORMAL_STATE;

	MOTOR_Init(MOTOR_OFF);
	RELAY_Init();
	WLS_Init();

	FLASH_DATA_Init();
}

void CONTROL_Handle(){
	MOTOR_Handle();
	RELAY_Handle();
	WLS_Handle();
	WLS1_Control();
	WLS2_Control();
	switch(CONTROL_Data.drum_control_state){
		case DRUM_HIGH_WATER_STATE:
			MOTOR_Set_State(MOTOR_OFF);
			RELAY_Set_State(TURN_OFF_ALL);
			break;
		case DRUM_NORMAL_STATE:
			MOTOR_Set_State(MOTOR_OFF);
			RELAY_Set_State(TURN_ON_RELAY_2);
			break;
		case DRUM_WASHING_STATE:
			MOTOR_Set_State(MOTOR_ON);
			RELAY_Set_State(TURN_ON_RELAY_1 | TURN_ON_RELAY_2);
			break;
		case DRUM_LOW_WATER_STATE:
			MOTOR_Set_State(MOTOR_OFF);
			RELAY_Set_State(TURN_ON_RELAY_2 | TURN_ON_RELAY_3 | TURN_ON_RELAY_4);
			break;
		case DRUM_ERROR_STATE:
			error_behavior();
			break;
		default:
			break;
	}

	switch(CONTROL_Data.pool_control_state){
		case POOL_NORMAL_STATE:
			RELAY_Set_State(RELAY_Current_Relay_Mask() & ~(TURN_ON_RELAY_5));
			break;
		case POOL_LOW_WATER_STATE:
			RELAY_Set_State(RELAY_Current_Relay_Mask() | TURN_ON_RELAY_5);
			break;
	}

	if(RELAY_Current_Relay_Mask() != __relay_mask){
		MENU_Data.changed = 0;
		__relay_mask = RELAY_Current_Relay_Mask();
	}

}
