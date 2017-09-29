//#include "stm32f10x.h"

#include <stdio.h>
#include "cmsis_os.h"

#include "main.h"

#include "inc/uc1601s.h"
#include "ui.h"

uint8_t i = 0;

void Thread_LCD(void const *pvParameters);

osThreadDef(Thread_LCD, osPriorityNormal, 1, 0);

int Init_Thread (void) {

	osThreadId tid_Thread_LCD;
  
	tid_Thread_LCD = osThreadCreate (osThread(Thread_LCD), NULL);
  if(!tid_Thread_LCD) return(-1);
	
  return(0);
}

//Variable strings
char str[50] = "";
char strCurMode[10] = "��������";
const char strSensVal[10] = "1,5 ��";




//images 
uint8_t AR [] = {0
};

//LCD "objects"
const lcd_object strcnt = {.objtype = LCD_STR, .pstr = str, .x = 0, .y = 23, .font = FONT_TYPE_10x8};
const lcd_object strmode = {.objtype = LCD_STR, .pstr = "�����:", .x = 0, .y = 25, .font = FONT_TYPE_5x8};
const lcd_object str�mode = {.objtype = LCD_STR, .pstr = strCurMode, .x = 40, .y = 25, .font = FONT_TYPE_10x8};
const lcd_object strKdl = {.objtype = LCD_STR, .pstr = "���", .x = 40, .y = 15, .font = FONT_TYPE_10x15};
const lcd_object strDL21 = {.objtype = LCD_STR, .pstr = "�����-�� 2.1", .x = 0, .y = 15, .font = FONT_TYPE_10x15};
const lcd_object strThresh = {.objtype = LCD_STR, .pstr = "�����:", .x = 0, .y = 55, .font = FONT_TYPE_5x8};
const lcd_object strDB = {.objtype = LCD_STR, .pstr = "1 ��", .x = 65, .y = 55, .font = FONT_TYPE_5x15};


//LCD Images
//const lcd_object imgAr = {.obj_type = LCD_IMG, .pimg = (uint8_t*)AR, .x0 = 0, .y0 = 0, .width = 33, .height = 31};



//LCD screens
lcd_object* MainFrame[] ={(lcd_object*)&strmode, (lcd_object*)&strDL21, (lcd_object*)&strThresh, (lcd_object*)&strDB, (lcd_object*)&str�mode} ;
//lcd_object* Img[] = {(lcd_object*)&imgAr};

void Thread_LCD(void const *pvParameters) {

	int i=0;
	LCD_init();
	printf("LCD init complete\n\r");

	for (;;) {
		printf("Thread_LCD started!\n\r");
		
		sprintf(str, "����: %d", i++);

//		LCD_line(LINE_TYPE_BLACK, 0, 0, LCD_WIDTH-1, 0);
//		LCD_line(LINE_TYPE_BLACK, LCD_WIDTH-1, 0, LCD_WIDTH-1, LCD_HEIGHT-1);
		//LCD_line(LINE_TYPE_BLACK, LCD_WIDTH-1, LCD_HEIGHT-1, 0, LCD_HEIGHT-1);
//		LCD_line(LINE_TYPE_BLACK, 0, LCD_HEIGHT-1, 0,0);
		
//		LCD_string(str,  0,  0, FONT_TYPE_5x8, (i&INVERSE_TYPE_INVERSE));
		
		LCD_Update(MainFrame, 5);
//		LCD_Update(Img, 1);
		
		
		
/*
		LCD_string("X= 8, Y= 10, X= 8, Y= 8", 0,  10, FONT_TYPE_5x8, INVERSE_TYPE_INVERSE);
		LCD_string("X=16, Y=20", 0, 20, FONT_TYPE_5x8, INVERSE_TYPE_NOINVERSE);
		LCD_string("X=24, Y=30", 0, 30, FONT_TYPE_5x8, INVERSE_TYPE_INVERSE);
		LCD_string("X=32, Y=40", 0, 40, FONT_TYPE_5x8, INVERSE_TYPE_NOINVERSE);
		LCD_string("X=40, Y=50", 0, 50, FONT_TYPE_5x8, INVERSE_TYPE_INVERSE);
*/
		osDelay (1000);


	}

}



int main(void) {
/*
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // Enable TIM2 Periph clock

  // Timer base configuration
  TIM_TimeBaseStructure.TIM_Period = 2000;  //Period - 2s
  TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t) (SystemCoreClock / 1000) - 1; //1000 Hz
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
	
  LCD_init();

  //Enable TIM2 IRQ

  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
*/

//	Init_Timers();


	Init_Thread();
	if (!osKernelRunning ())  {                    // is the kernel running ?
    if (osKernelStart () != osOK)  {             // start the kernel
                                                 // kernel could not be started
    }
  }

  while (1) {}; // Infinity loop
}

void TIM2_IRQHandler(void) {
  TIM_ClearITPendingBit(TIM2, TIM_SR_UIF );

  // Some LCD demonstrations
  LCD_clear();
  switch (i++ % 7) {
    case 0:
      LCD_string("10x15", 0, 0, FONT_TYPE_10x15, INVERSE_TYPE_NOINVERSE);
      break;
    case 1:
      LCD_string("5x8", 0, 0, FONT_TYPE_5x8, INVERSE_TYPE_NOINVERSE);
      break;
    case 2:
      LCD_string("5x15", 0, 0, FONT_TYPE_5x15, INVERSE_TYPE_NOINVERSE);
      break;
    case 3:
      LCD_rect(LINE_TYPE_BLACK, ANGLE_TYPE_RECT, 1, FILL_TYPE_BLACK, 0, 0, 132, 64); //tool_strlen(string) * 6 + 5 - calculate rect width for place str
      LCD_string("ACHTUNG!!!", 15, 25, FONT_TYPE_10x15, INVERSE_TYPE_INVERSE);
      break;
    case 4: {
      char *string = "5x8i";
      LCD_rect(LINE_TYPE_BLACK, ANGLE_TYPE_ROUNDED, 1, FILL_TYPE_BLACK, 8, 8,
          tool_strlen(string) * 6 + 5, 15); //tool_strlen(string) * 6 + 5 - calculate rect width for place str
      LCD_string("5x8i", 10, 10, FONT_TYPE_5x8, INVERSE_TYPE_INVERSE);
      break;
    }
    case 5:
      LCD_rect(LINE_TYPE_BLACK, ANGLE_TYPE_RECT, 1, FILL_TYPE_TRANSPARENT, 2, 2,
          20, 10);
      LCD_rect(LINE_TYPE_BLACK, ANGLE_TYPE_ROUNDED, 1, FILL_TYPE_TRANSPARENT, 8,
          8, 20, 10);
      LCD_rect(LINE_TYPE_DOT, ANGLE_TYPE_RECT, 1, FILL_TYPE_WHITE, 14, 14, 20,
          10);
      LCD_rect(LINE_TYPE_BLACK, ANGLE_TYPE_RECT, 1, FILL_TYPE_GRAY, 20, 20, 20,
          10);
      break;
    case 6: {
      uint8_t j;
      for (j = 0; j <= LCD_WIDTH; j = j + 3) {
        LCD_line(LINE_TYPE_BLACK, j, 0, j, LCD_HEIGHT - 1);
      }
      break;
    }
  }
}

