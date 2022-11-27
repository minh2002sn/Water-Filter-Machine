#include "Menu.h"
#include "Setting_menu.h"

SETTING_MENU_DATA_t SETTING_MENU_Data;

void SETTING_MENU_Init(){

}

void SETTING_MENU_Set_State(){
	MENU_Data.state = SETTING_MENU;
	MENU_Data.changed = 0;
	MENU_Data.is_changing_menu = 1;
	SETTING_MENU_Data.setting_state = NON_SETTING;
	SETTING_MENU_Data.new_flash_data = FLASH_DATA_Get_Current_Data();
	SETTING_MENU_Data.new_realtime = REALTIME_Data;
	SETTING_MENU_Data.pointer_position = 0;
}

void SETTING_MENU_Choose_Setting_State(SETTING_STATE_t p_new_setting_state){
	SETTING_MENU_Data.setting_state = p_new_setting_state;
	SETTING_MENU_Data.pointer_position = 0;
	MENU_Data.changed = 0;
}

void SETTING_MENU_Keypad_Input(uint8_t p_key){
	if(p_key == '#'){
		if(SETTING_MENU_Data.setting_state == NON_SETTING){
			return;
		}
		if(SETTING_MENU_Data.setting_state == SETTING_HOUR){
			SETTING_MENU_Data.setting_state = SETTING_MINUTE;
			SETTING_MENU_Data.pointer_position = 0;
		} else if(SETTING_MENU_Data.setting_state == SETTING_WASHING_TIME){
			if(SETTING_MENU_Data.new_flash_data.washing_time < MIN_WASHING_TIME){
				SETTING_MENU_Data.new_flash_data.washing_time = MIN_WASHING_TIME;
			} else{
				FLASH_DATA_Update(&SETTING_MENU_Data.new_flash_data);
				SETTING_MENU_Set_State();
				return;
			}
		} else{
			if(SETTING_MENU_Data.setting_state == NON_SETTING){
				MAIN_MENU_Set_State();
			} else if(SETTING_MENU_Data.setting_state == SETTING_MINUTE){
				REALTIME_Set_New_Realtime(&SETTING_MENU_Data.new_realtime);
			} else if(SETTING_MENU_Data.setting_state == SETTING_SENSOR_NORMAL_STATE){
				FLASH_DATA_Update(&SETTING_MENU_Data.new_flash_data);
			}
			SETTING_MENU_Set_State();
			return;
		}
	} else if(p_key == '*'){
		if(SETTING_MENU_Data.setting_state == NON_SETTING){
			MAIN_MENU_Set_State();
			return;
		}
		if(SETTING_MENU_Data.setting_state == SETTING_MINUTE){
			SETTING_MENU_Data.setting_state = SETTING_HOUR;
			SETTING_MENU_Data.pointer_position = 0;
		} else{
			SETTING_MENU_Set_State();
			return;
		}
	} else if(p_key >= '0' && p_key <= '9'){
		if(SETTING_MENU_Data.setting_state == NON_SETTING){
			if(p_key == '1'){
				SETTING_MENU_Data.setting_state = SETTING_HOUR;
			} else if(p_key == '2'){
				SETTING_MENU_Data.setting_state = SETTING_WASHING_TIME;
			} else if(p_key == '3'){
				SETTING_MENU_Data.setting_state = SETTING_SENSOR_NORMAL_STATE;
			}
		} else if(SETTING_MENU_Data.setting_state == SETTING_HOUR ||
		SETTING_MENU_Data.setting_state == SETTING_MINUTE){
			uint8_t *t_data = (uint8_t *)(&SETTING_MENU_Data.new_realtime) + (SETTING_MENU_Data.setting_state - 1);
			if(SETTING_MENU_Data.pointer_position == 0){
				*t_data = ((*t_data) % 10) + (p_key - '0') * 10;
				SETTING_MENU_Data.pointer_position = 1;
			} else{
				*t_data = ((*t_data) / 10 * 10) + (p_key - '0');
				SETTING_MENU_Data.pointer_position = 0;
			}
			if(SETTING_MENU_Data.setting_state == SETTING_HOUR && *t_data > 23){
				*t_data = 23;
			} else if(SETTING_MENU_Data.setting_state == SETTING_MINUTE && *t_data > 59){
				*t_data = 59;
			}
		} else if(SETTING_MENU_Data.setting_state == SETTING_WASHING_TIME){
			uint8_t t_digit[4];
			t_digit[0] = SETTING_MENU_Data.new_flash_data.washing_time / 1000;
			t_digit[1] = (SETTING_MENU_Data.new_flash_data.washing_time % 1000) / 100;
			t_digit[2] = (SETTING_MENU_Data.new_flash_data.washing_time % 100) / 10;
			t_digit[3] = SETTING_MENU_Data.new_flash_data.washing_time % 10;
			t_digit[SETTING_MENU_Data.pointer_position] = p_key - '0';
			SETTING_MENU_Data.new_flash_data.washing_time = t_digit[0] * 1000 + t_digit[1] * 100 + t_digit[2] * 10 + t_digit[3];
			if(SETTING_MENU_Data.new_flash_data.washing_time < MIN_WASHING_TIME)
				SETTING_MENU_Data.new_flash_data.washing_time = MIN_WASHING_TIME;
			if(SETTING_MENU_Data.new_flash_data.washing_time > MAX_WASHING_TIME)
				SETTING_MENU_Data.new_flash_data.washing_time = MAX_WASHING_TIME;
			if(SETTING_MENU_Data.pointer_position < 3){
				SETTING_MENU_Data.pointer_position++;
			} else{
				SETTING_MENU_Data.pointer_position = 0;
			}
		} else if(SETTING_MENU_Data.setting_state == SETTING_SENSOR_NORMAL_STATE){
			if(p_key == '0' || p_key == '1'){
				SETTING_MENU_Data.new_flash_data.sensor_normal_state = p_key - '0';
			}
		}
	}
	MENU_Data.changed = 0;
}

