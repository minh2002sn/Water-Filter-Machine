#include "keypad_driver.h"
#include "Menu.h"

void KeypadPressingCallback(uint8_t p_key){
	switch(MENU_Data.state){
		case MAIN_MENU:
			if(p_key == '#'){
				SETTING_MENU_Set_State();
			}
			break;
		case SETTING_MENU:
			if((p_key >= '0' && p_key <= '9') || p_key == '*' || p_key == '#'){
				SETTING_MENU_Keypad_Input(p_key);
			}
			break;
		default:
			break;
	}
}

void KEYPAD_DRIVER_Handle(){
	Keypad_Handle();
}
