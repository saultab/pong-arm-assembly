#ifndef _ADC_H_
#define _ADC_H_

#include "lpc17xx.h"
#include "../GLCD/GLCD.h"
//#include "../timer/timer.h"
#include <time.h>
#include <stdlib.h>

#define PADDLE_SX -25
#define PADDLE_DX 24
#define START_PADDLE_Y0 278
#define START_PADDLE2_Y0 32

/* lib_adc.c */
extern void ADC_init (void);
extern void ADC_start_conversion (void);

/* IRQ_adc.c */
extern void ADC_IRQHandler(void);
extern void update_paddle(void);

#endif
