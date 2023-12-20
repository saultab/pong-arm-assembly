#include "button.h"

extern int down, down1, down2, loser;

void EINT0_IRQHandler (void)	  	/* INT0	*/
{
	down2=1;		//reset game
	if (loser==1){
		disable_timer(0);	//non aggiornare ball
		disable_timer(1);	//non aggiornare paddle
		disable_timer(2);
	}
	NVIC_DisableIRQ(EINT0_IRQn);	/* disable Button interrupts				*/
	LPC_PINCON->PINSEL4    &= ~(1 << 20);     /* GPIO pin selection		 */
	
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	down = 1;		//start game
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	down1=1;		//pause game
	NVIC_DisableIRQ(EINT2_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 24);     /* GPIO pin selection */
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


