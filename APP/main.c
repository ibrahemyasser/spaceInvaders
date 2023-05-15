#include "../Nokia5110.h"
#include "../Random.h"
#include "../TExaS.h"
#include "../HAL/inc/spaceInvaders.h"
#include "../MCAL/SYSTICK/Inc/Systick.h"




int main(void){
  
	TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
	Systick_Init();
	Nokia5110_Init();
  Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();
	game_Init();
	main_menu_select();
  // Game loop
  while (1) {
 
    //updatePlayerBullet();

    // Draw game state
     Nokia5110_ClearBuffer();
		if (enemyGenrateFlag == TRUUE)
		{
			enemyGenrateFlag = FALSSE;
			generateEnemies();
		}
		check_Player_Collide();
		check_Enemy_Collide();
    draw_explosion();
		draw_player();
    draw_bullet();
		draw_enemies();
    Nokia5110_DisplayBuffer();
    
    // Add other game logic here
  }
}






