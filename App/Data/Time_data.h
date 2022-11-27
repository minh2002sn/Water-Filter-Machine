#ifndef TIME_DATA_H
#define TIME_DATA_H

#include "stdint.h"

typedef struct{
	uint16_t washing_cycle;
	uint16_t washing_time;
} __attribute__((packed)) TIME_DATA_t;

#endif
