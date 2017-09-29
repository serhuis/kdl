//ui.h

#ifndef __UI_H
#define __UI_H

#include "main.h"
typedef enum __lcd_object_type
{
	LCD_STR = 1,
	LCD_IMG ,
}lcdobj_t;

#pragma anon_unions

typedef union __lcd_object
{
	struct {
		lcdobj_t objtype;
		uint8_t x;
		uint8_t y;
		uint8_t len;
		font_type font;
		char* pstr;
		uint8_t inversion;
	};
	struct{
		lcdobj_t obj_type;
		uint8_t x0;
		uint8_t y0;
		uint8_t width;
		uint8_t height;
		uint8_t* pimg;
		uint8_t inv_img;
	};
}lcd_object;


void LCD_Update (lcd_object* obj[], uint8_t cnt);


#endif
