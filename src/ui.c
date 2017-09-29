//ui.c
#include "ui.h"
#include "uc1601s.h"
#include "i2c.h"
#include "tools.h"

/*
typedef struct __lcd_string
{
	char* pstr;
	uint8_t x;
	uint8_t y;
	font_type font;
}lcd_string;
*/


void LCD_Update (lcd_object** obj, uint8_t cnt)
{
	uint8_t i;
	lcd_object* tempobj = *obj;
	for (i=0; i<cnt; i++)
	{
		if(LCD_STR == (tempobj->objtype))
			LCD_string(tempobj->pstr, tempobj->x, tempobj->y, tempobj->font, INVERSE_TYPE_NOINVERSE);
		else 
			if(LCD_IMG == (tempobj->objtype))
				LCD_image(tempobj->pimg, tempobj->x, tempobj->y, tempobj->width, tempobj->height);
		
		++tempobj;
	}
}
