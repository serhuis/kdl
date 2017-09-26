//#include "stm32f10x.h"

#include <stdio.h>
#include "cmsis_os.h"

#include "main.h"


#include "inc/uc1601s.h"


uint8_t i = 0;

void Thread_LCD(void const *pvParameters);

osThreadDef(Thread_LCD, osPriorityNormal, 1, 0);

int Init_Thread (void) {

	osThreadId tid_Thread_LCD;
  
	tid_Thread_LCD = osThreadCreate (osThread(Thread_LCD), NULL);
  if(!tid_Thread_LCD) return(-1);
	
  return(0);
}

void Thread_LCD(void const *pvParameters) {

	char str[] = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0};
	LCD_init();

	for (;;) {
		

//		LCD_line(LINE_TYPE_BLACK, 0, 0, LCD_WIDTH-1, 0);
//		LCD_line(LINE_TYPE_BLACK, LCD_WIDTH-1, 0, LCD_WIDTH-1, LCD_HEIGHT-1);
		//LCD_line(LINE_TYPE_BLACK, LCD_WIDTH-1, LCD_HEIGHT-1, 0, LCD_HEIGHT-1);
//		LCD_line(LINE_TYPE_BLACK, 0, LCD_HEIGHT-1, 0,0);
		
//		LCD_WIDTH
/*		LCD_string(str,  0,  0, FONT_TYPE_5x8, INVERSE_TYPE_NOINVERSE);
*/		LCD_string("X= 8, Y= 8, X= 8, Y= 8", 0,  8, FONT_TYPE_5x8, INVERSE_TYPE_INVERSE);
		LCD_string("X=16, Y=16", 0, 16, FONT_TYPE_5x8, INVERSE_TYPE_NOINVERSE);
		LCD_string("X=24, Y=24", 0, 24, FONT_TYPE_5x8, INVERSE_TYPE_INVERSE);
		LCD_string("X=32, Y=32", 0, 32, FONT_TYPE_5x8, INVERSE_TYPE_NOINVERSE);
		LCD_string("X=40, Y=40", 0, 40, FONT_TYPE_5x8, INVERSE_TYPE_INVERSE);
		LCD_string("X=48, Y=48", 0, 48, FONT_TYPE_5x8, INVERSE_TYPE_NOINVERSE);
		LCD_string("X=56, Y=56", 0, 56, FONT_TYPE_5x8, INVERSE_TYPE_INVERSE);


		osDelay (1000);


	}

}



int main(void) {
	
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

