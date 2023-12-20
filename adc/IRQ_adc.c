/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/
#include "adc.h"

extern unsigned short AD_current, AD_last, paddle1_refresh_dx;
extern int primo;

void ADC_IRQHandler(void) {
	if(primo==1)
		update_paddle();
}

void update_paddle(void){
	
	int diff_AD, i;
	
	//cattura AD paddle
	AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);
	AD_current = AD_current*230/0xfff;
	
	if(AD_current > 209)
			AD_current = 209;
	else if (AD_current < 30)
		AD_current = 30;
	
	diff_AD = (int)AD_current - (int)AD_last;
	
	if(diff_AD < -2 || diff_AD > 2){

		if(AD_current >= AD_last)
			paddle1_refresh_dx=1;

		else
			paddle1_refresh_dx=0;
	
		//Verso DX
		for(i=0; i<50 && paddle1_refresh_dx==1; i++)
			LCD_DrawLine(AD_last + PADDLE_SX + i, START_PADDLE_Y0, AD_last + PADDLE_SX + i, START_PADDLE_Y0 + 9, Black);
		for(i=0; i<50 && paddle1_refresh_dx==1; i++)
			LCD_DrawLine(AD_current + PADDLE_SX + i, START_PADDLE_Y0, AD_current + PADDLE_SX + i, START_PADDLE_Y0 + 9, Green);
		
		
		//Verso SX
		for(i=0; i<50 && paddle1_refresh_dx==0; i++)
			LCD_DrawLine(AD_last + PADDLE_DX - i, START_PADDLE_Y0, AD_last + PADDLE_DX - i, START_PADDLE_Y0 + 9, Black);
		for(i=0; i<50 && paddle1_refresh_dx==0; i++)
			LCD_DrawLine(AD_current + PADDLE_DX - i, START_PADDLE_Y0, AD_current + PADDLE_DX - i, START_PADDLE_Y0 + 9, Green);
					
		AD_last = AD_current;
		}
}
