/****************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 ***************************************/

/****************************************
 *  INCLUDES
 ***************************************/
#include "../Nokia5110.h"
#include "../LIBRARIES/common/Std_Types.h"
#include "../LIBRARIES/CpuDriver/inc/cpu_driver.h"
#include "../../MCAL/SYSTICK/Inc/Systick.h"
#include "../MCAL/INTERRUPT/inc/IntCtrl.h"
#include "../inc/spaceInvaders.h"
#include "../MCAL/PORT/Inc/Port_Cfg.h"
#include "../Random.h"
#include "Bit_Math.h"

/****************************************
*  LOCAL MACROS CONSTANT\FUNCTION
***************************************/

/****************************************
 *  LOCAL DATA 
 ***************************************/

/****************************************
 *  GLOBAL DATA
 ***************************************/
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

const unsigned char smallexplosion0[] ={
 0x42, 0x4D, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0,
 0x0F, 0x00, 0x0F, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0xF0, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
 0xF0, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x00, 0xF0, 0xF0, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
};


	// Set up the player at the bottom center of the screen


uint8_t flag=0,flag2=0;
uint32_t max_score=0;
uint8_t nextBullet = 0;
uint8_t bulletsCounter = 0;
uint8_t mnk4 = FALSSE;
uint8_t lifes=MAX_LIVES;
uint8_t enemyGenrateFlag = TRUUE;
uint8_t generateCount = 0;
uint8_t start = FALSSE;
uint8_t bye		= FALSSE;

unsigned long FrameCount=0; 
unsigned long TimerCount;
unsigned long Semaphore; 
unsigned long SW1,SW2;  // input from PF4,PF0

uint8_t moveLeft_Flag = FALSSE;
uint8_t moveRight_Flag = FALSSE;
sint16_t Explosion_xPos ;
sint16_t Explosion_yPos ;

Player player = { {SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2, SCREEN_HEIGHT - PLAYER_PADDING}, TRUUE,FALSSE};
Bullet playerBullet[MAX_OF_BULLETS];
Enemy_t enemies[MAX_OF_ENEMIES];
STyp Enemy[4];
/****************************************
 *  LOCAL FUNCTION PROTOTYPES
 ***************************************/

/****************************************
 *  LOCAL FUNCTIONS
 ***************************************/

/****************************************
 *  GLOBAL FUNCTIONS
 ***************************************/
void delay_ms(int milliseconds) {
  int i, j;
  
  for (i = 0; i < milliseconds; i++) {
    for (j = 0; j < 3180; j++) {}  // Adjust this value to create a delay of 1 millisecond
  }
}
void game_Init(void)
{
	uint8_t i;
	Port_Init(&Move_Right_Button);
	Port_Init(&Move_Left_Button);
	Port_Init(&Fire_Button);
	for (i=0; i<MAX_LIVES; i++){
	Port_Init(&led_indicators[i]);
	}
	
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
	//player.active=TRUUE;
	for (i = 0;i<MAX_OF_ENEMIES;i++)
	{
		enemies[i].alive = FALSSE;	
	}
	cpuDriver_EnableGlobalInterrupt();
}

// Draw the player on the screen
void draw_player(void) {

	if(lifes==0){
		GameOver(max_score);
		exit(1);
	}
	if(moveLeft_Flag == TRUUE)
	{
		move_left();
		moveLeft_Flag = FALSSE;
	}
	if(moveRight_Flag == TRUUE)
	{
		move_right();
		moveRight_Flag = FALSSE;
	}
  if(player.active)
	{
		Nokia5110_PrintBMP(player.pos.x, player.pos.y, PlayerShip0, 1);
	}
  
	//Nokia5110_DisplayBuffer(); 
	
 /*  else
	 {
		 Nokia5110_PrintBMP(p.pos.x, p.pos.y, SmallEnemy10PointA, 1);
		 Nokia5110_DisplayBuffer();
     //delay_ms(3000);		 
	 }
*/	
	
}

// Clear the player from the screen
void clear_player(void) {
  Nokia5110_PrintBMP(player.pos.x, player.pos.y, PlayerShip0, 1);
}

