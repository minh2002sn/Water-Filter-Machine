#ifndef MENU_H
#define MENU_H

#include "stdint.h"
#include "LCD_I2C.h"
#include "Main_menu.h"
#include "Setting_menu.h"

typedef enum{
	MAIN_MENU,
	SETTING_MENU,
} MENU_STATE_t;

typedef struct{
	MENU_STATE_t state;
	uint8_t changed;
	uint8_t is_changing_menu;
	LCD_I2C_HandleTypeDef *hlcd;
} MENU_DATA_t;

void MENU_Init();
void MENU_Handle();

extern MENU_DATA_t MENU_Data;

#endif
