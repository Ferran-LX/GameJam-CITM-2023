#include "ScenePreintro.h"
#include <SDL_image.h>

#include "../../Application/Application.h"
#include "../../Application/FileNames.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleInput.h"
#include "../../Modules/Core/ModuleFadeToBlack.h"
#include "../Gameplay/ModuleInsertCoin.h"

ScenePreintro::ScenePreintro(bool startEnabled) : Module(startEnabled) {
}

ScenePreintro::~ScenePreintro() {
}

bool ScenePreintro::Start() {
	LOG("Loading background assets SCENE Preintro");

	bool ret = true;
	startTime = SDL_GetTicks();

	ArrayImagesPreintro[0] = App->textures->Load(FI_Introimage_35.c_str());

	//App->render->camera.x = 0;
	//App->render->camera.y = 0;

	
	
	return ret;
}

//NO TOCAR NADA //FadeToBlack de Intro -> Juego
Update_Status ScenePreintro::Update() {
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true) {
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 60);
	}

	if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_DOWN)
	{
		tokenFx = App->audio->LoadFx(FA_Fx_token.c_str());
	};


	return Update_Status::UPDATE_CONTINUE;

}

// Update: draw background
Update_Status ScenePreintro::PostUpdate() {
	//DIBUJADO DE LAS IMAGENES DE LA INTRO
	Uint32 currentTime = SDL_GetTicks() - startTime;

	if (currentTime >= 1000) {
		int y = (currentTime - 1000) / 5;
		App->render->Blit(ArrayImagesPreintro[0], 0, -y + 1000, NULL);//jovani

	}

	if (currentTime >= 20000) {
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 60);
	}




	return Update_Status::UPDATE_CONTINUE;

}