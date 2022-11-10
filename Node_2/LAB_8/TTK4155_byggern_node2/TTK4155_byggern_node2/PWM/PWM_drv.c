/*
 * PWM_drv.c
 *
 * Created: 20.10.2022 16:00:46
 *  Author: haavarok
 */ 

#include "PWM_drv.h"
#include "sam3x8e.h"

// 0 % dutycyle of period = dutycycle
// 10 % dutycle of period = dutycyle - 10 %
 
// Commented values are for the green ping pong board
#define PWM_CHN_5_MID_VAL 0x3D8 // 0x2F6D
#define PWM_CHN_5_RANGE 0x148 // 0x189
#define PWM_CHN_5_INIT_VAL 0x3D8  //0x2F6D
#define PWM_CHN_5_PERIOD_VAL 0x7B1  //0x3345

void PWM_init()
{
	// Enabling peripheral clock for PWM
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;
	//Enable pin 19 to Peripheral
	PIOC->PIO_PDR |= PIO_PDR_P19;
	// Enable peripheral B for P19
	PIOC->PIO_ABSR |= PIO_ABSR_P19;
	
	// Prescales MCLK with 128
	PWM->PWM_CH_NUM[5].PWM_CMR |= PWM_CMR_CPRE_MCK_DIV_128;
	// CPRD = (MCLK * Period)/Prescaler. CPRD = (84MHz*20ms)/128
	//Sets channel 5 period update to 20 ms
	PWM->PWM_CH_NUM[5].PWM_CPRD |= PWM_CPRD_CPRD(PWM_CHN_5_PERIOD_VAL);
	//Sets channel 5 Duty Cycle to 1,5 ms, mid position for servo
	PWM->PWM_CH_NUM[5].PWM_CDTY |= PWM_CDTY_CDTY(PWM_CHN_5_INIT_VAL);
	//Enables PWM channel 0 
	PWM->PWM_ENA |= PWM_ENA_CHID5;

}

uint32_t PWM_set_period_percentage(int16_t value)
{
	if (value > 100) value = 100;
	else if (value < -100) value = -100;
	
	//PWM signal is reversed
	uint32_t pwm_value =  PWM_CHN_5_MID_VAL + (value * PWM_CHN_5_RANGE)/100;
	
	// Update PWM value in register
	PWM->PWM_CH_NUM[5].PWM_CDTYUPD = (pwm_value);
	return pwm_value;
}
