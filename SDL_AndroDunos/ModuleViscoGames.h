#ifndef __MODULEVISCOGAMES_H__
#define __MODULEVISCOGAMES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2point.h"

struct SDL_Texture;

class ModuleViscoGames : public Module
{
public:
	ModuleViscoGames();
	~ModuleViscoGames();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * visco;

	SDL_Rect Visco;
	SDL_Rect Games;

	iPoint positionvisco;
	iPoint positiongames;

	int current_time = 0;
	int init_time = 0;

};

#endif // __MODULEVISCOGAMES_H__
