#include "Application.h"
#include "Enemy_PowerUp.h"
#include "ModuleCollision.h"
#include "Globals.h"
#include "ModulePowerUp.h"
#include "ModulePlayer1.h"

#define PIXEL 26


Enemy_PowerUp::Enemy_PowerUp(int x, int y) : Enemy(x, y)
{
	left.PushBack({ 153 + (PIXEL * 0), 0, PIXEL, PIXEL }); //left
	left.PushBack({ 153 + (PIXEL * 1), 0, PIXEL, PIXEL });

	transition1.PushBack({ 153 + (PIXEL * 2), 0, PIXEL, PIXEL }); //transition1

	left_down.PushBack({ 153 + (PIXEL * 3), 0, PIXEL, PIXEL }); //left_down
	left_down.PushBack({ 153 + (PIXEL * 4), 0, PIXEL, PIXEL });

	transition2.PushBack({ 153 + (PIXEL * 5), 0, PIXEL, PIXEL }); //transition2
	transition2.PushBack({ 153 + (PIXEL * 6), 0, PIXEL, PIXEL });
	transition2.PushBack({ 153 + (PIXEL * 7), 0, PIXEL, PIXEL });
	 
	left_up.PushBack({ 153 + (PIXEL * 8), 0, PIXEL, PIXEL });//left_up
	left_up.PushBack({ 153 + (PIXEL * 9), 0, PIXEL, PIXEL });
	
	transition3.PushBack({ 153 + (PIXEL * 10), 0, PIXEL, PIXEL }); //transition3
	transition3.PushBack({ 153 + (PIXEL * 0), PIXEL, PIXEL, PIXEL });     //2nd row
	transition3.PushBack({ 153 + (PIXEL * 1), PIXEL, PIXEL, PIXEL });
	transition3.PushBack({ 153 + (PIXEL * 2), PIXEL, PIXEL, PIXEL });
	transition3.PushBack({ 153 + (PIXEL * 3), PIXEL, PIXEL, PIXEL });
	transition3.PushBack({ 153 + (PIXEL * 4), PIXEL, PIXEL, PIXEL });
	transition3.PushBack({ 153 + (PIXEL * 5), PIXEL, PIXEL, PIXEL });
	transition3.PushBack({ 153 + (PIXEL * 6), PIXEL, PIXEL, PIXEL });
	transition3.PushBack({ 153 + (PIXEL * 7), PIXEL, PIXEL, PIXEL });
	transition3.PushBack({ 153 + (PIXEL * 8), PIXEL, PIXEL, PIXEL });
	transition3.PushBack({ 153 + (PIXEL * 9), PIXEL, PIXEL, PIXEL });
	transition3.PushBack({ 153 + (PIXEL * 10), PIXEL, PIXEL, PIXEL });
	transition3.PushBack({ 153 + (PIXEL * 0), PIXEL * 2, PIXEL, PIXEL });//3th row
	transition3.PushBack({ 153 + (PIXEL * 1), PIXEL * 2, PIXEL, PIXEL });

	right.PushBack({ 153 + (PIXEL * 1), PIXEL * 2, PIXEL, PIXEL }); //right
	right.PushBack({ 153 + (PIXEL * 2), PIXEL * 2, PIXEL, PIXEL });

	transition4.PushBack({ 153 + (PIXEL * 3), PIXEL * 2, PIXEL, PIXEL }); //transition 4
	transition4.PushBack({ 153 + (PIXEL * 4), PIXEL * 2, PIXEL, PIXEL });
	transition4.PushBack({ 153 + (PIXEL * 5), PIXEL * 2, PIXEL, PIXEL });
	transition4.PushBack({ 153 + (PIXEL * 6), PIXEL * 2, PIXEL, PIXEL });
	transition4.PushBack({ 153 + (PIXEL * 7), PIXEL * 2, PIXEL, PIXEL });
	transition4.PushBack({ 153 + (PIXEL * 8), PIXEL * 2, PIXEL, PIXEL });
	transition4.PushBack({ 153 + (PIXEL * 9), PIXEL * 2, PIXEL, PIXEL });
	transition4.PushBack({ 153 + (PIXEL * 10), PIXEL * 2, PIXEL, PIXEL });
	transition4.PushBack({ 153 + (PIXEL * 0), PIXEL * 3, PIXEL, PIXEL });       //4th row
	transition4.PushBack({ 153 + (PIXEL * 1), PIXEL * 3, PIXEL, PIXEL });
	transition4.PushBack({ 153 + (PIXEL * 2), PIXEL * 3, PIXEL, PIXEL });
	transition4.PushBack({ 153 + (PIXEL * 3), PIXEL * 3, PIXEL, PIXEL });
	transition4.PushBack({ 153 + (PIXEL * 4), PIXEL * 3, PIXEL, PIXEL });
	transition4.PushBack({ 153 + (PIXEL * 5), PIXEL * 3, PIXEL, PIXEL });
	transition4.PushBack({ 153 + (PIXEL * 6), PIXEL * 3, PIXEL, PIXEL });
	transition4.PushBack({ 153 + (PIXEL * 0), 0, PIXEL, PIXEL });

	left.speed = 0.25f;
	transition1.speed = 0.25f;
	left_down.speed = 0.25f;
	transition2.speed = 0.25f;
	left_up.speed = 0.25f;
	transition3.speed = 0.25f;
	right.speed = 0.25f;
	transition4.speed = 0.25f;

	transition1.loop = false;
	transition2.loop = false;
	transition3.loop = false;
	transition4.loop = false;

	animation = &left;
	animation = &transition1;
	animation = &left_down;
	animation = &transition2;
	animation = &left_up;
	animation = &transition3;
	animation = &right;
	animation = &transition4;


	path.PushBack({ -1.0f, 0.0f }, 40, &left);//Important
	path.PushBack({ 1.0f, 0.0f }, 20, &transition1);
	path.PushBack({ -1.0f, 1.0f }, 25, &left_down);//Important
	path.PushBack({ 1.0f, 0.0f }, 20, &transition2);
	path.PushBack({ -1.0f, -1.0f }, 25, &left_up);//Important
	path.PushBack({ 1.0f, 0.0f }, 45, &transition3);
	path.PushBack({ 3.0f, 0.0f }, 70, &right);//Important Important
	path.PushBack({ 1.0f, 0.0f }, 45, &transition4);

	path.PushBack({ -1.0f, 0.0f }, 20, &left);//Important
	path.PushBack({ 1.0f, 0.0f }, 20, &transition1);
	path.PushBack({ -1.0f, 1.0f }, 25, &left_down);//Important
	path.PushBack({ 1.0f, 0.0f }, 20, &transition2);
	path.PushBack({ -1.0f, -1.0f }, 25, &left_up);//Important
	path.PushBack({ 1.0f, 0.0f }, 45, &transition3);
	path.PushBack({ 3.0f, 0.0f }, 70, &right);//Important Important
	path.PushBack({ 1.0f, 0.0f }, 45, &transition4);

	path.PushBack({ -1.0f, 0.0f }, 20, &left);//Important
	path.PushBack({ 1.0f, 0.0f }, 20, &transition1);
	path.PushBack({ -1.0f, 1.0f }, 25, &left_down);//Important
	path.PushBack({ 1.0f, 0.0f }, 20, &transition2);
	path.PushBack({ -1.0f, -1.0f }, 25, &left_up);//Important
	path.PushBack({ 1.0f, 0.0f }, 45, &transition3);
	path.PushBack({ 3.0f, 0.0f }, 70, &right);//Important Important
	path.PushBack({ 1.0f, 0.0f }, 45, &transition4);

	path.PushBack({ -1.0f, 0.0f }, 20, &left);//Important
	path.PushBack({ 1.0f, 0.0f }, 20, &transition1);
	path.PushBack({ -1.0f, 1.0f }, 25, &left_down);//Important
	path.PushBack({ 1.0f, 0.0f }, 20, &transition2);
	path.PushBack({ -1.0f, -1.0f }, 25, &left_up);//Important
	path.PushBack({ 1.0f, 0.0f }, 45, &transition3);
	path.PushBack({ 3.0f, 0.0f }, 70, &right);//Important Important
	path.PushBack({ 1.0f, 0.0f }, 45, &transition4);

	path.PushBack({ -1.0f, 0.0f }, 500, &left); // you're no longer welcome here.

	collider = App->collision->AddCollider({ 0, 0, 26, 26 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_PowerUp::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
	part_power_up = 1;
}

void Enemy_PowerUp::OnCollision(Collider* c1) {

	App->powerup->AddPowerUp(App->powerup->powerup_S, position.x, position.y, COLLIDER_POWER_S);
}