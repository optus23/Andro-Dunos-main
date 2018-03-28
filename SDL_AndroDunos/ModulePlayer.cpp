#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"


ModulePlayer::ModulePlayer()
{
	position.x = SCREEN_WIDTH/2;
	position.y = SCREEN_HEIGHT/2;

	idle.PushBack({ 94,108,27,17 });

	up.PushBack({ 94,87,27,15 });
	up.PushBack({ 94,66,27,15 });
	up.speed = 0.02f;

	down.PushBack({ 94,131,27,16 });
	down.PushBack({ 94,153,27,17 });
	down.speed = 0.02f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ships.png");
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1) {
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == 1) {
		current_animation = &up;
		position.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == 0)
		up.reset();
	if (App->input->keyboard[SDL_SCANCODE_S] == 1) {
		current_animation = &down;
		position.y += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 0)
		down.reset();

	
	// Draw everything --------------------------------------
	SDL_Rect r;
	if (current_animation == &up || current_animation == &down) {
		r = current_animation->end_animation();
	}
	else r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}