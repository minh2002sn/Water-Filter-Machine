#ifndef SETTING_MENU_H
#define SETTING_MENU_H

#include "Flash_data.h"
#include "real_time.h"

typedef enum{
	NON_SETTING,
	SETTING_HOUR,
	SETTING_MINUTE,
	SETTING_WASHING_TIME,
	SETTING_SENSOR_NORMAL_STATE,
} SETTING_STATE_t;

typedef struct{
	FLASH_DATA_t new_flash_data;
	REALTIME_DATA_HandleTypeDef new_realtime;
	uint8_t pointer_position;
	SETTING_STATE_t setting_state;
} SETTING_MENU_DATA_t;

void SETTING_MENU_Init();
void SETTING_MENU_Set_State();
void SETTING_MENU_Choose_Setting_State(SETTING_STATE_t p_state);
void SETTING_MENU_Keypad_Input(uint8_t p_key);
void SETTING_MENU_Display();

extern SETTING_MENU_DATA_t SETTING_MENU_Data;

#endif
