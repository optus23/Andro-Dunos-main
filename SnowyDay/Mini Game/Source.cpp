#include "SDL/include/SDL.h"
#include "SDL/include/SDL_image.h"

#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2_image.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")
#define HEIGHT 4320
#define WEIGHT 600
#define NSHOT 100

void shotInit(SDL_Rect a[]) {
	for (int i = 0; i < NSHOT; i++) {
		a[i].h = 26;
		a[i].w = 14;
		a[i].x = 0 - a[0].w;
		a[i].y = 0 - a[0].h;
	}
}
	
int main(int argc, char* argv[]) {
		//INICIALIZAR
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	//Audio

		//LOCAL VAR
	int x_ball = 275, y_ball = 50, x_background = 0, y_background = 0, x_pickup = 0, y_pickup = 0, x_snowman = 0, y_snowman = 525, x_sled = 255, y_sled = 0; //Position
	int cont_shot = 0, life = 3;
	int ball_h = 50, ball_w = 50, cont_background = 0; //Part of h&w
	bool loop=true, key_left=false, key_right=false, key_a = false, key_d = false, mov_e = true, shoot = false; //Part of Loop
	int vel=4, cont=0; //Time

		//SDL
	SDL_Event event;
	SDL_Rect background;
	SDL_Rect ball;
	SDL_Rect pickup;
	SDL_Rect snowman;
	SDL_Rect sled;
	SDL_Rect enemy;
	SDL_Rect shot[NSHOT];
	SDL_Rect heart;

	SDL_Window *window = SDL_CreateWindow(
		"SnowyDay", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 1000, SDL_WINDOW_SHOWN);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC); //Important

	SDL_Texture *texture_background = IMG_LoadTexture(renderer, "Backgorund_Skystar_BIG2.png");
	SDL_Texture *texture_ball = IMG_LoadTexture(renderer, "Snowball.png");
	SDL_Texture *texture_pickup = IMG_LoadTexture(renderer, "Snow_Pick_Up.png");
	SDL_Texture *texture_snowman = IMG_LoadTexture(renderer, "Snowman.png");
	SDL_Texture *texture_sled = IMG_LoadTexture(renderer, "Trineo.png");
	SDL_Texture *mario_tx = IMG_LoadTexture(renderer, "mario.png");
	SDL_Texture *shot_tx = IMG_LoadTexture(renderer, "fireshot.png");
	SDL_Texture *heart_tx = IMG_LoadTexture(renderer, "heart.png");

		//HEIGHT & WIDTH
	background.h = HEIGHT;
	background.w = WEIGHT;
	pickup.h = HEIGHT;
	pickup.w = WEIGHT;
	snowman.h = HEIGHT;
	snowman.w = WEIGHT;
	sled.h = HEIGHT;
	sled.w = WEIGHT;
	ball.h = ball_h;
	ball.w = ball_w;
	enemy.h = 16*4;
	enemy.w = 12*4;
	enemy.x = 30;
	enemy.y = 1000 - enemy.h - 50;
	shotInit(shot);
	snowman.x = x_snowman;
	snowman.y = y_snowman;
	sled.x = x_sled;
	sled.y = y_sled;
	heart.x = 15;
	heart.y = 950;
	heart.w = 11*5;
	heart.h = 9*5;

		//LOOP PRINCIPAL
	while (loop) {

		SDL_RenderClear(renderer);

		ball.x = x_ball;
		ball.y = y_ball;
		background.x = x_background;
		background.y = y_background;
		pickup.x = x_pickup;
		pickup.y = y_pickup;
		

		//LOOP K_EVENT

		while (SDL_PollEvent(&event) ){
			

			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				loop = 0;
			}

			if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
					key_left = true;
						break;
				case SDLK_RIGHT:
					key_right = true;
					break;
				case SDLK_SPACE:
					shot[cont_shot].x = enemy.x;
					shot[cont_shot].y = enemy.y;
					cont_shot++;
					if (cont_shot == NSHOT)
						cont_shot = 0;
					break;
				default:
					break;
				}
			}
			if (event.type == SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
					key_left = false;
					break;
				case SDLK_RIGHT:
					key_right = false;
					break;
				default:
					break;
				}
			}
		}

		if (key_left == true) {
			x_ball -= 7;
			if (x_ball <= 0) {
				x_ball += 7;
			}
		}
		if (key_right == true) {
			x_ball+= 7;
			if (x_ball >= 550) {
				x_ball -= 7;
			}
		}
	
		//mov mario
		if (enemy.x >= WEIGHT - enemy.w)
			mov_e = false;
		if (enemy.x == 0)
			mov_e = true;
		if (mov_e)
			enemy.x += 5;
		if (!mov_e)
			enemy.x -= 5;

		//shot
		for (int i = 0; i <= cont_shot; i++) {
			shot[i].y -= 20;
		}
		
		//}
			//CONDITIONS BACKGROUND
		
		if (background.y >= -4015) {
			y_background -= vel;
			y_pickup -= vel;
			y_sled -= vel;
			if (y_background <= -1400) { //Mov sled <--
				x_sled -= 7;
				y_sled--;
			}

			if (cont <= 90) { //Mov snowflakes <- ->
				if (cont <= 45) {
					x_pickup -= 1;
				}
				else {
					x_pickup += 1;
				}
				cont++;
			}
			else { cont = 0; }
		}
		//collision
		for (int i = 0; i < cont_shot; i++) {
			if(SDL_HasIntersection(&shot[i], &ball) == SDL_TRUE){
				x_ball = 275;
				i = cont_shot;
				shotInit(shot);
				life--;
			}
		}
			//SDL_RENDER
		SDL_RenderCopy(renderer, texture_background, NULL, &background);
		SDL_RenderCopy(renderer, texture_pickup, NULL, &pickup);
		switch (life) {
		case 3:
			SDL_RenderCopy(renderer, heart_tx, NULL, &heart);
			heart.x += 60;
			SDL_RenderCopy(renderer, heart_tx, NULL, &heart);
			heart.x += 60;
			SDL_RenderCopy(renderer, heart_tx, NULL, &heart);
			heart.x = 15;
			break;
		case 2:
			SDL_RenderCopy(renderer, heart_tx, NULL, &heart);
			heart.x += 60;
			SDL_RenderCopy(renderer, heart_tx, NULL, &heart);
			heart.x = 15;
			break;
		case 1:
			SDL_RenderCopy(renderer, heart_tx, NULL, &heart);
			heart.x = 15;
			break;
		case 0://Game over
			
			break;
		}

		SDL_RenderCopy(renderer, texture_ball, NULL, &ball);
		SDL_RenderCopy(renderer, mario_tx, NULL, &enemy);
		for (int i = 0; i < cont_shot; i++) {
			SDL_RenderCopy(renderer, shot_tx, NULL, &shot[i]);
		}
		//SDL_RenderCopy(renderer, texture_snowman, NULL,  &snowman);
		
		SDL_RenderPresent(renderer);

	}


	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	return 0;
}