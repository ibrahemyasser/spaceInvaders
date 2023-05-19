// Sound.h



void Sound_Init(void);
void Sound_Play(void);
void Sound_Shoot(void);
void Sound_Killed(void);
void Sound_Explosion(void);
void Sound_InvaderShoot(void);




// **************Sound_Tone*********************
// Change SysTick periodic interrupts to start sound output
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long period);


// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void);
