/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "RIT.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern unsigned short AD_current, AD_last, pallina_Y, pallina_X, paddle2_X;
extern char score1[10], score2[10];
extern int angle, increment_y, increment_x, down, down1, down2, primo, pause, loser, flag;

void RIT_IRQHandler (void)
{
	int i;
	if(down2!=0){
		if(((LPC_GPIO2->FIOPIN & (1<<10)) == 0) && loser==1 ){  //INT0 RESET
			down2++;
			switch(down2){
				case 2:
					flag=0;
					pause=1;
					loser=2;
					disable_timer(0);
					disable_timer(1);
					disable_timer(2);
				
					GUI_Text(90, 160, (uint8_t *) "YOU LOSE", Black, Black);	//cancello "YOU LOSE"
					LCD_Clear(Black);
				/*Stampo bordo rosso*/
					for(i=0; i<320; i++){
						LCD_DrawLine(0, i, 4, i,Red);
						LCD_DrawLine(235, i, 240, i,Red);
					}
					
					sprintf(score1,"%d",0);
					sprintf(score2,"%d",0);
					GUI_Text(10, 160, (uint8_t *) score1, White, Black);
					GUI_Text_Player2(226, 176, (uint8_t *)score2, White, Black);

					break;
				default:
					break;
			}
		}
		else { /* button released */
			down2=0;
			NVIC_EnableIRQ(EINT0_IRQn);							 
			LPC_PINCON->PINSEL4    |= (1 << 20);     
		}
	}
	if(down!=0){
		if(((LPC_GPIO2->FIOPIN & (1<<11)) == 0) && (loser == 0 || loser ==2)){  //KEY 1 START
			down++;
			switch(down){
				case 2:
					loser=0;
					flag=2;
					start();
					
					enable_timer(2);
					enable_timer(1);
					enable_timer(0);
					AD_current=120;
					paddle2_X=120;
	
					paint_ball(pallina_X,pallina_Y,Green);
					increment_x = -1;
					increment_y = 1;
					angle = 45;
					primo = 1;
					break;
				default:
					break;
			}
		}
		else {	 /* button released */
			down=0;			
			NVIC_EnableIRQ(EINT1_IRQn);							 
			LPC_PINCON->PINSEL4    |= (1 << 22);     
		}
	}
	
	if(down1!=0){
		if(((LPC_GPIO2->FIOPIN & (1<<12)) == 0) && (loser == 0 && flag==2)){  //KEY 2 PAUSA
			down1++;
			switch(down1++){
				case 2:
					 if(pause==0){	//metto in pausa il gioco
						 pause = 1;
						 GUI_Text(100,160, (uint8_t *) "PAUSE", Blue, Black);
						 disable_timer(0);
						 disable_timer(1);
						 disable_timer(2);
						 primo=0;
					 }
					 else if(pause==1){					//riparte il gioco
						 pause = 0;
						 GUI_Text(100,160, (uint8_t *) "PAUSE", Black, Black);
						 enable_timer(0);
						 enable_timer(1);
						 enable_timer(2);
						 primo=1;
					 }
					break;
				default:
					break;
			}
		}
		else {	
			down1=0;
			NVIC_EnableIRQ(EINT2_IRQn);							 
			LPC_PINCON->PINSEL4    |= (1 << 24);  
		}
	}			
  LPC_RIT->RICTRL |= 0x1;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