// Move the player left
void move_left(void) {
  
	if (player.pos.x >= 0) {
		player.pos.x -= PLAYER_SPEED;
		if (player.pos.x <= 0)
		{
			player.pos.x = 0;
		}

  }
}

// Move the player right
void move_right(void) {
  
  if (player.pos.x <= SCREEN_WIDTH - PLAYER_WIDTH) {
		player.pos.x += PLAYER_SPEED;
		if (player.pos.x >= SCREEN_WIDTH - PLAYER_WIDTH)
		{
			player.pos.x = SCREEN_WIDTH - PLAYER_WIDTH;
		}

  }
  
}
void draw_bullet() {
	uint8_t bu;
	for( bu = 0;bu<MAX_OF_BULLETS;bu++)
	{
		if (playerBullet[bu].active)
		{
			Nokia5110_PrintBMP(playerBullet[bu].pos.x, playerBullet[bu].pos.y, Bullet_Map, 1);
		}
	}
  
}

//Game Over 

void GameOver(int MAX_SCORE){
	Nokia5110_Clear();
  Systick_StopTimer();
  Nokia5110_SetCursor(2, 0);
  Nokia5110_OutString("GAME OVER");
	Nokia5110_SetCursor(2, 2);
	Nokia5110_OutString("Score:");
	Nokia5110_SetCursor(1, 4);
	Nokia5110_OutUDec(MAX_SCORE);
	
	
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



// Clear the player from the screen
void clear_bullet(Bullet p) {
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
	uint8_t j ;
	uint8_t numEnemies;
	numEnemies = (Random() % MAX_OF_ENEMIES )+ 1;
  for ( i = 0; i < numEnemies; i++) {
		
    if (!enemies[i].alive) {
          enemies[i].pos.x = Random32() % (84 - ENEMY_WIDTH + 1);
          enemies[i].pos.y = ENEMY_HEIGHT;
          enemies[i].alive = TRUUE;
					if(i==0)
					{
						if(enemies[i].pos.x - enemies[MAX_OF_ENEMIES-1].pos.x <= 0 && enemies[MAX_OF_ENEMIES-1].pos.x-enemies[i].pos.x < ENEMY_WIDTH)
							{
								enemies[i].pos.x -= ENEMY_WIDTH - (enemies[MAX_OF_ENEMIES-1].pos.x-enemies[i].pos.x );
								continue;
							}
							if(enemies[i].pos.x - enemies[MAX_OF_ENEMIES-1].pos.x > 0 && enemies[MAX_OF_ENEMIES-1].pos.x-enemies[i].pos.x > ENEMY_WIDTH)
							{
								enemies[i].pos.x += ENEMY_WIDTH - (enemies[MAX_OF_ENEMIES-1].pos.x-enemies[i].pos.x );
							}
					}
					for(j=0;j<i;j++)
					{	
						if(i>1)
						{
							if(enemies[i].pos.x - enemies[j].pos.x <= 0 && enemies[j].pos.x-enemies[i].pos.x < ENEMY_WIDTH)
							{
								enemies[i].pos.x -= ENEMY_WIDTH - (enemies[j].pos.x-enemies[i].pos.x );
								continue;
							}
							if(enemies[i].pos.x - enemies[j].pos.x > 0 && enemies[j].pos.x-enemies[i].pos.x > ENEMY_WIDTH)
							{
								enemies[i].pos.x += ENEMY_WIDTH - (enemies[j].pos.x-enemies[i].pos.x );
							}
						}
					}
					break;
        }
  }
}
	
	
	//  uint8_t i ;
//	uint8_t j ;
//	uint8_t numEnemies = (Random()%MAX_OF_ENEMIES) + 1;
//	BOOL occupiedColumns[SCREEN_WIDTH / ENEMY_WIDTH] = {FALSSE};
//  for ( i = 0; i < numEnemies; i++) {
//		uint8_t column;
//    do {
//      column = Random() % (SCREEN_WIDTH / ENEMY_WIDTH);
//    } while (occupiedColumns[column]);
//    for (j = 0; j < MAX_OF_ENEMIES; j++) {
//		if (!enemies[j].alive) {
//          enemies[j].pos.x = column*ENEMY_WIDTH;
//          enemies[j].pos.y = 0;
//          enemies[j].alive = TRUUE;
//					occupiedColumns[column] = TRUUE;
//					break;
//        }
//			}

void draw_explosion()
{
	uint8_t bu;
	
	for(bu=0;bu<MAX_OF_BULLETS;bu++)
	{
		if(playerBullet[bu].collide)
		{
			playerBullet[bu].active=FALSSE;
			playerBullet[bu].collide=FALSSE;
			playerBullet[bu].fired = FALSSE;
			mnk4 = TRUUE;
		}
		if (mnk4 == TRUUE)
		{
			Nokia5110_PrintBMP(Explosion_xPos, Explosion_yPos, smallexplosion0, 0);
			Nokia5110_DisplayBuffer();
		}
			
	}
	 
}
void updatePlayerBullet(void) {
	
  uint8_t bu=0;
	Systick_StopTimer();
	if((++generateCount)%ENEMY_FREQ == 0)
	{
		enemyGenrateFlag = TRUUE;
		generateCount= 0;
	}
	
	player.active=TRUUE;
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
	mnk4 = FALSSE;
	//player.active=TRUUE;

	Systick_StartTimer(BULLET_DELAY,updatePlayerBullet);
	//Systick_StartTimer(BULLET_DELAY,updatePlayerBullet);
}

void check_Enemy_Collide(void)
{
	uint8_t cu;
	uint8_t bu;
	for(cu=0;cu<MAX_OF_BULLETS;cu++)
	{
		
		for(bu = 0;bu<MAX_OF_ENEMIES;bu++)
		{
			if(playerBullet[cu].active&&enemies[bu].alive)
			{
					if( playerBullet[cu].pos.y<=(enemies[bu].pos.y+ENEMY_HEIGHT	))
					{
						if((playerBullet[cu].pos.x>=enemies[bu].pos.x&&playerBullet[cu].pos.x<=(enemies[bu].pos.x+ENEMY_WIDTH))||((playerBullet[cu].pos.x+BULLET_WIDTH)<=(enemies[bu].pos.x+ENEMY_WIDTH)&&(playerBullet[cu].pos.x+BULLET_WIDTH)>=(enemies[bu].pos.x)))
						{
							playerBullet[cu].collide=TRUUE;
							flag=bu;
							flag2=1;
							max_score+=SCORE;
							enemies[bu].alive = FALSSE;
							Explosion_xPos = enemies[flag].pos.x;
							Explosion_yPos = enemies[flag].pos.y;				
							break;
						}
					}
			}
		}
		if(flag2)
		{
     flag2=0;
			break;
		}
	}
}

void check_Player_Collide(void)
{
	uint8_t bu;
	for(bu=0;bu<MAX_OF_ENEMIES;bu++)
	{
			if(enemies[bu].alive)
			{
					if( player.pos.y<=(enemies[bu].pos.y+ENEMY_HEIGHT	))
					{
						if((player.pos.x>=enemies[bu].pos.x&&player.pos.x<=(enemies[bu].pos.x+ENEMY_WIDTH))||((player.pos.x+PLAYER_WIDTH)<=(enemies[bu].pos.x+ENEMY_WIDTH)&&(player.pos.x+PLAYER_WIDTH)>=(enemies[bu].pos.x)))
						{
							//enemies[bu].alive = FALSSE;
							player.collide=TRUUE;
							--lifes;
						
							CLEAR_BIT_PERIPH_BAND(led_indicators[lifes].GPIOx->GPIODATA,led_indicators[lifes].ChannelId);
							//game_Init();
							break;
						}
					}
					
				}
	}
	if(player.collide)
	{
		uint8_t i;
		player.collide=FALSSE;
		if(player.pos.x ==SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2 &&player.pos.y==SCREEN_HEIGHT - PLAYER_HEIGHT - 2)
		 player.active=FALSSE;
		 
		 else 
		 {
			 player.pos.x =SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2 ;
			 player.pos.y=SCREEN_HEIGHT - PLAYER_PADDING;
		 }
		 
		
		
	for (i = 0;i<MAX_OF_BULLETS;i++)
	{
		playerBullet[i].pos.x = 0;
		playerBullet[i].pos.y = 0;
		playerBullet[i].active = FALSSE;	
		playerBullet[i].fired = FALSSE;		
	}
	//player.active=TRUUE;
	for (i = 0;i<MAX_OF_ENEMIES;i++)
	{
		enemies[i].alive = FALSSE;	
	}
	}
}
void draw_enemies(void)
{
	uint8_t bu;
	for( bu = 0;bu<MAX_OF_ENEMIES;bu++)
	{
		if (enemies[bu].alive)
		{
			Nokia5110_PrintBMP(enemies[bu].pos.x, enemies[bu].pos.y, SmallEnemy10PointA, 1);
		}
	}
}



void Init(void){ 
	int i;
  for(i=0;i<4;i++){
    Enemy[i].x = 20*i;
    Enemy[i].y = 10;
    Enemy[i].image[0] = SmallEnemy10PointA;
    Enemy[i].image[1] = SmallEnemy10PointA;
    Enemy[i].life = 1;
   }
}
void Move(void){ int i;
  for(i=0;i<4;i++){
    if(Enemy[i].x < 72){
      Enemy[i].x += 1; // move to right
    }else{
      Enemy[i].life = 0;
    }
  }
}



void Draw(void){ int i;
  Nokia5110_ClearBuffer();
  for(i=0;i<4;i++){
    if(Enemy[i].life > 0){
     Nokia5110_PrintBMP(Enemy[i].x, Enemy[i].y, Enemy[i].image[FrameCount], 0);
    }
  }
  Nokia5110_DisplayBuffer();      // draw buffer
  FrameCount = (FrameCount+1)&0x01; // 0,1,0,1,...
}
void Timer2_Init(unsigned long period){ 
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
  delay = SYSCTL_RCGCTIMER_R;
  TimerCount = 0;
  Semaphore = 0;
  TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period-1;    // 4) reload value
  TIMER2_TAPR_R = 0;            // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 39, interrupt number 23
  NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC
  TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
}

void Timer2A_Handler(void){ 
  TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout
  TimerCount++;
  Move(); 
  Semaphore = 1; // trigger
}

	 
void BYE(void){
	int AnyLife = 1; int i;  
  Init();
  Timer2_Init(80000000/30);  // 30 Hz
 while(AnyLife){
	 
    while(Semaphore == 0){};
    Semaphore = 0; // runs at 30 Hz
    AnyLife = 0;
    for(i=0; i<4 ; i++){
      AnyLife |= Enemy[i].life;
    }
		
    Draw();
		Nokia5110_SetCursor(0, 3);
		Nokia5110_OutString("    BYE ");
			
		}

}


void main_menu_select(void){
		MAIN_MENU();
	 while((!start) &&  (!bye));
		if(start)
		{
			Systick_StartTimer(BULLET_DELAY,updatePlayerBullet);
			return;
		}
		if(bye)
		{
			BYE();
			exit(1);
		}
}

void UART_Init(void){
// as part of Lab 11, modify this program to use UART0 instead of UART1
//                 switching from PC5,PC4 to PA1,PA0
  SYSCTRL->RCGC1 |= SYSCTL_RCGC1_UART0; // activate UART0

  SYSCTRL->RCGC2 |= SYSCTL_RCGC2_GPIOA; // activate port A
  UART0->CTL  &= ~UART_CTL_UARTEN;      // disable UART
	UART0->IBRD = 43;											// IBRD = int(80,000,000 / (16 * 115200)) = int(43.402778)
        
  UART0->FBRD = 26;                    // FBRD = round(0.402778 * 64) = 26
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0->LCRH = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0->CTL |= UART_CTL_UARTEN;       // enable UART
  GPIOA->GPIOAFSEL |= 0x03;           // enable alt funct on PA1,PA0
  GPIOA->GPIODEN |= 0x03;             // enable digital I/O on PA1,PA0
                                        // configure PA1,PA0 as UART0
  GPIOA->GPIOPCTL= (GPIOA->GPIOPCTL&0xFFFFFF00)+0x00000011;
  GPIOA->GPIOAMSEL &= ~0x03;          // disable analog functionality on PA1,PA0
}



/**************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
***************************/


/****************************************
 *  END OF FILE: spaceInvaders.c
 ***************************************/
