#include "DAC.h"
#include "..//tm4c123gh6pm.h"


// Initialize 4-bit DAC 
// Input: none
// Output: none
void DAC_Init(void){
	
//	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
//	/*unsigned long volatile delay;
//  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate port B
//  delay = SYSCTL_RCGC2_R;    // allow time to finish activating*/
//	
//	//This function must be called after SwitchLed_Init function from SwitchLed.c
//	//The clock for PortB is activated in SwitchLed_Init; hence it does not need to be activated here
//	
//  GPIO_PORTB_AMSEL_R &= ~0x0F;      // no analog function for PB3-0
//  GPIO_PORTB_PCTL_R &= ~0x0000FFFF; // regular function for PB3-0
//  GPIO_PORTB_DIR_R |= 0x0F;      // make PB3-0 out
//	GPIO_PORTB_DR8R_R |= 0x0F;    // can drive up to 8mA out
//  GPIO_PORTB_AFSEL_R &= ~0x0F;   // disable alt funct on PB3-0
//  GPIO_PORTB_DEN_R |= 0x0F;      // enable digital I/O on PB3-0
	
	volatile int i;
  SYSCTL_RCGC2_R |= 0x00000002;     // 1) activate clock for Port B
	i =2;
  GPIO_PORTB_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTB_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTB_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTB_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTB_DIR_R = 0x0F;          // 5) PF4,PF0 in, PF3-1 out    0000 1111
  GPIO_PORTB_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTB_PUR_R = 0x00;          // enable pull-up on PF0 and PF4
  GPIO_PORTB_DEN_R = 0x0F;          // 7) enable digital I/O on PF4-0
	GPIO_PORTB_DR8R_R = 0x0F;  // 0000 1111 enable 8mA driver for the first 4 pins
}



// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long data){
  //GPIO_PORTB_DATA_R = data;
  GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~(0x0F)) | (data & 0x0F);
}
