#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleStage1.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "SDL/include/SDL.h"
#include <stdio.h>

ModulePlayer1::ModulePlayer1()
{
	state = CLEAR;

	animationShip = nullptr;

	idle.PushBack({ 0,48,39,17 });
	idle.PushBack({ 42,48,39,17 });
	idle.PushBack({ 85,48,39,17 });


	up.PushBack({ 2,4,39,15 });
	up.PushBack({ 41,4,39,15 });
	up.PushBack({ 85,4,39,15 });
	
	up.speed = 0.5f;

	upidle.PushBack({ 85,24,39,15 });
	upidle.PushBack({ 43,24,39,15 });
	upidle.PushBack({ 2,24,39,15 });


	upidle.speed = 0.5f;
	
	down.PushBack({ 2,104,39,17 });
	down.PushBack({ 43,104,39,17 });
	down.PushBack({ 85,104,39,17 });


	down.speed = 0.5f;

	downidle.PushBack({ 0,76,39,16 });
	downidle.PushBack({ 43,76,39,16 });
	downidle.PushBack({ 85,76,39,16 });

	downidle.speed = 0.5f;

	clear.PushBack({ 0,48,39,17 });
	clear.PushBack({ 0,0,10,20 });

	clear.speed = 0.4f;
}

ModulePlayer1::~ModulePlayer1()
{}

// Load assets
bool ModulePlayer1::Start()
{
	LOG("Loading player textures");
	bool ret = true;

	init_time = SDL_GetTicks(); //Timer
	

	graphics = App->textures->Load("assets/Sprites/ships.png");
	position.x = 0;
	position.y = SCREEN_HEIGHT / 3;

	destroyed = false;
	type_weapon = 1;
	powerup = 1;
	player_col = App->collision->AddCollider({ position.x,position.y,39,17 }, COLLIDER_PLAYER, this);
	hp = 3;
	font_score = App->fonts->Load("Assets/Fonts/font_score.png", "1234567890P", 1);
	score = 0;
	god_mode_die = true;
	laser1 = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type-1_(Main_Ships).wav");
	laser2 = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type-2_(Main_Ships).wav");
	laser3 = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type-3_(Main_Ships).wav");
	laser4 = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type-4_(Main_Ships).wav");
	explosion_player = App->audio->Loadfx("Assets/Audio/Player_Death_Explosion.wav");
	type_change = App->audio->Loadfx("Assets/Audio/Laser_Shot_Type_CHANGE.wav");

	return ret;
}

// Update: draw background
update_status ModulePlayer1::Update()
{
	current_time = SDL_GetTicks() - init_time;
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
		if (god_mode == false) {
			player_col->type = COLLIDER_NONE;
			god_mode = true;
		}
		else if (god_mode == true) {
			god_mode = false;
			player_col->type = COLLIDER_PLAYER;
		}
	}

	//Respawn 
	if (god_mode_die == true) {
		if (current_time < 2500) {
			player_col->type = COLLIDER_NONE;
			if (position.x <= App->stage1->camera_limit.xi + 44)
				position.x++;
		}
		
		else {
			player_col->type = COLLIDER_PLAYER;
			god_mode_die = false;
			state = IDLE;
		}	
	}
	// input
		//controller input
	if (!SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_A))
		stillpressed_a = false;

	if (SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_A) && !stillpressed_a) {
		shoot = true;
		stillpressed_a = true;
	}
	if (!SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_X))
		stillpressed_x = false;

	if (SDL_GameControllerGetButton(App->input->controller1, SDL_CONTROLLER_BUTTON_X) && !stillpressed_x) {
		change = true;
		stillpressed_x = true;
	}
		//change weapon
	if (App->input->keyboard[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN || change) {
		change = false;
		App->audio->PlayFx(type_change);
		type_weapon++;
		if (type_weapon == 5)
			type_weapon = 1;
	}
		//powerup+
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
		powerup++;
	if (powerup > 4)
		powerup = 4;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || shoot)
		Shoot();
	
	if (SDL_GameControllerGetAxis(App->input->controller1, SDL_CONTROLLER_AXIS_LEFTX) > 100)
		position.x += speedMoveShip;

	if (SDL_GameControllerGetAxis(App->input->controller1, SDL_CONTROLLER_AXIS_LEFTX) < -100)
		position.x -= speedMoveShip;

	if (SDL_GameControllerGetAxis(App->input->controller1, SDL_CONTROLLER_AXIS_LEFTY) < -100)
	{
		position.y -= speedMoveShip;
		counterMoved += speedMoveShip;

		if (state == IDLE_UP && counterMoved > METERSMOVED || state == UP && counterMoved > METERSMOVED)
			state = UP;
		else
			state = IDLE_UP;
	}
	if (SDL_GameControllerGetAxis(App->input->controller1, SDL_CONTROLLER_AXIS_LEFTY) > 100)
	{
		position.y += speedMoveShip;
		counterMoved2 += speedMoveShip;

		if (state == IDLE_DOWN && counterMoved2 > METERSMOVED || state == DOWN && counterMoved2 > METERSMOVED)
			state = DOWN;
		else
			state = IDLE_DOWN;
	}

	if (!App->input->keyboard[SDL_SCANCODE_S] && !App->input->keyboard[SDL_SCANCODE_W])
	{
		if (state == DOWN)
			state = IDLE_DOWN;

		else if (state == UP)
			state = IDLE_UP;

		else if (state == IDLE_DOWN)
			counterReturn++;

		else if ( state == IDLE_UP)
			counterReturn2++;

		if (counterReturn > TIMERETURNIDDLE || counterReturn2 > TIMERETURNIDDLE)
		{
			counterReturn = 0;
			counterReturn2 = 0;
			state = IDLE;
		}

	}

	switch (state)
	{
	case DOWN:		
		animationShip = &down;
		break;
	case IDLE_DOWN:
		animationShip = &downidle;
		break;
	case IDLE:
		animationShip = &idle;

		if (counterMoved > 0 || counterMoved2 > 0)
		{
			counterMoved = 0;
			counterMoved2 = 0;
		}
		
		break;
	case IDLE_UP:
		animationShip = &upidle;
		break;
	case UP:
		animationShip = &up;
		break;
	case CLEAR:
		animationShip = &clear;
		break;
	}
	player_col->SetPos(position.x, position.y);
	// Draw everything --------------------------------------
	SDL_Rect ship;

	ship = animationShip->GetCurrentFrame();

	if (!destroyed && dead == false)
		App->render->Blit(graphics, position.x, position.y, &ship);
	
	sprintf_s(score_text, 10, "%7d", score);
	
	// Blit the text of the score in at the bottom of the screen	
	App->fonts->BlitText(30, 6, font_score, score_text);
	App->fonts->BlitText(10, 6, font_score, "P1");

	return UPDATE_CONTINUE;
}

