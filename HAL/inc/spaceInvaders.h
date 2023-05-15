#ifndef SPACE_INVADERS_H_
#define SPACE_INVADERS_H_

#include "Std_Types.h"
#include "../MCAL/PORT/Inc/Port_Cfg.h"

#define TIMER2_CFG_R            (*((volatile unsigned long *)0x40032000))
#define TIMER2_TAMR_R           (*((volatile unsigned long *)0x40032004))
#define TIMER2_TBMR_R           (*((volatile unsigned long *)0x40032008))
#define TIMER2_CTL_R            (*((volatile unsigned long *)0x4003200C))
#define TIMER2_SYNC_R           (*((volatile unsigned long *)0x40032010))
#define TIMER2_IMR_R            (*((volatile unsigned long *)0x40032018))
#define TIMER2_RIS_R            (*((volatile unsigned long *)0x4003201C))
#define TIMER2_MIS_R            (*((volatile unsigned long *)0x40032020))
#define TIMER2_ICR_R            (*((volatile unsigned long *)0x40032024))
#define TIMER2_TAILR_R          (*((volatile unsigned long *)0x40032028))
#define TIMER2_TBILR_R          (*((volatile unsigned long *)0x4003202C))
#define TIMER2_TAMATCHR_R       (*((volatile unsigned long *)0x40032030))
#define TIMER2_TBMATCHR_R       (*((volatile unsigned long *)0x40032034))
#define TIMER2_TAPR_R           (*((volatile unsigned long *)0x40032038))
#define TIMER2_TBPR_R           (*((volatile unsigned long *)0x4003203C))
#define TIMER2_TAPMR_R          (*((volatile unsigned long *)0x40032040))
#define TIMER2_TBPMR_R          (*((volatile unsigned long *)0x40032044))
#define TIMER2_TAR_R            (*((volatile unsigned long *)0x40032048))
#define TIMER2_TBR_R            (*((volatile unsigned long *)0x4003204C))
#define TIMER2_TAV_R            (*((volatile unsigned long *)0x40032050))
#define TIMER2_TBV_R            (*((volatile unsigned long *)0x40032054))
#define TIMER2_RTCPD_R          (*((volatile unsigned long *)0x40032058))
#define TIMER2_TAPS_R           (*((volatile unsigned long *)0x4003205C))
#define TIMER2_TBPS_R           (*((volatile unsigned long *)0x40032060))
#define TIMER2_TAPV_R           (*((volatile unsigned long *)0x40032064))
#define TIMER2_TBPV_R           (*((volatile unsigned long *)0x40032068))
#define TIMER2_PP_R             (*((volatile unsigned long *)0x40032FC0))
#define NVIC_PRI5_R             (*((volatile unsigned long *)0xE000E414))
#define SYSCTL_RCGCTIMER_R      (*((volatile unsigned long *)0x400FE604))
#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))


#define SCREEN_WIDTH 			84
#define SCREEN_HEIGHT 		48

#define PLAYER_WIDTH 			18
#define PLAYER_HEIGHT 		8

#define BULLET_WIDTH			4
#define BULLET_HEIGHT			6

#define PLAYER_SPEED 2
#define PLAYER_BULLET_SPEED 2
#define PLAYER_PADDING			4

#define BULLET_DELAY				100
#define MAX_OF_BULLETS			2

#define MAX_OF_ENEMIES			4
#define ENEMY_SPEED					2
#define ENEMY_FREQ					3

#define SCORE								10
#define MAX_LIVES           3

#define ENEMY_WIDTH					0x10
#define ENEMY_HEIGHT				0x0A
#define SYSCTL_RCGC2_GPIOA      0x00000001  // port A Clock Gating Control
#define UART_CTL_UARTEN         0x00000001  // UART Enable
#define UART_LCRH_WLEN_8        0x00000060  // 8 bits
#define UART_LCRH_FEN           0x00000010  // UART Enable FIFOs

#define SYSCTL_RCGC1_UART0      0x00000001  // UART0 Clock Gating Control
typedef enum 
{
	FALSSE=0,
	TRUUE
}BOOL;


// Define a struct to store player position
typedef struct {
  sint16_t x;
  sint16_t y;
} Point;

typedef struct {
  Point pos;
  BOOL alive;
} Enemy_t;
typedef struct {
  Point pos;
  BOOL active;
	BOOL fired;
	BOOL collide;
} Bullet;

typedef struct {
  Point pos;
 // uint16_t score;
	BOOL active;
	//BOOL fired;
	BOOL collide;
} Player;
typedef struct  {
  unsigned long x;      // x coordinate
  unsigned long y;      // y coordinate
  const unsigned char *image[2]; // two pointers to images
  long life;            // 0=dead, 1=alive
}STyp;         


extern Port_ConfigType Move_Right_Button;
extern Port_ConfigType Move_Left_Button;
extern Port_ConfigType Fire_Button;	
	
extern Port_ConfigType led_indicators [MAX_LIVES];
extern GPIO_EXTI_ConfigType Right_Button;
extern GPIO_EXTI_ConfigType Left_Button;
extern GPIO_EXTI_ConfigType Fire_EXTI_Button;
	
extern IntCtr_Config Int_RightButton;
extern IntCtr_Config Int_LeftButton;
extern IntCtr_Config Int_FireButton;

extern Player player;
extern Bullet playerBullet[MAX_OF_BULLETS];

extern uint8_t nextBullet ;
extern uint8_t bulletsCounter;
extern uint8_t enemyGenrateFlag;

extern uint8_t mnk4;
extern uint8_t moveLeft_Flag ;
extern uint8_t moveRight_Flag ;

extern uint8_t start ;
extern uint8_t bye	;

extern const unsigned char PlayerShip0[] ;
extern const unsigned char Bullet_Map[] ;

void draw_player(void);
void clear_player(void); 
void move_left(void); 
void move_right(void);
void game_Init(void);
void game_InterruptInit(void);
void clear_bullet(Bullet p);
void draw_bullet(void);
void updatePlayerBullet(void);
void fire_PlayerBullet(void);
void generateEnemies(void);
void draw_enemies(void);
void GameOver(int MAX_SCORE);
void MAIN_MENU(void);
void BYE(void);
void main_menu_select(void);
void Draw(void);
void Move(void);
void Init(void);
void draw_explosion(void);
void check_Player_Collide(void);
void check_Enemy_Collide(void);

#endif
