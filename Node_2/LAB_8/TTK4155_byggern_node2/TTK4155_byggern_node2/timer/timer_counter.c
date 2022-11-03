/*
 * timer_counter.c
 *
 * Created: 03.11.2022 14:52:07
 *  Author: haavarok
 */ 

#include "timer_counter.h"

void timer_counter_init()
{
	// Peripheral Clock 27 Enable (TC0)
	PMC->PMC_PCER0 = PMC_PCER0_PID27;
	// Counter clock enable command (TC0)
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN;
	// Enable RC Trigger
	TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_CPCTRG;
	// Set Compare Time
	TC0->TC_CHANNEL[0].TC_RC = 0x501BD00;
	// Enable TC0 Interrupt
	TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;
	// Enable Interrupt for TC0
	NVIC_EnableIRQ(TC0_IRQn);
	//Counter is reset and the clock is started p.880
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG;
	
	// TIMER COUNTER FOR ENCODER READ:
	
	// Peripheral Clock 28 Enable (TC1)
	PMC->PMC_PCER0 = PMC_PCER0_PID28;	
	// Counter clock enable command (TC1)
	TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN;
	// Enable RC Trigger
	TC0->TC_CHANNEL[1].TC_CMR = TC_CMR_CPCTRG;
	// Set Compare Time
	TC0->TC_CHANNEL[1].TC_RC = 0x280DE80; // 0x348 Should equal 20 microseconds :--)
	//Counter is reset and the clock is started p.880
	TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_SWTRG;
}

void delay_ch1_micro(uint32_t microsec)
{	
	// Reset TC1
	uint32_t tc_sr = TC0->TC_CHANNEL[1].TC_SR;
	// Read TC value into two variables to make millis-ish
	uint32_t time0 = TC0->TC_CHANNEL[1].TC_CV;
	uint32_t time1 = TC0->TC_CHANNEL[1].TC_CV;
	// Wait until 20 microsec has passed
	while ((time1 - time0) < (microsec*42)) time1 = TC0->TC_CHANNEL[1].TC_CV;
}