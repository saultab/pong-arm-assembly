/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "timer.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern unsigned short pallina_Y, pallina_X, AD_current, paddle2_X, paddle2_refresh_dx;
extern int angle, primo, increment_y, increment_x, partenza, loser, flag;
extern char score1[10], score2[10];

void TIMER0_IRQHandler (void){				/*timer0 per pallina*/
	
	static int tmp=0, codpad=0;

  if (LPC_TIM0->IR & 01){
		if(primo>=1){
			
			/* verifica pallina contro paddle1 */
			if((pallina_Y >= 271) && (pallina_X + 2 >= AD_current - 25 && pallina_X - 2<= AD_current + 25 ))
				codpad = 1;
			

			/* verifica pallina contro paddle2 */
			else if((pallina_Y <= 43) && (pallina_X + 2 >= paddle2_X - 25 && pallina_X - 2 <= paddle2_X + 25))
				codpad = 2;
			
			/* verifica pallina contro parete dx oppure sx */
			else if((pallina_X + 2 >= 233 ||  pallina_X - 2 <= 8) && (pallina_Y >= 41 && pallina_Y <= 277)){
				tmp = increment_y;
				incremento_coord(&increment_x,&increment_y,180-angle);
				angle = 180 - angle;

				if(tmp>0 && increment_x!=0)
					increment_y += 2*tmp;
			}
			
			/* controllo game over paddle1 */
			else if(pallina_Y+2>278){
				codpad = 0;
				point_Player2();
			}
			
			/* controllo game over paddle2 */
			else if(pallina_Y-2<30){
				codpad = 0;
				point_Player1();
			}
			
			NVIC_SetPriority(TIMER0_IRQn, 0);
			NVIC_SetPriority(TIMER1_IRQn, 1);
			NVIC_SetPriority(TIMER2_IRQn, 1);
			
		}
		
		if (codpad==1 && primo>=1){

				if((pallina_X>=AD_current+PADDLE_SX && pallina_X<= AD_current+PADDLE_SX+5) || (pallina_X>=AD_current+PADDLE_DX-5 && pallina_X<= AD_current+ PADDLE_DX)){
					if(increment_x<0)
						angle = 180-22;
					else
						angle = 22;
				}
				else if((pallina_X>=AD_current+PADDLE_SX+6 && pallina_X<= AD_current+PADDLE_SX+11) || (pallina_X>=AD_current+PADDLE_DX-11 && pallina_X<= AD_current+ PADDLE_DX-6)){
					if(increment_x<0)
						angle = 180-60;
					else
						angle = 60;
				}
				else if((pallina_X>=AD_current+PADDLE_SX+12 && pallina_X<= AD_current+PADDLE_SX+17) || (pallina_X>=AD_current+PADDLE_DX-17 && pallina_X<= AD_current+ PADDLE_DX-12)){
					if(increment_x<0)
						angle = 180-70;
					else
						angle = 70;
				}
				else {
					if(increment_x<0)
						angle = 180-75;
					else
						angle = 75;
				}
				flag=2;
				incremento_coord(&increment_x,&increment_y,angle);
				codpad=0;
			}
		
			/* se pallina colpisce paddle2 */
			else if (codpad==2 && primo>=1){
				if((pallina_X>=AD_current+PADDLE_SX && pallina_X<= AD_current+PADDLE_SX+5) || (pallina_X>=AD_current+PADDLE_DX-5 && pallina_X<= AD_current+ PADDLE_DX)){
					if(increment_x<0)
						angle = 180-22;
					else
						angle = 22;
				}
				else if((pallina_X>=AD_current+PADDLE_SX+6 && pallina_X<= AD_current+PADDLE_SX+11) || (pallina_X>=AD_current+PADDLE_DX-11 && pallina_X<= AD_current+ PADDLE_DX-6)){
					if(increment_x<0)
						angle = 180-60;
					else
						angle = 60;
				}
				else if((pallina_X>=AD_current+PADDLE_SX+12 && pallina_X<= AD_current+PADDLE_SX+17) || (pallina_X>=AD_current+PADDLE_DX-17 && pallina_X<= AD_current+ PADDLE_DX-12)){
					if(increment_x<0)
						angle = 180-70;
					else
						angle = 70;
				}
				else {
					if(increment_x<0)
						angle = 180-75;
					else
						angle = 75;
				}
				flag=2;
				incremento_coord(&increment_x,&increment_y,angle);
				increment_y =-1*increment_y;
				codpad=0;
			}
			/* riscrittura score player1 se pallina passa sopra */
			if (pallina_X > 8 &&  pallina_Y > 155 && pallina_Y < 165)	
					GUI_Text(10, 160, (uint8_t *) score1, White, Black);
			
			/* riscrittura score player2 se pallina passa sopra */
			if(pallina_X > 210 && pallina_Y > 155 && pallina_Y < 165)
					GUI_Text_Player2(226, 176, (uint8_t *) score2, White, Black);
			
		
			if(primo>=1)
			refresh_ball(&increment_x, &increment_y);
		
		LPC_TIM0->IR = 1;			
	}
	else if(LPC_TIM0->IR & 02)
  {
		LPC_TIM0->IR =  2 ;			
	}
	else if(LPC_TIM0->IR & 4)
  {
		LPC_TIM0->IR =  4 ;	
	}
	else if(LPC_TIM0->IR & 8)
  {
		LPC_TIM0->IR =  8 ;
	}
  return;
}

