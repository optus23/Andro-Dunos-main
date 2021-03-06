#include "Application.h"
#include "Enemy_FishShip.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include <stdlib.h> //srand
#include <time.h>
#include "SDL/include/SDL.h"

#include "Globals.h"

#define PIXEL 16
#define PIXEL2 33

Enemy_FishShip::Enemy_FishShip(int x, int y) : Enemy(x, y)				//2nd path DOWN to UP
{
	srand(time(NULL));

	up.PushBack({ 105,483,16,16 });
	
	trans.PushBack({ 105 + PIXEL,483,PIXEL,PIXEL });
	trans.PushBack({ 105 + PIXEL * 2,483,PIXEL,PIXEL });
	trans.PushBack({ 105 + PIXEL * 3,483,PIXEL,PIXEL });

	down.PushBack({ 105 + PIXEL * 4,483,PIXEL,PIXEL });


	trans.speed = 0.07;
	down.speed = 1;
	up.loop = false;
	trans.loop = false;
	down.loop = false;

	life = 0.5;

	//Path

	path.PushBack({ 0, 0 }, 120, &up);

	
	path.PushBack({ 0, -2.0f }, 70, &up);

	path.PushBack({ 0, -1.f }, 20, &trans);
	path.PushBack({ 0, -0.5f }, 30, &trans);
	//path.PushBack({ 0, 0.5f }, 0, &trans);
	path.PushBack({ 0, 0.5f }, 20, &down);
	path.PushBack({ 0, 1 }, 20, &down);
	path.PushBack({ 0, 2 }, 100, &down);


	path.PushBack({ -10.0f, 0 }, 5000, &down);//getting out

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	init_time = SDL_GetTicks(); //Timer
}

void Enemy_FishShip::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	current_time = SDL_GetTicks() - init_time; //Set Time 
	

}








Enemy_Water::Enemy_Water(int x, int y) : Enemy(x, y)				//2nd path DOWN to UP
{
	fly.PushBack({ 105 + PIXEL2 * 0,499,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 1,499,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 2,499,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 3,499,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 4,499,PIXEL2,PIXEL2 });
	

	fly.PushBack({ 105 + PIXEL2 * 0,499 + PIXEL2 ,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 1,499 + PIXEL2,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 2,499 + PIXEL2,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 3,499 + PIXEL2,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 4,499 + PIXEL2,PIXEL2,PIXEL2 });

	fly.PushBack({ 105 + PIXEL2 * 0,499 + PIXEL2 * 2,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 1,499 + PIXEL2 * 2,PIXEL2,PIXEL2 });


	fly.speed = 0.1;
	
	fly.loop = false;




	//Path

	path.PushBack({ 0, 0 }, 120, &nothing);
	path.PushBack({ 0, 0.4f }, 420, &fly);
	path.PushBack({ -10.0f, 0 }, 5000, &fly);//getting out



	collider = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_TYPE::COLLIDER_NONE, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	init_time = SDL_GetTicks(); //Timer
}

void Enemy_Water::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	current_time = SDL_GetTicks() - init_time; //Set Time 

}




Enemy_Water2::Enemy_Water2(int x, int y) : Enemy(x, y)				//2nd path DOWN to UP
{
	fly.PushBack({ 105 + PIXEL2 * 0,499,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 1,499,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 2,499,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 3,499,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 4,499,PIXEL2,PIXEL2 });


	fly.PushBack({ 105 + PIXEL2 * 0,499 + PIXEL2 ,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 1,499 + PIXEL2,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 2,499 + PIXEL2,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 3,499 + PIXEL2,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 4,499 + PIXEL2,PIXEL2,PIXEL2 });

	fly.PushBack({ 105 + PIXEL2 * 0,499 + PIXEL2 * 2,PIXEL2,PIXEL2 });
	fly.PushBack({ 105 + PIXEL2 * 1,499 + PIXEL2 * 2,PIXEL2,PIXEL2 });


	fly.speed = 0.1;

	fly.loop = false;




	//Path

	path.PushBack({ 0, 0 }, 332, &nothing);
	path.PushBack({ 0, 0.4f }, 420, &fly);
	path.PushBack({ -10.0f, 0 }, 5000, &fly);//getting out



	collider = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_TYPE::COLLIDER_NONE, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	init_time = SDL_GetTicks(); //Timer
}

void Enemy_Water2::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	current_time = SDL_GetTicks() - init_time; //Set Time 

}


