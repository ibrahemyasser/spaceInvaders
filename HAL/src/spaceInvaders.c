
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../Nokia5110.h"
#include "../LIBRARIES/common/Std_Types.h"
#include "../LIBRARIES/CpuDriver/inc/cpu_driver.h"
#include "../../MCAL/SYSTICK/Inc/Systick.h"
#include "../MCAL/INTERRUPT/inc/IntCtrl.h"
#include "../inc/spaceInvaders.h"
#include "../MCAL/PORT/Inc/Port_Cfg.h"
#include "../Random.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
// image of the player's ship
// includes two blacked out columns on the left and right sides of the image to prevent smearing when moved 2 pixels to the left or right
// width=18 x height=8
const unsigned char SmallEnemy10PointA[] = {
 0x42, 0x4D, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x0F, 0xF0, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x0F,
 0xF0, 0xFF, 0xFF, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF};
const unsigned char PlayerShip0[] = {
 0x42, 0x4D, 0xD6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00,
 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0xAA, 0xAA, 0xAA, 0xAA,
 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF};

const unsigned char Bullet_Map[]  ={
 0x42, 0x4D, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0xFF,
};




	// Set up the player at the bottom center of the screen

extern Port_ConfigType Move_Right_Button;
extern Port_ConfigType Move_Left_Button;
extern Port_ConfigType Fire_Button;	
	
extern GPIO_EXTI_ConfigType Right_Button;
extern GPIO_EXTI_ConfigType Left_Button;
extern GPIO_EXTI_ConfigType Fire_EXTI_Button;
	
extern IntCtr_Config Int_RightButton;
extern IntCtr_Config Int_LeftButton;
extern IntCtr_Config Int_FireButton;

uint8_t nextBullet = 0;
uint8_t bulletsCounter = 1;
Player player = { {SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2, SCREEN_HEIGHT - PLAYER_HEIGHT - 2}, 0 };

Bullet playerBullet[MAX_OF_BULLETS];
Enemy_t enemies[MAX_OF_ENEMIES];

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void game_Init(void)
{
	uint8_t i;
	Port_Init(&Move_Right_Button);
	Port_Init(&Move_Left_Button);
	Port_Init(&Fire_Button);
	
	Port_EXTI_Init(&Right_Button);
	Port_EXTI_Init(&Left_Button);
	Port_EXTI_Init(&Fire_EXTI_Button);
	
	IntCrtl_Init(&Int_RightButton);
	IntCrtl_Init(&Int_LeftButton);
	IntCrtl_Init(&Int_FireButton);
	for (i = 0;i<MAX_OF_BULLETS;i++)
	{
		playerBullet[i].pos.x = 0;
		playerBullet[i].pos.y = 0;
		playerBullet[i].active = FALSSE;	
		playerBullet[i].fired = FALSSE;		
	}
	for (i = 0;i<MAX_OF_ENEMIES;i++)
	{
		enemies[i].alive = FALSSE;	
	}
}

// Draw the player on the screen
void draw_player(Player p) {
  Nokia5110_PrintBMP(p.pos.x, p.pos.y, PlayerShip0, 1);
	Nokia5110_DisplayBuffer();     
}

// Clear the player from the screen
void clear_player(Player p) {
  Nokia5110_PrintBMP(p.pos.x, p.pos.y, PlayerShip0, 1);
}

// Move the player left
void move_left(void) {
  
	if (player.pos.x > 0) {
		clear_player(player);
		draw_player(player);
		player.pos.x -= PLAYER_SPEED;
  }
}

// Move the player right
void move_right(void) {
  
  if (player.pos.x < SCREEN_WIDTH - PLAYER_WIDTH) {
    clear_player(player);
		player.pos.x += PLAYER_SPEED;
		draw_player(player);
  }
  
}
void draw_bullet() {
	uint8_t bu;
	for( bu = 0;bu<MAX_OF_BULLETS;bu++)
	{
		if (playerBullet[bu].active)
		{
			Nokia5110_PrintBMP(playerBullet[bu].pos.x, playerBullet[bu].pos.y, Bullet_Map, 1);
			Nokia5110_DisplayBuffer();     
		}
		
	}
  
	
}

// Clear the player from the screen
void clear_bullet(Player p) {
  Nokia5110_PrintBMP(p.pos.x, p.pos.y, Bullet_Map, 1);
}

void fire_PlayerBullet(void)
{
	uint8_t bu;
	for(bu = 0;bu<MAX_OF_BULLETS;bu++)
	{
		if ((!(playerBullet[bu].active))&&(!(playerBullet[bu].fired)))
		{
			playerBullet[bu].pos.x = player.pos.x + PLAYER_WIDTH / 2 - BULLET_WIDTH / 2;
			playerBullet[bu].pos.y = player.pos.y - 7 ;
			playerBullet[bu].active = TRUUE; 
			playerBullet[bu].fired = TRUUE;
			break;
		}
		
	}
}

void generateEnemies(void) {
  uint8_t i ;
	uint8_t numEnemies = Random() % (MAX_OF_ENEMIES + 1);
  for ( i = 0; i < numEnemies; i++) {
    
    if (!enemies[i].alive) {
          enemies[i].pos.x = Random32() % (84 - ENEMY_WIDTH + 1);
          enemies[i].pos.y = 0;
          enemies[i].alive = TRUUE;
          break;
        }
  }
}

void updatePlayerBullet(void) {
  uint8_t bu;
	for(bu = 0;bu<MAX_OF_BULLETS;bu++)
	{
		if (playerBullet[bu].active) {
    playerBullet[bu].pos.y -= PLAYER_BULLET_SPEED;
    if (playerBullet[bu].pos.y < 0) {
      playerBullet[bu].active = FALSSE;
			playerBullet[bu].fired = FALSSE;
			}
		}
  }
	for(bu = 0;bu<MAX_OF_ENEMIES;bu++)
	{
		if (enemies[bu].alive) {
    enemies[bu].pos.y += ENEMY_SPEED;
    if (enemies[bu].pos.y > 48) {
      enemies[bu].alive = FALSSE;
			}
		}
  }
	generateEnemies();
	Systick_StartTimer(BULLET_DELAY,updatePlayerBullet);
}
void draw_enemies(void)
{
	uint8_t bu;
	for( bu = 0;bu<MAX_OF_ENEMIES;bu++)
	{
		if (enemies[bu].alive)
		{
			Nokia5110_PrintBMP(enemies[bu].pos.x, enemies[bu].pos.y, SmallEnemy10PointA, 1);
			Nokia5110_DisplayBuffer();     
		}
		
	}
}




//Game Over 

void GameOver(int MAX_SCORE){
	
  Nokia5110_Clear();
  Systick_StopTimer();
  Nokia5110_SetCursor(1, 2);
  Nokia5110_OutString("GAME OVER");
	
	
}

//main menu

void MAIN_MENU(void){
		
  Nokia5110_Clear();
  Nokia5110_SetCursor(0, 0);
  Nokia5110_OutString("  MAIN MENU");
  Nokia5110_SetCursor(0, 1);
  Nokia5110_OutString("............");
  Nokia5110_SetCursor(0, 3);
  Nokia5110_OutString("1-GO TO PLAY");
  Nokia5110_SetCursor(0, 5);
  Nokia5110_OutString("2- EXIT");
  
}

/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/


/**********************************************************************************************************************
 *  END OF FILE: spaceInvaders.c
 *********************************************************************************************************************/









