#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	// laser particle
	laser1.anim.PushBack({ 21,6,16,10 });
	laser1.anim.loop = false;
	laser1.anim.speed = 0.8f;
	laser1.life = 670;
	laser1.speed.x = 7;
	laser1.fx;//("Laser_Shot_Type-1_(Main_Ships).wav")

	//laser 2_1 particle
	laser2_1.anim.PushBack({ 6,69,10,3 });
	laser2_1.anim.loop = false;
	laser2_1.anim.speed = 0.8f;
	laser2_1.life = 670;
	laser2_1.speed.x = 7;

	//laser 2_2 particle
	laser2_2.anim.PushBack({ 6,84,10,3 });
	laser2_2.anim.loop = false;
	laser2_2.anim.speed = 0.8f;
	laser2_2.life = 670;
	laser2_2.speed.x = -7;

	//laser 3 particle
	laser3.anim.PushBack({ 16,101,32,3 });
	laser3.anim.loop = false;
	laser3.anim.speed = 0.8f;
	laser3.life = 670;
	laser3.speed.x = 7;

	//laser 4_1 particle
	laser4_1.anim.PushBack({ 41,11,13,2 });
	laser4_1.anim.PushBack({ 41,23,13,6 });
	laser4_1.anim.PushBack({ 41,38,13,8 });
	laser4_1.anim.loop = false;
	laser4_1.anim.speed = 0.8f;
	laser4_1.life = 670;
	laser4_1.speed.x = 7;
	laser4_1.speed.y = 3;

	//laser 4_2 particle
	laser4_2.anim.PushBack({ 41,11,13,2 });
	laser4_2.anim.PushBack({ 41,23,13,6 });
	laser4_2.anim.PushBack({ 41,38,13,8 });
	laser4_2.anim.loop = false;
	laser4_2.anim.speed = 0.8f;
	laser4_2.life = 670;
	laser4_2.speed.x = 7;
	laser4_2.speed.y = -3;

	//mini explosion particle
	mini_explosion.anim.PushBack({ 160,133,32,32 });
	mini_explosion.anim.PushBack({ 160,165,32,32 });
	mini_explosion.anim.PushBack({ 160,197,32,32 });
	mini_explosion.anim.PushBack({ 160,229,32,32 });
	mini_explosion.anim.loop = false;
	mini_explosion.anim.speed = 0.8f;

	//big explosion particle
	big_explosion.anim.PushBack({ 41,11,13,2 });
	big_explosion.anim.loop = false;
	big_explosion.anim.speed = 0.8f;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("assets/laser_types.png");
	
	//laser1.fx = App->audio->Loadfx("Assets/Laser_Shot_Type-1_(Main_Ships).wav");
	//laser2.fx = App->audio->Loadfx("Assets/Laser_Shot_Type-2_(Main_Ships).wav");
	//laser3.fx = App->audio->Loadfx("Assets/Laser_Shot_Type-3_(Main_Ships).wav");
	//laser4.fx = App->audio->Loadfx("Assets/Laser_Shot_Type-4_(Main_Ships).wav");
	//explosion.fx = App->audio->Loadfx("Assets/");
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	//App->audio->Unload(laser1.fx);
	//App->audio->Unload(laser2.fx);
	//App->audio->Unload(laser3.fx);
	//App->audio->Unload(laser4.fx);
	//App->audio->Unload(explosion.fx);

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));

			if(p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here!
				//App->audio->PlayFx(p->fx);
				if (App->player1->type_weapon == 1 && App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
					App->audio->Loadfx("Assets/Laser_Shot_Type-1_(Main_Ships).wav");
				if (App->player1->type_weapon == 2 && App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
					App->audio->Loadfx("Assets/Laser_Shot_Type-2_(Main_Ships).wav");
				if (App->player1->type_weapon == 3 && App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
					App->audio->Loadfx("Assets/Laser_Shot_Type-3_(Main_Ships).wav");
				if (App->player1->type_weapon == 4 && App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
					App->audio->Loadfx("Assets/Laser_Shot_Type-4_(Main_Ships).wav");
				
				if (App->player2->type_weapon == 1 && App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN)
					App->audio->Loadfx("Assets/Laser_Shot_Type-1_(Main_Ships).wav");
				if (App->player2->type_weapon == 2 && App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN)
					App->audio->Loadfx("Assets/Laser_Shot_Type-2_(Main_Ships).wav");
				if (App->player2->type_weapon == 3 && App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN)
					App->audio->Loadfx("Assets/Laser_Shot_Type-3_(Main_Ships).wav");
				if (App->player2->type_weapon == 4 && App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN)
					App->audio->Loadfx("Assets/Laser_Shot_Type-4_(Main_Ships).wav");
				
				if (App->player1->destroyed == true || App->player2->destroyed == true)
					App->audio->Loadfx("Assets/Player_Death_Explosion.wav");
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			delete active[i];
			active[i] = nullptr;
			break;
		}
		
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}