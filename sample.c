/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
//#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "adc/adc.h"
#include "Button/button.h"
//#include "joystick/joystick.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


volatile char score1[10] = {"0"}, score2[10]={"0"};
volatile unsigned short AD_current=120, AD_last = 120, pallina_X = 120, pallina_Y = 180;
volatile unsigned short	paddle2_X = 120, paddle2_refresh_dx=1, paddle1_refresh_dx=1;
volatile int angle=0, primo=1, increment_y=0,increment_x=0, down=0, down1=0, down2=0,  pause=0, loser=0, flag=0;

int main(void)
{
	static int i;
	
  SystemInit();  												/* System Initialization (i.e., PLL)  */
  LCD_Initialization();
	LCD_Clear(Black);
	BUTTON_init();
		
	//valoreRIT = Fclock * 10 ms = 100Mhz*10ms = 0x4c4b40 = 1'000'000
	init_RIT(0xF4240);										/* RIT Initialization 10 msec      		*/
	enable_RIT();													/* RIT enabled												*/
	
	ADC_init();

//	TIMER PER SCHEDA FISICA
//	init_timer(0,0,0,3, 0xF4240);					//ball 50msec
//	init_timer(1,0,0,3, 0x2625A0);				//paddle1 100msec
//	init_timer(2,0,0,3, 0xF4240);					//paddle2 100msec

//	TIMER PER SIMULATORE KEIL
	init_timer(0,0,0,3, 0x61A8);					//ball 1msec
	init_timer(1,0,0,3, 0x7A120);					//paddle1 20msec
	init_timer(2,0,0,3, 0x3D090);					//paddle2 10msec
	
	//valoreTimer = Fclock * 1 ms = 25Mhz*1ms = 0x61A8
	
	LPC_PINCON->PINSEL1 |= (1<<21);       /* convertitore D/A			*/
	LPC_PINCON->PINSEL1 &= ~(1<<20);			/* per il suono					*/
	LPC_GPIO0->FIODIR |= (1<<26);					/*											*/
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode			*/
	LPC_SC->PCON &= ~(0x2);		
			
			
	//print init paddle1
	for(i=0; i<10; i++)
		LCD_DrawLine(120+PADDLE_SX, START_PADDLE_Y0+i, 120+PADDLE_DX, START_PADDLE_Y0+i, Green);
				
	//print init paddle2
	for(i=0; i<10; i++)
		LCD_DrawLine(120 + PADDLE_DX, START_PADDLE2_Y0 + i, 120 + PADDLE_SX, START_PADDLE2_Y0 + i, Green);
	
	preview();

  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
