#include "ScenePantallaLose.h"
#include <SDL_image.h>

#include "../../Application/Application.h"
#include "../../Application/FileNames.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Core/ModuleInput.h"
#include "../../Modules/Core/ModuleFadeToBlack.h"
#include "../Gameplay/ModuleEnemies.h"
#include "../Gameplay/ModulePlayer.h"
#include "../../Modules/Gameplay/SceneLevel1.h"

ScenePantallaLose::ScenePantallaLose(bool startEnabled) : Module(startEnabled) {
}

ScenePantallaLose::~ScenePantallaLose() {
}

bool ScenePantallaLose::Start() {
	LOG("Loading assets SCENE PantallaLose");

	bool ret = true;

	startTime = SDL_GetTicks();

	ArrayImagesContinue[0] = App->textures->Load(FI_continue_1.c_str());
	ArrayImagesContinue[1] = App->textures->Load(FI_continue_2.c_str());
	ArrayImagesContinue[2] = App->textures->Load(FI_continue_3.c_str());
	ArrayImagesContinue[3] = App->textures->Load(FI_continue_4.c_str());
	ArrayImagesContinue[4] = App->textures->Load(FI_continue_5.c_str());
	ArrayImagesContinue[5] = App->textures->Load(FI_continue_6.c_str());
	ArrayImagesContinue[6] = App->textures->Load(FI_continue_7.c_str());
	ArrayImagesContinue[7] = App->textures->Load(FI_continue_8.c_str());
	ArrayImagesContinue[8] = App->textures->Load(FI_continue_9.c_str());

	return ret;
}

Update_Status ScenePantallaLose::Update() {
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true) {//continuar partida

		App->player->lives += 1;
		App->scenePantallaLose->Disable();
		App->sceneLevel_1->stopGame = false;
		App->player->stopGame = false;
		App->enemies->stopGame = false;
		App->audio->PlayMusic(FA_Music_stage1.c_str(), 1.0f);
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ScenePantallaLose::PostUpdate() {

	Uint32 currentTime = SDL_GetTicks() - startTime;

	if (currentTime >= 1000 && currentTime < 2000) {
		App->render->Blit(ArrayImagesContinue[0], App->render->camera.x, App->render->camera.y, NULL);
	}

	if (currentTime >= 2000 && currentTime < 3000) {
		App->render->Blit(ArrayImagesContinue[1], App->render->camera.x, App->render->camera.y, NULL);
	}

	if (currentTime >= 3000 && currentTime < 4000) {
		App->render->Blit(ArrayImagesContinue[2], App->render->camera.x, App->render->camera.y, NULL);
	}

	if (currentTime >= 4000 && currentTime < 5000) {
		App->render->Blit(ArrayImagesContinue[3], App->render->camera.x, App->render->camera.y, NULL);
	}

	if (currentTime >= 5000 && currentTime < 6000) {
		App->render->Blit(ArrayImagesContinue[4], App->render->camera.x, App->render->camera.y, NULL);
	}

	if (currentTime >= 6000 && currentTime < 7000) {
		App->render->Blit(ArrayImagesContinue[5], App->render->camera.x, App->render->camera.y, NULL);
	}

	if (currentTime >= 7000 && currentTime < 8000) {
		App->render->Blit(ArrayImagesContinue[6], App->render->camera.x, App->render->camera.y, NULL);
	}

	if (currentTime >= 8000 && currentTime < 9000) {
		App->render->Blit(ArrayImagesContinue[7], App->render->camera.x, App->render->camera.y, NULL);
	}

	if (currentTime >= 9000 && currentTime < 11000) {
		App->render->Blit(ArrayImagesContinue[8], App->render->camera.x, App->render->camera.y, NULL);
	}


	if (currentTime >= 10000 && currentTime < 12000) {
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneStart, 60); //Menu start no intro
	}
	if (play)
	{
		App->audio->PlayMusic(FA_Music_GameOver.c_str(), 1.0f);
		play = false;
	}
	return Update_Status::UPDATE_CONTINUE;
}