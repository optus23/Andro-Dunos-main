#ifndef __ModulePlayer1_H__
#define __ModulePlayer1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define METERSMOVED 50
#define TIMERETURNIDDLE 10

struct SDL_Texture;
struct Collider;

class ModulePlayer1 : public Module
{
public:
	ModulePlayer1();
	~ModulePlayer1();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider*, Collider*);

public:

	PLAYER_STATE_MOVE state;
	int speedMoveShip = 2;
	Animation *animationShip;

	int counterMoved = 0;
	int counterMoved2 = 0;
	int counterReturn = 0;
	int counterReturn2 = 0;

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation upidle;
	Animation up;
	Animation downidle;
	Animation down;
	Animation clear;
	iPoint position;
	Collider* player_col = nullptr;

	uint laser1, laser2, laser3, laser4, explosion_player, type_change;

	bool destroyed = false;
	bool dead = false;
	bool god_mode = false;
	bool god_mode_die = false;

	bool shoot = false;
	bool change = false;
	bool stillpressed_a = false;
	bool stillpressed_x = false;

	int type_weapon = 0;
	int powerup=1;
	int hp;

	int current_time = 0;
	int init_time = 0;

	int font_score = 1;
	char score_text[10];
	uint score = 0;
};
#endif