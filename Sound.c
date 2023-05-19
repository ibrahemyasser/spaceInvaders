// Sound.c


#include "../DAC.h"
#include "Sound.h"
#include "../SoundWaves.h"
#include "..//tm4c123gh6pm.h"

unsigned long Index = 0;
const unsigned char *Wave;
unsigned long SoundCount = 0;


const unsigned short wave[32] = {	
  8,9,11,12,13,14,14,15,15,15,14,	
  14,13,12,11,9,8,7,5,4,3,2,	
  2,1,1,1,2,2,3,4,5,7};	
	

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also calls DAC_Init() to initialize DAC
// Input: none
// Output: none
void Sound_Init(void){
	DAC_Init();
  Index = 0;
  NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
  NVIC_ST_RELOAD_R = 4777 - 1;// reload value
  NVIC_ST_CURRENT_R = 0;      // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000; // priority 1      
}

// **************Sound_Tone*********************
// Change Systick periodic interrupts to start sound output
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long period){
	NVIC_ST_CTRL_R = 0x0007;  // enable SysTick with core clock and interrupts
	NVIC_ST_RELOAD_R = period - 1;// reload value
}


// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void){
 NVIC_ST_CTRL_R = 0;
}


//// Interrupt service routine
//// Executed every 12.5ns*(period)
//void SysTick_Handler(void){
//  Index = (Index+1) % 32; 
//  DAC_Out(wave[Index]); 
//}


//Periodic function passed to Timer2A 
//It determines whether a sound should play or not
void Sound_Play(void){
  if(SoundCount){
    DAC_Out(Wave[Index]>>4);
    Index = Index + 1;
    SoundCount = SoundCount - 1;
  }else{
		DAC_Out(0);
  }
}


//void Sound_Init(void){
//  DAC_Init();               // initialize simple 4-bit DAC
//  Index = 0;
//  SoundCount = 0;
//}


void SoundOut(const unsigned char *pt, unsigned long count){
  Wave = pt;
  Index = 0;
  SoundCount = count;
}

void Sound_Shoot(void){
  SoundOut(shoot,4080);
}
void Sound_Killed(void){
  SoundOut(invaderkilled,3377);
}
void Sound_Explosion(void){
  SoundOut(explosion,2000);
}
void Sound_InvaderShoot(void){
  SoundOut(invadershoot,1802);
}
