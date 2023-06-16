#include "SceneStart.h"
#include <SDL_image.h>

#include "../../Application/Application.h"
#include "../../Application/FileNames.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleInput.h"
#include "../../Modules/Core/ModuleFadeToBlack.h"

SceneStart::SceneStart(bool startEnabled) : Module(startEnabled) {
}

SceneStart::~SceneStart() {
}

bool SceneStart::Start() {
	LOG("Loading background assets SCENE INTRO");

	bool ret = true;

	//Carga de texturas(imagenes)

	ArrayImagesStart[0] = App->textures->Load(FI_Start_1.c_str());
	ArrayImagesStart[1] = App->textures->Load(FI_Start_2.c_str());

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

//NO TOCAR NADA //FadeToBlack de Intro -> primera escena
Update_Status SceneStart::Update() {
	GamePad& pad = App->input->pads[0];
	if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN || pad.start==true) {
		// TODO: Falta meter sonido
		coins++;
		LOG("+ COIN!")
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true) {
		if (coins > 0)
		{
			LOG("Game start!")
			App->fade->FadeToBlack(this, (Module*)App->sceneEscoger, 60);
			coins--;
		}
		else
		{
			LOG("No tens monedes!")
		}
	}
	if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_DOWN)
	{
		tokenFx = App->audio->LoadFx(FA_Fx_token.c_str());
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneStart::PostUpdate() {
	//DIBUJADO DE LAS IMAGENES DE LA INTRO

	timer += 1.0f / 60.0f; // Suma 1 segundo//Funciona a 60 fps

	if (timer >= 0.05f) { // Mostramos cada imagen durante 3 segundos
		currentImage++;
		if (currentImage == NUM_IMAGES) {
			currentImage = 0;
		}
		timer = 0.0f;
	}

	App->render->Blit(ArrayImagesStart[currentImage], 0, 0, NULL);


	return Update_Status::UPDATE_CONTINUE;
}