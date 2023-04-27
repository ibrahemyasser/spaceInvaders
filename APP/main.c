#include "../Nokia5110.h"
#include "../Random.h"
#include "../TExaS.h"
#include "../HAL/inc/spaceInvaders.h"
#include "../MCAL/SYSTICK/Inc/Systick.h"


int main(void){
  
	TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
	Nokia5110_Init();
  Nokia5110_ClearBuffer();
	game_Init();
	Systick_Init();
  
  
  // Game loop
  while (1) {
 
    //updatePlayerBullet();

    // Draw game state
    Nokia5110_ClearBuffer();
    draw_player(player);
    draw_bullet(playerBullet);
    Nokia5110_DisplayBuffer();
    
    // Add other game logic here
  }
}






