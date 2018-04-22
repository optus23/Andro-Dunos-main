#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "Enemy_WavingShip.h"
#include "Enemy_HorizontalRocket.h"
#include "Enemy_PowerUp.h"
#include "Enemy_MiniMiniBoss.h"


#define MAX_ENEMIES 200

enum ENEMY_TYPES
{
	NO_TYPE,
	WAVINGSHIP,
	HORIZONTALROCKET,
	POWERUP,
	MINIMINIBOSS
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
	bool drop;

};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	virtual void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y, bool drop = false);

	uint score = 0;

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;

	uint big_explosion_fx;
};

#endif // __ModuleEnemies_H__