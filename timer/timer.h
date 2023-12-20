/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_timer, funct_timer, IRQ_timer .c files
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#ifndef __TIMER_H
#define __TIMER_H
#include "lpc17xx.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../GLCD/GLCD.h" 
//#include "../TouchPanel/TouchPanel.h"
#include "../adc/adc.h"
#include <math.h>

/* init_timer.c */
extern uint32_t init_timer ( uint8_t timer_num, uint32_t Prescaler, uint8_t MatchReg, uint8_t SRImatchReg, uint32_t TimerInterval );
extern void enable_timer( uint8_t timer_num );
extern void disable_timer( uint8_t timer_num );
extern void reset_timer( uint8_t timer_num );
/* IRQ_timer.c */
extern void TIMER0_IRQHandler (void);
extern void TIMER1_IRQHandler (void);
extern void TIMER2_IRQHandler (void);
extern void TIMER3_IRQHandler (void);
extern void paint_ball(int x, int y, uint16_t Color);
void point_Player1(void);
void point_Player2(void);
#endif /* end __TIMER_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
