#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleStage1.h"
#include "ModuleStage2.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleAudio.h"
#include "ModuleNeoGeo.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMainMenu.h"
#include "ModuleStageClear.h"
#include "ModuleViscoGames.h"
#include "ModuleGameOver.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleInsertCoin.h"
#include "ModuleEnemies.h"
#include "ModuleFonts.h"
#include "ModulePowerUp.h"
//#include "ModuleUI.h"



Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = stage1 = new ModuleStage1();
	//modules[5] = stage2 = new ModuleStage2();
	modules[5] = player1 = new ModulePlayer1();
	modules[6] = player2 = new ModulePlayer2();
	modules[7] = audio = new ModuleAudio();
	modules[8] = neogeo = new ModuleNeoGeo();
	modules[9] = visco = new ModuleViscoGames();
	modules[10] = mainmenu = new ModuleMainMenu();
	modules[11] = fade = new ModuleFadeToBlack();
	modules[12] = stageclear = new ModuleStageClear();
	modules[13] = gameover = new ModuleGameOver();
	modules[14] = particles = new ModuleParticles();
	modules[15] = collision = new ModuleCollision();
	modules[16] = insertCoin = new ModuleInsertCoin();
	modules[17] = enemies = new ModuleEnemies();
	modules[18] = fonts = new ModuleFonts();
	modules[19] = powerup = new ModulePowerUp();
	//modules[19] = ui = new ModuleUI();

}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Player will be enabled on the first update of a new scene
	player1->Disable();
	player2->Disable();
	// Disable the map that you do not start with
	insertCoin->Disable();
	visco->Disable();
	mainmenu->Disable();
	gameover->Disable();
	stageclear->Disable();
	//stage2->Disable();
	stage1->Disable();
	neogeo->Enable();
	gameover->Disable();
	collision->Disable();
	enemies->Disable();
	fonts->Disable();
	//ui->Disable();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}