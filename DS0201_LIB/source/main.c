/*******************************************************************************
* File Name: main.c
*******************************************************************************/

#include "Lcd.h"
#include "stm32f10x_lib.h"
#include "usb_lib.h"
#include "HW_V1_Config.h"
#include "memory.h"
#include "widgets.h"

typedef  void (*pFunction)(void);
const u32 __APP_VECTORS = 0x0800C000;

extern u32 Mass_Memory_Size;
extern u32 Mass_Block_Size;
extern u32 Mass_Block_Count;

void main(void)
{
  void *app_stack;
  pFunction app_reset;

/*--------------initialization-----------*/

  Set_System();
  NVIC_Configuration();
  GPIO_Config();
  SD_Card_Check();
  //MSD_Init();
  //Get_Medium_Characteristics();
  USB_Init();
  //DMA_Configuration();
  ADC_Configuration();
  Timer_Configuration();
  LCD_Initial();
 
  //WaitForKey();
  Display_Str(8, 23, YEL,   PRN, "LIB ver 3.01");



/*-------------- Analog needle test ------------*/
  Clear_Screen(BLACK); 

	sWAnalogNeedle ndl;
	WgAnalogNeedle_SetGeometry (&ndl,0,0,200);
	WgAnalogNeedle_SetRange (&ndl,0,100,10);
	WgAnalogNeedle_Draw (&ndl);
	int t = 0;
	while(1) {
		Delayms (200);
		t++;
		if (t > 100)
			t = 0;
		WgAnalogNeedle_SetValue (&ndl,t);
		WgAnalogNeedle_Update (&ndl);
		Draw_Line (0,18,320,18,RGB(20,20,20));
	}
/*------------------------------------------------*/



/*------------- progress bar test ----------------*/
	Draw_Line (0,18,320,18,RGB(20,20,20));
	sWProgressBar pTacho;
	sWProgressBar pFuel;
	WgProgressBar_SetGeometry (&pTacho, 320 - 60 - 10, 20, 60, 240-30);
	WgProgressBar_SetGeometry (&pFuel, 10, 20, 60, 240-30);
	WgProgressBar_SetRange (&pFuel, 50, 150, 10);
	WgProgressBar_SetRange (&pTacho, 50, 400, 7);
	WgProgressBar_Draw (&pTacho);
	WgProgressBar_Draw (&pFuel);

	int i = 0;
	int y = 0;
	int d = 0;
	int m = 0;
  
	while (1) {
		WgProgressBar_SetValue (&pTacho,i);
		WgProgressBar_SetValue (&pFuel,y);
		WgProgressBar_Update (&pTacho);
		WgProgressBar_Update (&pFuel);

		if (!d)
			i+=10;
		else
			i-=10;
		if (i > 400)
			d = 1;
		if (i <= 0)
			d = 0;
		
		if (!m)
			y+=4;
		else
			y-=10;
		if (y > 150)
			m = 1;
		if (y <= 50)
			m = 0;

		Delayms (200);
	}
/*-----------------------------------------*/





}
/********************************* END OF FILE ********************************/
