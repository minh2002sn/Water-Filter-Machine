#include "Main_menu.h"
#include "real_time.h"
#include "Control.h"
#include "Menu.h"
#include "Relay.h"
#include "Motor.h"

void MAIN_MENU_Init(){

}

void MAIN_MENU_Set_State(){
	MENU_Data.state = MAIN_MENU;
	MENU_Data.changed = 0;
	MENU_Data.is_changing_menu = 1;
}

void MAIN_MENU_Display(){
	if(MENU_Data.is_changing_menu){
		LCD_Clear(MENU_Data.hlcd);
		MENU_Data.is_changing_menu = 0;
	}
	LCD_Cursor_No_Blink(MENU_Data.hlcd);

	LCD_Set_Cursor(MENU_Data.hlcd, 0, 0);
	LCD_Write(MENU_Data.hlcd, "Time: %02d:%02d", REALTIME_Data.system_hour, REALTIME_Data.system_minute);

	LCD_Set_Cursor(MENU_Data.hlcd, 0, 1);
	if(CONTROL_Data.drum_control_state == DRUM_NORMAL_STATE){
		LCD_Write(MENU_Data.hlcd, "WLS1:NoEr  ", CONTROL_Data.drum_control_state);
	} else{
		LCD_Write(MENU_Data.hlcd, "WLS1:Er%1d   ", CONTROL_Data.drum_control_state);
	}

	if(CONTROL_Data.pool_control_state == POOL_NORMAL_STATE){
		LCD_Write(MENU_Data.hlcd, "WLS2:NoEr", CONTROL_Data.pool_control_state);
	} else{
		LCD_Write(MENU_Data.hlcd, "WLS2:Er%1d ", CONTROL_Data.pool_control_state);
	}

	LCD_Set_Cursor(MENU_Data.hlcd, 0, 2);
	LCD_Write(MENU_Data.hlcd, "Motor: ");
	for(int i = 0; i < 5; i++){
		if((RELAY_Current_Relay_Mask() & (1 << i))){
			LCD_Write(MENU_Data.hlcd, "%1d", i + 1);
		} else{
			LCD_Send_Data(MENU_Data.hlcd, 0xFF);
		}
	}

	if(MOTOR_Data.state == MOTOR_ON){
		LCD_Write(MENU_Data.hlcd, "%1d", 6);
	} else{
		LCD_Send_Data(MENU_Data.hlcd, 0xFF);
	}

	LCD_Set_Cursor(MENU_Data.hlcd, 0, 3);
	LCD_Write(MENU_Data.hlcd, " [Press # to set up]");

}
