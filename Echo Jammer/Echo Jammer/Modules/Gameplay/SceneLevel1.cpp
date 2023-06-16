#include "SceneLevel1.h"

#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Core/ModuleInput.h"
#include "../Gameplay/ModuleEnemies.h"
#include "../Gameplay/ModulePlayer.h"
#include "../Gameplay/ModuleInsertCoin.h"
#include "../Gameplay/SceneLevel1.h"
#include "../../Application/Application.h"

#include <SDL_timer.h>



SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled) {
}

SceneLevel1::~SceneLevel1() {
}

// Load assets
bool SceneLevel1::Start() {
	LOG("Loading background assets SCENE 1");

	bool ret = true;

	texture_sea = App->textures->Load(FI_background_sea.c_str());
	texture_sea2 = App->textures->Load(FI_background_sea2.c_str());
	texture_forest1 = App->textures->Load(FI_background_forest1.c_str());
	texture_castle = App->textures->Load(FI_background_castle.c_str());
	texture_colum = App->textures->Load(FI_background_precolumnas.c_str());
	texture_start = App->textures->Load(FI_background_pre.c_str());
	texture_arboles = App->textures->Load(FI_background_arboles.c_str());

	App->audio->PlayMusic(FA_Music_stage1.c_str(), 1.0f);


	//Wall colliders
	int xt = 0;
	int yt = 2850;
	int wt = SCREEN_WIDTH;
	int ht = 10;
	topcoll = App->collisions->AddCollider({ xt, yt, wt, ht }, Collider::Type::WALL_PLAYER);

	int xb = 0;
	int yb = 3920;
	int wb = SCREEN_WIDTH;
	int hb = 10;
	botcoll = App->collisions->AddCollider({ xb, yb, wb, hb }, Collider::Type::WALL_PLAYER);

	int xl = 0;
	int yl = 2850;
	int wl = 10;
	int hl = SCREEN_HEIGHT;
	leftcoll = App->collisions->AddCollider({ xl, yl, wl, hl }, Collider::Type::WALL_PLAYER);

	int xr = SCREEN_WIDTH - 10;
	int yr = 2850;
	int wr = 10;
	int hr = SCREEN_HEIGHT;
	raightcoll = App->collisions->AddCollider({ xr, yr, wr, hr }, Collider::Type::WALL_PLAYER);

	start_time = SDL_GetTicks();


#pragma region ENEMIES

	// add chest
	App->enemies->AddEnemy(Enemy_Type::GOLD, 100, -2150, 1);
	App->enemies->AddEnemy(Enemy_Type::CHEST_RED, 450, -2600, 1);
	App->enemies->AddEnemy(Enemy_Type::CHEST_BLUE, 100, -7300, 1);
	App->enemies->AddEnemy(Enemy_Type::CHEST_GREEN, 450, -13400, 1);
	App->enemies->AddEnemy(Enemy_Type::GOLD, 450, -32000, 1);
	App->enemies->AddEnemy(Enemy_Type::CHEST_RED, 450, -32500, 1);
	App->enemies->AddEnemy(Enemy_Type::CHEST_RED, 450, -39200, 1);
	App->enemies->AddEnemy(Enemy_Type::GOLD, 450, -39480, 1);
	App->enemies->AddEnemy(Enemy_Type::CHEST_GREEN, 450, -40000, 1);
	App->enemies->AddEnemy(Enemy_Type::CHEST_BLUE, 100, -42500, 1);


#pragma region STAGE

	App->enemies->AddEnemy(Enemy_Type::FLAG, 500, -100, 1);
	App->enemies->AddEnemy(Enemy_Type::NUM1, 500, -100, 1);
	App->enemies->AddEnemy(Enemy_Type::STAGE, -350, -100, 1);


#pragma endregion

#pragma region Red ball 
	
	
	
		//add red ball
		
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 120, -2200, 1);
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 120, -2300, 1);
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 120, -2400, 1);
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 120, -2500, 1);
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 120, -2600, 1);
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 120, -2700, 1);
		///*App->enemies->AddEnemy(Enemy_Type::RED_BALL, 50, -680, 1, 7);
		//App->enemies->AddEnemy(Enemy_Type::RED_BALL, 50, -710, 1, 8);*/
	
		////add red ball 2
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 640, -4500, 2);
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 640, -4600, 2);
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 640, -4700, 2);
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 640, -4800, 2);
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 640, -4900, 2);
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 640, -5000, 2);
	//	////App->enemies->AddEnemy(Enemy_Type::RED_BALL, 290, -940, 2, 7);
	//	////App->enemies->AddEnemy(Enemy_Type::RED_BALL, 290, -970, 2, 8);
	//
	//	////add red ball 3
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 180, -6800, 3);
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 180, -6900, 3);
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 180, -7000, 3);
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 180, -7100, 3);
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 180, -7200, 3);
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 180, -7300, 3);
	//	/*App->enemies->AddEnemy(Enemy_Type::RED_BALL, 110, -1900, 3, 7);
	//	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 110, -1950, 3, 8);*/
	
		
		//add red ball 4
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 710, -9100, 4);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 710, -9200, 4);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 710, -9300, 4);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 710, -9400, 4);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 710, -9500, 4);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 710, -9600, 4);

	//	/*App->enemies->AddEnemy(Enemy_Type::RED_BALL, 290, -2400, 4, 7);
	//	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 290, -2450, 4, 8);*/
	
	//add red ball 5
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 100, -11400, 5);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 100, -11500, 5);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 100, -11600, 5);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 100, -11700, 5);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 100, -11800, 5);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 100, -11900, 5);

	//add red ball 6
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 700, -20000, 6);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 700, -20100, 6);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 700, -20200, 6);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 700, -20300, 6);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 700, -20400, 6);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 700, -20500, 6);

		//add red ball 7

	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 100, -25000, 7);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 100, -25100, 7);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 100, -25200, 7);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 100, -25300, 7);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 100, -25400, 7);
	App->enemies->AddEnemy(Enemy_Type::RED_BALL, 100, -25500, 7);
	//
		/*App->enemies->AddEnemy(Enemy_Type::RED_BALL, 50, -5100, 7, 7);
		App->enemies->AddEnemy(Enemy_Type::RED_BALL, 50, -5150, 7, 8);*/

