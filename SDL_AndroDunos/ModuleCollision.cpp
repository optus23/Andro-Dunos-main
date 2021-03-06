#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_WALL][COLLIDER_BONUS] = false;
	matrix[COLLIDER_WALL][COLLIDER_ONE_UP] = false;
	matrix[COLLIDER_WALL][COLLIDER_DEAD] = false;
	matrix[COLLIDER_WALL][COLLIDER_SHIELD] = false;


	matrix[COLLIDER_WALL4][COLLIDER_WALL4] = false;
	matrix[COLLIDER_WALL4][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL4][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_WALL4][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL4][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL4][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_WALL4][COLLIDER_BONUS] = false;
	matrix[COLLIDER_WALL4][COLLIDER_ONE_UP] = false;
	matrix[COLLIDER_WALL4][COLLIDER_DEAD] = false;
	matrix[COLLIDER_WALL4][COLLIDER_SHIELD] = false;


	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_WALL4] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POWERUP] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_BONUS] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ONE_UP] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_DEAD] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_SHIELD] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_WALL4] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_BONUS] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ONE_UP] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_DEAD] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_SHIELD] = true;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL4] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BONUS] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ONE_UP] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_DEAD] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_SHIELD] = false;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL4] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BONUS] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ONE_UP] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_DEAD] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_SHIELD] = true;

	matrix[COLLIDER_BONUS][COLLIDER_WALL] = false;
	matrix[COLLIDER_BONUS][COLLIDER_WALL4] = false;
	matrix[COLLIDER_BONUS][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_BONUS][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_BONUS][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BONUS][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BONUS][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_BONUS][COLLIDER_BONUS] = false;
	matrix[COLLIDER_BONUS][COLLIDER_DEAD] = true;
	matrix[COLLIDER_BONUS][COLLIDER_SHIELD] = false;

	matrix[COLLIDER_POWERUP][COLLIDER_WALL] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_WALL4] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWERUP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_BONUS] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_ONE_UP] = false;
	matrix[COLLIDER_POWERUP][COLLIDER_DEAD] = true;
	matrix[COLLIDER_POWERUP][COLLIDER_SHIELD] = false;

	matrix[COLLIDER_ONE_UP][COLLIDER_WALL] = false;
	matrix[COLLIDER_ONE_UP][COLLIDER_WALL4] = false;
	matrix[COLLIDER_ONE_UP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ONE_UP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ONE_UP][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ONE_UP][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ONE_UP][COLLIDER_BONUS] = false;
	matrix[COLLIDER_ONE_UP][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_ONE_UP][COLLIDER_ONE_UP] = false;
	matrix[COLLIDER_ONE_UP][COLLIDER_DEAD] = true;
	matrix[COLLIDER_ONE_UP][COLLIDER_SHIELD] = false;

	matrix[COLLIDER_DEAD][COLLIDER_WALL] = false;
	matrix[COLLIDER_DEAD][COLLIDER_WALL4] = false;
	matrix[COLLIDER_DEAD][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_DEAD][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_DEAD][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_DEAD][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_DEAD][COLLIDER_BONUS] = true;
	matrix[COLLIDER_DEAD][COLLIDER_POWERUP] = true;
	matrix[COLLIDER_DEAD][COLLIDER_ONE_UP] = true;
	matrix[COLLIDER_DEAD][COLLIDER_SHIELD] = false;
	matrix[COLLIDER_DEAD][COLLIDER_DEAD] = false;

	matrix[COLLIDER_SHIELD][COLLIDER_WALL] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_WALL4] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_SHIELD][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_SHIELD][COLLIDER_BONUS] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_POWERUP] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_ONE_UP] = false;
	matrix[COLLIDER_SHIELD][COLLIDER_SHIELD] = false;
	
}


// Destructor
ModuleCollision::~ModuleCollision()
{}
update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Calculate collisions
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return UPDATE_CONTINUE;
}
// Called before render is available
update_status ModuleCollision::Update()
{

	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	if (debug == true)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_WALL4: //blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_SHIELD: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY_SHOT: // cyan
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_BONUS: //magenta
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		case COLLIDER_POWERUP: //magenta
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		case COLLIDER_ONE_UP: //black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case COLLIDER_DEAD: //Grey
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	if (r.x > rect.x + rect.w || r.x + r.w<rect.x || r.y>rect.y + rect.h || r.y + r.h < rect.y)
		return false;
	else return true;

}