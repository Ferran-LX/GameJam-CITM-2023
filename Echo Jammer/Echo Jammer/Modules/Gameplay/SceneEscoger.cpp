#include "SceneEscoger.h"
#include <SDL_image.h>

#include "../../Application/Application.h"
#include "../../Application/FileNames.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleInput.h"
#include "../../Modules/Core/ModuleFadeToBlack.h"

SceneEscoger::SceneEscoger(bool startEnabled) : Module(startEnabled) {
}

SceneEscoger::~SceneEscoger() {
}

bool SceneEscoger::Start() {
	LOG("Loading background assets SCENE INTRO");

	bool ret = true;
	//Carga de texturas(imagenes)


	ArrayImagesEscoger[0] = App->textures->Load(FI_choseplayer_1.c_str());
	ArrayImagesEscoger[1] = App->textures->Load(FI_choseplayer_2.c_str());
	ArrayImagesEscoger[2] = App->textures->Load(FI_choseplayer_3.c_str());
	ArrayImagesEscoger[3] = App->textures->Load(FI_choseplayer_4.c_str());
	App->audio->PlayMusic(FA_Music_Selection.c_str(), 1.0f);
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

//NO TOCAR NADA //FadeToBlack de Intro -> primera escena
Update_Status SceneEscoger::Update() {
	GamePad& pad = App->input->pads[0];
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true) {

		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 60);
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneEscoger::PostUpdate() {
	//DIBUJADO DE LAS IMAGENES DE LA INTRO

	timer += 1.0f / 60.0f; // Suma 1 segundo//Funciona a 60 fps

	if (timer >= 0.05f) { // Mostramos cada imagen durante 3 segundos
		currentImage++;
		if (currentImage == NUM_IMAGES) {
			currentImage = 0;
		}
		timer = 0.0f;
	}

	App->render->Blit(ArrayImagesEscoger[currentImage], 0, 0, NULL);



	return Update_Status::UPDATE_CONTINUE;

}