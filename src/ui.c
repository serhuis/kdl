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
lcd_string strKdl = {
				.pstr = "йдк",
				.x = 0,
				.y = 0,
				.font = FONT_TYPE_10x15,};


lcd_string *MainFrame[] ={&strKdl} ;
