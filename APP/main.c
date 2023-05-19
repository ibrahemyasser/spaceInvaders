#include "../Nokia5110.h"
#include "../Random.h"
#include "../TExaS.h"
#include "../HAL/inc/spaceInvaders.h"
#include "../MCAL/SYSTICK/Inc/Systick.h"


//extern unsigned char UART0_InChar(void);
//extern unsigned char UART0_OutChar(uint8_t);

int main(void){
	TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
	Systick_Init();
	Nokia5110_Init();
	draw_icon();
	game_Init();
	Sound_Init();	
	//UART_Init();
	main_menu_select();
	moveLeft_Flag = FALSSE;
	moveRight_Flag = FALSSE;
  // Game loop
  while (1) {
//			receivedChar = UART_InChar();
//		uartOutChar(receivedChar);
		
		if (enemyGenrateFlag == TRUUE)
		{
			enemyGenrateFlag = FALSSE;
			generateEnemies();
		}
		if (fireBullet_Flag == TRUUE)
		{
			fireBullet_Flag = FALSSE;
			fire_PlayerBullet();
		}
		check_Player_Collision();
		check_Bullet_Collision();
    Nokia5110_ClearBuffer();
    draw_explosion();
		draw_player();
    draw_bullet();
		draw_enemies();
    Nokia5110_DisplayBuffer();
	  
	  //		Sound_Play();
//		
//		Sound_Tone(5);
    
    // Add other game logic here
  }
}






