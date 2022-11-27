#include "Flash_data.h"
#include "flash.h"

#define DATA_FRAME_SIZE_BYTE 	(sizeof(FLASH_DATA_t))	// in byte

FLASH_DATA_t FLASH_Data;

void FLASH_DATA_Init(){
	uint8_t t_data[DATA_FRAME_SIZE_BYTE];
	FLASH_Read(FIRST_PAGE_ADD + BYTE_PER_PAGE * 63, t_data, DATA_FRAME_SIZE_BYTE);
	FLASH_Data = *(FLASH_DATA_t *)t_data;
	if(FLASH_Data.washing_time < MIN_WASHING_TIME || FLASH_Data.washing_time > MAX_WASHING_TIME ||
		FLASH_Data.washing_cycle < MIN_WASHING_CYCLE || FLASH_Data.washing_cycle > MAX_WASHING_CYCLE ||
		FLASH_Data.sensor_normal_state > 1){
		if(FLASH_Data.washing_time < MIN_WASHING_TIME || FLASH_Data.washing_time > MAX_WASHING_TIME){
			FLASH_Data.washing_time = MIN_WASHING_TIME;
		}
		if(FLASH_Data.washing_cycle < MIN_WASHING_CYCLE || FLASH_Data.washing_cycle > MAX_WASHING_CYCLE){
			FLASH_Data.washing_cycle = MIN_WASHING_CYCLE;
		}
		if(FLASH_Data.sensor_normal_state > 1){
			FLASH_Data.sensor_normal_state = 0;
		}
		FLASH_DATA_Store();
	}
}

void FLASH_DATA_Update(FLASH_DATA_t *p_new_data){
	FLASH_Data = *p_new_data;
	if(p_new_data->washing_time < MIN_WASHING_TIME){
		FLASH_Data.washing_time = MIN_WASHING_TIME;
	} else if(p_new_data->washing_time > MAX_WASHING_TIME){
		FLASH_Data.washing_time = MAX_WASHING_TIME;
	}
	if(FLASH_Data.washing_cycle < MIN_WASHING_CYCLE){
		FLASH_Data.washing_cycle = MIN_WASHING_CYCLE;
	} else if(FLASH_Data.washing_cycle > MAX_WASHING_CYCLE){
		FLASH_Data.washing_cycle = MAX_WASHING_CYCLE;
	}
	FLASH_DATA_Store();
}

void FLASH_DATA_Store(){
	FLASH_Write(63, (uint8_t *)(&FLASH_Data), DATA_FRAME_SIZE_BYTE);
}

FLASH_DATA_t FLASH_DATA_Get_Current_Data(){
	return FLASH_Data;
}
