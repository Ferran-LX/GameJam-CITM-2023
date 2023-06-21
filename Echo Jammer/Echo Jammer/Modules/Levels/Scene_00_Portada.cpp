#include "Scene_00_Portada.h"
#include <SDL_timer.h>
#include <SDL_image.h>

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleFadeToBlack.h"
#include "../../Modules/Core/ModuleInput.h"
#include "../../Modules/Core/ModuleAudio.h"

Scene_00_Portada::Scene_00_Portada(bool startEnabled) : Module(startEnabled) {
}

Scene_00_Portada::~Scene_00_Portada() {
}

bool Scene_00_Portada::Start() {
	textura = App->textures->Load(FI_Animacio_Portada.c_str());

	startTime = SDL_GetTicks();
	App->audio->PlayMusic(FA_Music_Ambient.c_str(), 1.0f);

	for (int i = 0; i < _numFiles; i++)
	{
		for (int k = 0; k < _numFramesPerFila; k++)
			_animPortada.PushBack({ 1920 * k, 1080 * i, 1920, 1080 });
	}

	ArrayImagesStart[0] = App->textures->Load(FI_Animacio_Start.c_str());

	_animPortada.loop = true;
	_animPortada.speed = 0.2f;

	_currentAnimation = &_animPortada;

	return true;
}

Update_Status Scene_00_Portada::Update() {
	if (App->input-> keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN || controlP1.dash == Key_State::KEY_DOWN) {

		App->fade->FadeToBlack(this, (Module*)App->scene_01_tutorial, 60);
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Scene_00_Portada::PostUpdate() {
	
	Uint32 currentTime = SDL_GetTicks() - startTime;

	if (currentTime >= 500 && currentTime < 15000) {
		_currentAnimation->Update();
		App->render->Blit(textura, 0, 0, &_currentAnimation->GetCurrentFrame());

		App->render->Blit(ArrayImagesStart[0], 220, 900, NULL);//espacio_sprite

	}

	if (currentTime >= 13000) {
		App->fade->FadeToBlack(this, (Module*)App->scene_01_tutorial, 60);//canviar Tests

	}

	return Update_Status::UPDATE_CONTINUE;
}

bool Scene_00_Portada::CleanUp() {
	return true;
}
