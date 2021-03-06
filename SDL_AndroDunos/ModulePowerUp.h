#ifndef __MODULEPOWERUP_H__
#define __MODULEPPOWERUP_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_ITEMS 10

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

enum TYPE_POWERUP {
	S,
	B,
	U,
	M
};

struct Item
{
	Animation anim;
	uint fx = 0;
	fPoint position;
	fPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	Collider* collider = nullptr;
	int n_collisions;
	bool screen_col;
	bool colup = false;
	bool coldown = false;
	bool colleft = false;
	bool colright = true;
	TYPE_POWERUP powert;

	Item();
	Item(const Item& p);
	~Item();
	bool Update();
};

class ModulePowerUp : public Module
{
public:
	ModulePowerUp();
	~ModulePowerUp();

	bool Start();
	update_status Update();
	bool CleanUp();
	virtual void OnCollision(Collider* c1, Collider* c2);

	void AddPowerUp(const Item& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	Item* active[MAX_ACTIVE_ITEMS];

	uint powerup_fx, bonus_fx, one_up_fx;

public:
	Item bonus;
	Item powerup;
	Item one_up;

	
};

#endif // __MODULEPARTICLES_H__