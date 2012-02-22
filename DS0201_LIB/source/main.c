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
  Clear_Screen(BLACK); 
 
/*----------Power ON Information----------*/ 

//  Display_Info(8, 20, "Memory Size", Mass_Memory_Size);
//  Display_Info(8, 40, "Block Size ", Mass_Block_Size);
//  Display_Info(8, 60, "Block Count", Mass_Block_Count);
  Display_Str(80, 87, GRN,   PRN, "System Initializing");
  Display_Str(102, 71, GRN,   PRN, "Please Wait");
  Display_Str(8, 39, WHITE, PRN, "DSO Firmware Copyright (c) BenF 2010"); 
  Display_Str(8, 23, YEL,   PRN, "LIB ver 3.01");
  
  //WaitForKey();

//  app_stack = (void *) *(vu32 *)(__APP_VECTORS);
//  app_reset = (pFunction) *(vu32 *)(__APP_VECTORS + 4);
//
///* if stack pointer points to RAM this may be a valid vector table */
//  if (((int) app_stack & 0xFFFE0000) == 0x20000000) {
//      Display_Str(168, 23, WHITE,   PRN, "Jump to APP");
//      (*app_reset)();
//  }
//
///* No app found, just hang */
//  Display_Str(8, 7, RED,   PRN, "Error: No valid application found");
	Clear_Screen (BLACK);
//	Draw_Line (10,10,200,20,BLUE);
//	Draw_Line (10,10,20,200,WHITE);
//	Draw_Line (10,200,30,20,YEL);
//	Draw_Line (10,200,200,180,GRN);
//
//	Draw_Line (80,80, 160,80, BLUE);
//	Draw_Line (160,80,160,240, BLUE);

	sWProgressBar pTacho;
	sWProgressBar pFuel;
	
	WgProgressBar_SetGeometry (&pTacho, 320 - 60 - 10, 20, 60, 240-30);
	WgProgressBar_SetGeometry (&pFuel, 10, 20, 60, 240-30);

	WgProgressBar_Draw (&pTacho);
	WgProgressBar_Draw (&pFuel);

	WgProgressBar_SetRange (&pFuel, 0, 1000, 100);
	WgProgressBar_SetRange (&pTacho, 0, 100, 10);
	
	WgProgressBar_SetValue (&pFuel,30);
	WgProgressBar_SetValue (&pTacho,70);

	Draw_Line (0,18,320,18,RGB(20,20,20));

	WgProgressBar_Update (&pTacho);
	WgProgressBar_Update (&pFuel);

	int i = 0;
	int y = 30;
	int d;
  while (1) {
		WgProgressBar_SetValue (&pTacho,i);
		WgProgressBar_SetValue (&pFuel,y);
		WgProgressBar_Update (&pTacho);
		WgProgressBar_Update (&pFuel);
		i+=10;
		y+=155;
		if (i > 100)
			i=0;
		if (y > 1000)
			y=0;
		Delayms (200);
	}

}
/********************************* END OF FILE ********************************/
