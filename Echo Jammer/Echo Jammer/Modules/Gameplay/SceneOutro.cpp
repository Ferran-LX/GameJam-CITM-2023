#include "SceneOutro.h"
#include <SDL_image.h>

#include "../../Application/Application.h"
#include "../../Application/FileNames.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleInput.h"
#include "../../Modules/Core/ModuleFadeToBlack.h"

SceneOutro::SceneOutro(bool startEnabled) : Module(startEnabled) {
}

SceneOutro::~SceneOutro() {
}

bool SceneOutro::Start() {
	LOG("Loading background assets SCENE OUTRO");

	bool ret = true;
	//Carga de texturas(imagenes)

	startTime = SDL_GetTicks();

	ArrayImagesOutro[0] = App->textures->Load(FI_Outroimage_0.c_str());
	ArrayImagesOutro[1] = App->textures->Load(FI_Outroimage_1.c_str());
	ArrayImagesOutro[2] = App->textures->Load(FI_Outroimage_2.c_str());

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

//NO TOCAR NADA 
Update_Status SceneOutro::Update() {
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->sceneStart, 60 || pad.a == true);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneOutro::PostUpdate() {
	//DIBUJADO DE LAS IMAGENES DE LA INTRO

	Uint32 currentTime = SDL_GetTicks() - startTime;

	if (currentTime >= 1000 && currentTime < 3000) {

		App->render->Blit(ArrayImagesOutro[0], 0, 0, NULL);//jovani

	}

	if (currentTime >= 3000 && currentTime < 5000) {

		App->render->Blit(ArrayImagesOutro[1], 0, 0, NULL);//jovani

	}

	if (currentTime >= 5000) {

		App->render->Blit(ArrayImagesOutro[2], 0, 0, NULL);//jovani
	}

	if (currentTime >= 7000) {

		App->fade->FadeToBlack(this, (Module*)App->sceneStart, 60);
		
	}


	return Update_Status::UPDATE_CONTINUE;

}