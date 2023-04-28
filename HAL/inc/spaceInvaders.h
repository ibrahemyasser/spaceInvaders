#ifndef SPACE_INVADERS_H_
#define SPACE_INVADERS_H_

#include "Std_Types.h"

#define SCREEN_WIDTH 			84
#define SCREEN_HEIGHT 		48

#define PLAYER_WIDTH 			18
#define PLAYER_HEIGHT 		8

#define BULLET_WIDTH			4
#define BULLET_HEIGHT			6

#define PLAYER_SPEED 2
#define PLAYER_BULLET_SPEED 5

#define BULLET_DELAY				500
#define MAX_OF_BULLETS			5

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
  BOOL active;
	BOOL fired;
} Bullet;

typedef struct {
  Point pos;
  uint16_t score;
} Player;



extern Player player;
extern Bullet playerBullet[MAX_OF_BULLETS];

extern uint8_t nextBullet ;
extern uint8_t bulletsCounter;

extern const unsigned char PlayerShip0[] ;
extern const unsigned char Bullet_Map[] ;

void draw_player(Player p) ;
void clear_player(Player p); 
void move_left(void); 
void move_right(void);
void game_Init(void);
void game_InterruptInit(void);
void clear_bullet(Player p);
void draw_bullet(void);
void updatePlayerBullet(void);
void fire_PlayerBullet(void);




#endif