void TIMER1_IRQHandler (void){				/*timer1 per paddle1*/
	
  if (LPC_TIM1->IR & 01){
		if(primo>=1){
			ADC_start_conversion();
			update_paddle();
		}
		NVIC_SetPriority(TIMER1_IRQn, 0);
		NVIC_SetPriority(TIMER0_IRQn, 1);
		LPC_TIM1->IR = 1;
	}
		
	else if(LPC_TIM1->IR & 02){
		LPC_TIM1->IR =  2;			
	}
	
	else if(LPC_TIM1->IR & 4){
		LPC_TIM1->IR =  4;
	}

	else if(LPC_TIM1->IR & 8){
		LPC_TIM1->IR =  8;
	}
  return;
}

void TIMER2_IRQHandler (void){	/*timer2 per paddle2*/
	
	static int i;	

	if (LPC_TIM2->IR & 01){
		
		NVIC_SetPriority(TIMER2_IRQn, 0);
		NVIC_SetPriority(TIMER0_IRQn, 1);
		if((paddle2_X + PADDLE_DX) >= 234)
			paddle2_refresh_dx=0;

		else if((paddle2_X + PADDLE_SX) <=  5)
			paddle2_refresh_dx=1;
	
		//Verso DX
		for(i=0; i<30 && paddle2_refresh_dx==1; i++){
				LCD_DrawLine(paddle2_X + PADDLE_SX + i, START_PADDLE2_Y0, paddle2_X + PADDLE_SX + i, START_PADDLE2_Y0 + 9, Black);
				LCD_DrawLine(paddle2_X + PADDLE_DX + i, START_PADDLE2_Y0, paddle2_X + PADDLE_DX + i, START_PADDLE2_Y0 + 9, Green);
		}
		
		//Verso SX
		for(i=0; i<30 && paddle2_refresh_dx==0; i++){
				LCD_DrawLine(paddle2_X + PADDLE_DX - i, START_PADDLE2_Y0, paddle2_X + PADDLE_DX - i, START_PADDLE2_Y0 + 9, Black);
				LCD_DrawLine(paddle2_X + PADDLE_SX - i - 1, START_PADDLE2_Y0, paddle2_X + PADDLE_SX - i - 1, START_PADDLE2_Y0 + 9, Green);
		}
		
		if(paddle2_refresh_dx==1)
			paddle2_X+=30;

			else
				paddle2_X-=30;

		LPC_TIM2->IR = 1;			
	}
	
	else if(LPC_TIM2->IR & 02){
		LPC_TIM2->IR =  2;
	}
	
	else if(LPC_TIM2->IR & 4){
		LPC_TIM2->IR =  4;
	}
	
	else if(LPC_TIM2->IR & 8){
		LPC_TIM2->IR =  8;
	}
	
  return;
}

void TIMER3_IRQHandler (void){
	
	/* Match register 0 interrupt service routine */
	if (LPC_TIM3->IR & 01){
		LPC_TIM3->IR = 1;			/* clear interrupt flag */
	}
		/* Match register 1 interrupt service routine */
	else if(LPC_TIM3->IR & 02){
		LPC_TIM3->IR =  2 ;			/* clear interrupt flag */	
	}
	/* Match register 2 interrupt service routine */
	else if(LPC_TIM3->IR & 4){	 
		LPC_TIM3->IR =  4 ;			/* clear interrupt flag */	
	}
		/* Match register 3 interrupt service routine */
	else if(LPC_TIM3->IR & 8){
		LPC_TIM3->IR =  8 ;			/* clear interrupt flag */	
	}
	
  return;
}

void point_Player1(void){
	int var = atoi(score1);				
	if(var < 5){
		paint_ball(pallina_X,pallina_Y,Black);
		GUI_Text(10, 160, (uint8_t *) score1, Black, Black);
		var += 1;
		sprintf(score1,"%d",var);
		GUI_Text(10, 160, (uint8_t *) score1, White, Black);

		//restart e lancio pallina a paddle2 che ha perso
		pallina_X = 230;
		pallina_Y = 170;
		paint_ball(pallina_X,pallina_Y,Green);
		increment_x = increment_y = -2;
		angle = 135;
	}
	
	if(var == 5){
		primo = 0;
		flag = 0;
		loser=1;
		disable_timer(0);
		disable_timer(1);
		disable_timer(2);

		GUI_Text_Player2(160, 150, (uint8_t *) "YOU LOSE", White, Black);
		GUI_Text(100, 200, (uint8_t *) "YOU WIN", White, Black);

	}
}


void point_Player2(void){
	int var = atoi(score2);				
	if(var < 5){
		paint_ball(pallina_X,pallina_Y,Black);
		GUI_Text(226, 176, (uint8_t *) score2, Black, Black);
		var += 1;
		sprintf(score2,"%d",var);
		GUI_Text_Player2(226, 176, (uint8_t *) score2, White, Black);

		//restart e lancio pallina a paddle1 che ha perso
		pallina_X = 230;
		pallina_Y = 170;
		paint_ball(pallina_X,pallina_Y,Green);
		increment_x = -2;
		increment_y = 2;
		angle = 45;
	}
	if(var == 5){
		primo = 0;
		flag = 0;
		loser=1;
		disable_timer(0);
		disable_timer(1);
		disable_timer(2);
		GUI_Text_Player2(150, 150, (uint8_t *)  "YOU WIN", White, Black);
		GUI_Text(90, 160, (uint8_t *) "YOU LOSE", White, Black);
	}
}

/******************************************************************************
**                            End Of File
******************************************************************************/