#pragma endregion

#pragma region Wizard
		//	//add Wizard
	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, 450, -7500, 1);
	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, 510, -7500, 1);

	////add Wizard 2
	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, 120, -9600, 2);
	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, 180, -9600, 2);

	////add wizard 3
	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, 380, -11700, 3);
	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, 440, -11700, 3);

	////add wizard 4
	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, 120, -13400, 4);
	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, 180, -13400, 4);

	////add wizard 5
	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, 520, -14000, 5);
	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, 580, -14000, 5);

	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, -100, -36500, 6);
	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, 800, -36250, 7);
	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, -100, -36800, 6);
	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, 800, -36950, 7);

	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, -100, -37950, 6);
	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, 800, -38100, 7);
	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, -100, -38250, 6);
	App->enemies->AddEnemy(Enemy_Type::REDWIZARD, 800, -38400, 7);

#pragma endregion

#pragma region dragon
	////add dragon
	App->enemies->AddEnemy(Enemy_Type::DRAGON, 20, -17000, 1);
	App->enemies->AddEnemy(Enemy_Type::DRAGON, 400, -22000, 2);

#pragma endregion

#pragma region goblin

	App->enemies->AddEnemy(Enemy_Type::FLYTANK, 100, -31500, 1);
	App->enemies->AddEnemy(Enemy_Type::FLYTANK, 100, -42000, 1);

#pragma endregion