void SETTING_MENU_Display(){
	if(MENU_Data.is_changing_menu){
		LCD_Clear(MENU_Data.hlcd);
		MENU_Data.is_changing_menu = 0;
	}

	LCD_Set_Cursor(MENU_Data.hlcd, 0, 0);
	LCD_Write(MENU_Data.hlcd, "1.Real-time:%02d:%02d", SETTING_MENU_Data.new_realtime.system_hour, SETTING_MENU_Data.new_realtime.system_minute);

	LCD_Set_Cursor(MENU_Data.hlcd, 0, 1);
	LCD_Write(MENU_Data.hlcd, "2.Washing time:%04ds", SETTING_MENU_Data.new_flash_data.washing_time);

	LCD_Set_Cursor(MENU_Data.hlcd, 0, 2);
	LCD_Write(MENU_Data.hlcd, "3.WLS normal state:%d", SETTING_MENU_Data.new_flash_data.sensor_normal_state);

	LCD_Set_Cursor(MENU_Data.hlcd, 0, 3);
	LCD_Write(MENU_Data.hlcd, "[*]Back     [#]Enter", SETTING_MENU_Data.new_flash_data.sensor_normal_state);

	if(SETTING_MENU_Data.setting_state != NON_SETTING){
		if(SETTING_MENU_Data.setting_state == SETTING_HOUR || SETTING_MENU_Data.setting_state == SETTING_MINUTE){
			LCD_Set_Cursor(MENU_Data.hlcd, 12 + SETTING_MENU_Data.pointer_position + (SETTING_MENU_Data.setting_state - 1) * 3, 0);
		} else if(SETTING_MENU_Data.setting_state == SETTING_WASHING_TIME){
			LCD_Set_Cursor(MENU_Data.hlcd, 15 + SETTING_MENU_Data.pointer_position, 1);
		} else if(SETTING_MENU_Data.setting_state == SETTING_SENSOR_NORMAL_STATE){
			LCD_Set_Cursor(MENU_Data.hlcd, 19, 2);
		}
		LCD_Cursor_Blink(MENU_Data.hlcd);
	} else{
		LCD_Cursor_No_Blink(MENU_Data.hlcd);
	}
}
