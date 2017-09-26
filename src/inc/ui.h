//ui.h

#ifndef __UI_H
#define __UI_H

#include "main.h"

typedef struct __lcd_string
{
	char* pstr;
	uint8_t x;
	uint8_t y;
	font_type font;
}lcd_string;

#endif