#pragma region tanks


	App->enemies->AddEnemy(Enemy_Type::TANK, 0, -33250, 1);
	App->enemies->AddEnemy(Enemy_Type::TANK, -150, -33250, 1);
	App->enemies->AddEnemy(Enemy_Type::TANK, -300, -33250, 1);
	App->enemies->AddEnemy(Enemy_Type::TANK, 800, -33112, 2);
	App->enemies->AddEnemy(Enemy_Type::TANK, 950, -33112, 2);
	App->enemies->AddEnemy(Enemy_Type::TANK, 1100, -33112, 2);//17112

	App->enemies->AddEnemy(Enemy_Type::TANK, -150, -36350, 3);
	App->enemies->AddEnemy(Enemy_Type::TANK, 800, -36350, 4);
	App->enemies->AddEnemy(Enemy_Type::TANK, -150, -36500, 3);
	App->enemies->AddEnemy(Enemy_Type::TANK, 800, -36500, 4);
	App->enemies->AddEnemy(Enemy_Type::TANK, -150, -36650, 3);
	App->enemies->AddEnemy(Enemy_Type::TANK, 800, -36650, 4);
	App->enemies->AddEnemy(Enemy_Type::TANK, -150, -36800, 3);
	App->enemies->AddEnemy(Enemy_Type::TANK, 800, -36800, 4);

	/*App->enemies->AddEnemy(Enemy_Type::TANK, -0, -21600, 5);
	App->enemies->AddEnemy(Enemy_Type::TANK, -100, -21600, 5);
	App->enemies->AddEnemy(Enemy_Type::TANK, -0, -21750, 5);
	App->enemies->AddEnemy(Enemy_Type::TANK, -0, -21900, 5);*/

	App->enemies->AddEnemy(Enemy_Type::TANK, -0, -37400, 5);
	App->enemies->AddEnemy(Enemy_Type::TANK, -100, -37400, 5);
	App->enemies->AddEnemy(Enemy_Type::TANK, -0, -37550, 5);
	

	App->enemies->AddEnemy(Enemy_Type::TANK, -800, -38050, 5);
	App->enemies->AddEnemy(Enemy_Type::TANK, -100, -38550, 7);
	App->enemies->AddEnemy(Enemy_Type::TANK, -100, -39050, 6);
	App->enemies->AddEnemy(Enemy_Type::TANK, -100, -40350, 6);
	App->enemies->AddEnemy(Enemy_Type::TANK, -250, -40350, 6);

#pragma endregion

#pragma region turtle

	App->enemies->AddEnemy(Enemy_Type::TURTLE, 200, -34650, 2);
	App->enemies->AddEnemy(Enemy_Type::TURTLE, 450, -35850, 2);

	
	App->enemies->AddEnemy(Enemy_Type::TURTLE, -100, -38800, 1);

	App->enemies->AddEnemy(Enemy_Type::TURTLE, 100, -39250, 2);
	App->enemies->AddEnemy(Enemy_Type::TURTLE, 400, -39250, 2);

#pragma endregion

#pragma region goblin

	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 150, -34350, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 540, -34350, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 240, -34550, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 630, -34550, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 150, -34750, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 540, -34750, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 240, -34950, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 630, -34950, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 150, -35150, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 540, -35150, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 240, -35350, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 630, -35350, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 150, -35550, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 540, -35550, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 240, -35750, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 630, -35750, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 150, -35950, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 540, -35950, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 240, -36150, 1);
	App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 630, -36350, 1);


	//App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 720, -23550, 1);
	//App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 630, -23550, 1);
	//App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 540, -23550, 1);
	//App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 720, -23700, 1);
	//App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 630, -23700, 1);
	//App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 540, -23700, 1);
	//App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 720, -23850, 1);
	//App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 630, -23850, 1);
	//App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 540, -23850, 1);
	//App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 720, -24000, 1);
	//App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 630, -24000, 1);
	//App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 540, -24000, 1);
	//App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 720, -24150, 1);
	//App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 630, -24150, 1);
	//App->enemies->AddEnemy(Enemy_Type::MINIDRAGON, 540, -24150, 1);

#pragma endregion

#pragma region bigtank
	App->enemies->AddEnemy(Enemy_Type::BIGTANK, 0, 39490, 1);
	App->enemies->AddEnemy(Enemy_Type::BIGTANK, -277, -41600, 2);
	App->enemies->AddEnemy(Enemy_Type::BIGTANK, 800, -41600, 3);
#pragma endregion

#pragma region redbat
	/*App->enemies->AddEnemy(Enemy_Type::REDBAT, 600, -22050, 1);
	App->enemies->AddEnemy(Enemy_Type::REDBAT, 600, -22050, 1);
	App->enemies->AddEnemy(Enemy_Type::REDBAT, 550, -22250, 1);
	App->enemies->AddEnemy(Enemy_Type::REDBAT, 500, -22450, 1);*/

	/*App->enemies->AddEnemy(Enemy_Type::REDBAT, 50, -42000, 1);
	App->enemies->AddEnemy(Enemy_Type::REDBAT, 250, -42000, 1);
	App->enemies->AddEnemy(Enemy_Type::REDBAT, 450, -42000, 1);
	App->enemies->AddEnemy(Enemy_Type::REDBAT, 650, -42000, 1);*/
