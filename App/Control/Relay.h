#ifndef CONTACTOR_H
#define CONTACTOR_H

#include "main.h"
#include "stdint.h"

enum{
	TURN_OFF_ALL	=	0x00,
	TURN_ON_RELAY_1	=	0x01,	// washing motor
	TURN_ON_RELAY_2	=	0x02,	// 1st pumping water from drum to pool motor
	TURN_ON_RELAY_3	=	0x04,	// 2nd pumping water from drum to pool motor
	TURN_ON_RELAY_4	=	0x08,	// 3rd pumping water from drum to pool motor
	TURN_ON_RELAY_5	=	0x10,	// pumping water to machine motor
	TURN_ON_ALL		=	0xFF,
};

typedef struct{
	uint8_t relay_mask;
} RELAY_DATA_HandleTypeDef;

void RELAY_Init();
void RELAY_Set_State(uint8_t p_relay_mask);
uint8_t RELAY_Current_Relay_Mask();
void RELAY_Handle();

#endif
