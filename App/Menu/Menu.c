#include "Menu.h"

extern I2C_HandleTypeDef hi2c2;

MENU_DATA_t MENU_Data;
static LCD_I2C_HandleTypeDef hlcd;

void MENU_Init(){
	MENU_Data.state = MAIN_MENU;
	MENU_Data.changed = 0;
	MENU_Data.is_changing_menu = 1;
	MENU_Data.hlcd = &hlcd;
	LCD_Init(&hlcd, &hi2c2, 20, 4, 0x4E);

	MAIN_MENU_Init();
}

void MENU_Handle(){
	if(!MENU_Data.changed){
		switch(MENU_Data.state){
			case MAIN_MENU:
				MAIN_MENU_Display();
				MENU_Data.changed = 1;
				break;
			case SETTING_MENU:
				SETTING_MENU_Display();
				MENU_Data.changed = 1;
				break;
			default:
				break;
		}
	}
}