#pragma endregion

	App->enemies->AddEnemy(Enemy_Type::WARL, 30, -44000, 1);
	App->enemies->AddEnemy(Enemy_Type::WARR, 330, -44000, 1);
	App->enemies->AddEnemy(Enemy_Type::FLECH, 349, -44000, 1);

#pragma endregion
	App->enemies->AddEnemy(Enemy_Type::BOSS, 420, -48000, 1);

	// POSITION INITIAL CAMERA
	App->render->camera.x = 0;
	App->render->camera.y = 2850;

	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();


	return ret;
}

Update_Status SceneLevel1::Update() {

	LOG("Velocidad nivel: %d", velocitatNivell);

	if (!stopGame) {
		GamePad& pad = App->input->pads[0];

		App->render->camera.y += velocitatNivell;

		topcoll->rect.y += velocitatNivell;
		botcoll->rect.y += velocitatNivell;
		leftcoll->rect.y += velocitatNivell;
		raightcoll->rect.y += velocitatNivell;

		// Control velocidad aeropuerco
		if (SDL_GetTicks() - start_time >= 600 && !controlSalidaAeropuerco1) { velocitatNivell = -4; controlSalidaAeropuerco1 = true; }
		if (SDL_GetTicks() - start_time >= 2600 && !controlSalidaAeropuerco2) { velocitatNivell = -6; controlSalidaAeropuerco2 = true; }
		if (SDL_GetTicks() - start_time >= 4600 && !controlSalidaAeropuerco3) { velocitatNivell = -10; controlSalidaAeropuerco3 = true; }
		if (SDL_GetTicks() - start_time >= 6600 && !controlSalidaAeropuerco4) { velocitatNivell = -15; controlSalidaAeropuerco4 = true; }

		// Control velocidad castillo
		if (SDL_GetTicks() - start_time >= 40500 && !controlLlegadaCastillo1) { velocitatNivell = -6; controlLlegadaCastillo1 = true; }
		if (SDL_GetTicks() - start_time >= 43000 && !controlLlegadaCastillo2) { velocitatNivell = -4; controlLlegadaCastillo2 = true; }

		// Control velocidad BOSS
		if (SDL_GetTicks() - start_time >= 93500 && !controlLlegadaBoss) { velocitatNivell = -15; controlLlegadaBoss = true; }

		if ((App->player->position.x + 5 + App->player->collider->rect.w) >= raightcoll->rect.x)
			App->player->position.x = raightcoll->rect.x - (5 + App->player->collider->rect.w);


		if (App->player->position.x - 5 <= leftcoll->rect.x)
			App->player->position.x = leftcoll->rect.x + 5;

		if ((App->player->position.y + 5 + App->player->collider->rect.h) >= botcoll->rect.y)
			App->player->position.y = botcoll->rect.y - (5 + App->player->collider->rect.h); 

		//if ((App->player->position.y + 5 + App->player->collider->rect.h) >= botcoll->rect.y)// este if es el problema
		//{
		//	// TODO: declarar gamepad a .h, no creem un objecte nou en cada volta
		//	GamePad& pad = App->input->pads[0];
		//	/*App->render->camera.y += velocitatNivell;

		//	topcoll->rect.y += velocitatNivell;
		//	botcoll->rect.y += velocitatNivell;
		//	leftcoll->rect.y += velocitatNivell;
		//	raightcoll->rect.y += velocitatNivell;*/

		//	if ((App->player->position.x + 5 + App->player->collider->rect.w) >= raightcoll->rect.x)
		//		App->player->position.x = raightcoll->rect.x - (5 + App->player->collider->rect.w);


		//	if (App->player->position.x - 5 <= leftcoll->rect.x)
		//		App->player->position.x = leftcoll->rect.x + 5;


		//	if ((App->player->position.y + 5 + App->player->collider->rect.h) >= botcoll->rect.y)
		//		App->player->position.y = botcoll->rect.y - (5 + App->player->collider->rect.h);


		//	if (App->player->position.y - 5 <= topcoll->rect.y)
		//		App->player->position.y = topcoll->rect.y + 5;


		//	//Spawn cofres
		//	if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_DOWN || pad.up == true)
		//		App->enemies->AddEnemy(Enemy_Type::CHEST_RED, App->player->position.x + 50, App->player->position.y - 800, 1);

		//	if (App->input->keys[SDL_SCANCODE_2] == Key_State::KEY_DOWN || pad.down == true)
		//		App->enemies->AddEnemy(Enemy_Type::CHEST_GREEN, App->player->position.x + 50, App->player->position.y - 800, 1);

		//	if (App->input->keys[SDL_SCANCODE_3] == Key_State::KEY_DOWN || pad.right == true)
		//		App->enemies->AddEnemy(Enemy_Type::CHEST_BLUE, App->player->position.x + 50, App->player->position.y - 800, 1);

		//	if (App->input->keys[SDL_SCANCODE_4] == Key_State::KEY_DOWN || pad.left == true)
		//		App->enemies->AddEnemy(Enemy_Type::ANGEL, App->player->position.x + 50, App->player->position.y - 800, 1);

		//	if (App->input->keys[SDL_SCANCODE_F5] == Key_State::KEY_DOWN)
		//		App->enemies->AddEnemy(Enemy_Type::REDWIZARD, 400, App->player->position.y - 700, 1);

		//	if (App->input->keys[SDL_SCANCODE_Q] == Key_State::KEY_DOWN)
		//		App->enemies->AddEnemy(Enemy_Type::BOSS, 400, App->player->position.y - 700, 1);
		//}


		//Spawn cofres
		if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_DOWN || pad.up == true)
			App->enemies->AddEnemy(Enemy_Type::CHEST_RED, App->player->position.x + 50, App->player->position.y - 800, 1);

		if (App->input->keys[SDL_SCANCODE_2] == Key_State::KEY_DOWN || pad.down == true)
			App->enemies->AddEnemy(Enemy_Type::CHEST_GREEN, App->player->position.x + 50, App->player->position.y - 800, 1);

		if (App->input->keys[SDL_SCANCODE_3] == Key_State::KEY_DOWN || pad.right == true)
			App->enemies->AddEnemy(Enemy_Type::CHEST_BLUE, App->player->position.x + 50, App->player->position.y - 800, 1);

		if (App->input->keys[SDL_SCANCODE_4] == Key_State::KEY_DOWN || pad.left == true)
			App->enemies->AddEnemy(Enemy_Type::ANGEL, App->player->position.x + 50, App->player->position.y - 800, 1);

		if (App->input->keys[SDL_SCANCODE_Q] == Key_State::KEY_DOWN || pad.y == true)
			App->enemies->AddEnemy(Enemy_Type::BOSS, 400, App->player->position.y - 700, 1);

		if (App->input->keys[SDL_SCANCODE_T] == Key_State::KEY_DOWN || pad.b == true)
		{
			topcoll->rect.y = TP;
			botcoll->rect.y = TP + 1080;
			leftcoll->rect.y = TP;
			raightcoll->rect.y = TP;
			App->render->camera.y = TP;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneLevel1::PostUpdate() {
	// Draw everything --------------------------------------
	App->render->Blit(texture_forest1, 0, -SCREEN_HEIGHT * -1, NULL);
	App->render->Blit(texture_start, 0, -SCREEN_HEIGHT * -1, NULL);
	App->render->Blit(texture_colum, 0, -SCREEN_HEIGHT * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_sea, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_sea2, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea + Height_background_sea - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea + Height_background_sea + Height_background_castle - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_castle, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea + Height_background_sea + Height_background_castle - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_arboles, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea + Height_background_sea + Height_background_castle - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea + Height_background_sea + Height_background_castle + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea + Height_background_sea + Height_background_castle + Height_background_forest1 + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea + Height_background_sea + Height_background_castle + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea + Height_background_sea + Height_background_castle + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea + Height_background_sea + Height_background_castle + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea + Height_background_sea + Height_background_castle + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea + Height_background_sea + Height_background_castle + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea + Height_background_sea + Height_background_castle + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea + Height_background_sea + Height_background_castle + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea + Height_background_sea + Height_background_castle + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	App->render->Blit(texture_forest1, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea + Height_background_sea + Height_background_castle + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp() {
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	App->player->lives = 3;
	return true;
}