bool ModulePlayer1::CleanUp() {
	App->textures->Unload(graphics);
	App->collision->CleanUp();
	App->particles->CleanUp();
	App->fonts->UnLoad(font_score);
	App->audio->UnLoadFx(type_change);
	App->audio->UnLoadFx(explosion_player);
	App->audio->UnLoadFx(laser4);
	App->audio->UnLoadFx(laser3);
	App->audio->UnLoadFx(laser2);
	App->audio->UnLoadFx(laser1);



	if (player_col != nullptr)
		player_col->to_delete = true;

	return true;
}

void ModulePlayer1::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == player_col && destroyed == false && App->fade->IsFading() == false && c2->type != COLLIDER_TYPE::COLLIDER_BONUS && c2->type != COLLIDER_TYPE::COLLIDER_POWER_S)
	{
		App->audio->PlayFx(explosion_player);
		hp--;
		animationShip->reset();
		App->particles->AddParticle(App->particles->explosion_player1, position.x + 15, position.y - 2);
		if (hp <= 0 && App->player2->hp <= 0) {
			App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->gameover);
			destroyed = true;
		}
		else {
			
			god_mode_die = true;
			state = CLEAR;
			init_time = SDL_GetTicks();
			position.x = App->stage1->camera_limit.xi;
			position.y = App->stage1->camera_limit.yi+71;
		}
	}
}

void ModulePlayer1::Shoot() {
	shoot = false;

	switch (type_weapon) {
	case 1:
		switch (powerup) {
		case 1:
			App->particles->AddParticle(App->particles->laser1, position.x + 38, position.y + 3, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser1);
			break;
		case 2:
			App->particles->AddParticle(App->particles->laser1, position.x + 33, position.y, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser1, position.x + 38, position.y + 8, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser1, position.x + 33, position.y + 16, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser1);
			break;
		case 3:
			App->particles->AddParticle(App->particles->laser1, position.x + 33, position.y, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser1_1, position.x + 38, position.y + 8, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser1, position.x + 33, position.y + 18, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser1);
			break;
		case 4:
			App->particles->AddParticle(App->particles->laser1_1, position.x + 33, position.y, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser1_1, position.x + 38, position.y + 9, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser1_1, position.x + 33, position.y + 18, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser1);
			break;
		}
		break;
	case 2:
		switch (powerup) {
		case 1:
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser2);
			break;
		case 2:
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 6, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 13, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser2);
			break;
		case 3:
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 6, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 13, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_diagonal1, position.x + 10, position.y + 3, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_diagonal2, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser2);
			break;
		case 4:
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 6, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_1, position.x + 38, position.y + 13, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_diagonal1, position.x + 10, position.y + 3, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_diagonal2, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_3, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser2);
			break;
		}
		break;
	case 3:
		switch (powerup) {
		case 1:
			App->particles->AddParticle(App->particles->laser3, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser3);
			break;
		case 2:
			App->particles->AddParticle(App->particles->laser3_1, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser3_2, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser3);
			break;
		case 3:
			App->particles->AddParticle(App->particles->laser3_1, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser3_2, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser3_3, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser3_4, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser3);
			break;
		case 4:
			App->particles->AddParticle(App->particles->laser3_5, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser3_6, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser3_7, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser3_8, position.x + 25, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser3);
			break;
		}
		break;
	case 4:
		switch (powerup) {
		case 1:
			App->particles->AddParticle(App->particles->laser4_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_2, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser4);
			break;
		case 2:
			App->particles->AddParticle(App->particles->laser4_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_2, position.x + 42, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_3, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser4);
			break;
		case 3:
			App->particles->AddParticle(App->particles->laser4_1_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_2_1, position.x + 42, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_3_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser4);
			break;
		case 4:
			App->particles->AddParticle(App->particles->laser4_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_2, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_1_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_2_1, position.x + 38, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser4);
			break;
		}
		break;
	}
}