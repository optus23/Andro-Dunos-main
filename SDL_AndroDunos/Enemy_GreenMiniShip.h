#ifndef __ENEMY_GREENMINISHIP_H__
#define __ENEMY_GREENMINISHIP_H__

#include "Enemy.h"
#include "path.h"


class Enemy_GreenMiniShip1 : public Enemy
{
private:

	Path path;
	iPoint original_pos;
	int original_y = 0;
	Animation left, right, right_go;

public:

	Enemy_GreenMiniShip1(int x, int y);

	void Move();
};

class Enemy_GreenMiniShip2 : public Enemy
{
private:

	Path path;
	iPoint original_pos;
	int original_y = 0;
	Animation left, right, right_go;

public:

	Enemy_GreenMiniShip2(int x, int y);

	void Move();
};

#endif // __ENEMY_GREENMINISHIP_H__
#pragma once
