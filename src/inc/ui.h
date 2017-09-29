//ui.h

#ifndef __UI_H
#define __UI_H

#include "main.h"
typedef enum __lcd_object_type
{
	LCD_STR = 1,
	LCD_IMG = 2,
}lcdobj_t;

typedef struct __lcd_string
{
	lcdobj_t objtype;
	uint8_t x;
	uint8_t y;
	uint8_t len;
	font_type font;
	char* pstr;
}lcd_string;

typedef struct __lcd_img
{
	lcdobj_t objtype;
	uint8_t x;
	uint8_t y;
	uint8_t width;
	uint8_t height;
	uint8_t* pimg;
}lcd_img;

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
	};
	struct{
		lcdobj_t obj_type;
		uint8_t x0;
		uint8_t y0;
		uint8_t width;
		uint8_t height;
		uint8_t* pimg;
	};
}lcd_object;


void LCD_Update (lcd_object** obj, uint8_t cnt);


#endif
