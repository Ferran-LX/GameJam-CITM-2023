#include "ModuleOscuridad.h"

#include <SDL_timer.h>
#include <SDL_image.h>

#include "../../Application/FileNames.h"
#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleFadeToBlack.h"
#include "../../Modules/Core/ModuleInput.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Gameplay/ModulePlayer.h"

ModuleOscuridad::ModuleOscuridad(bool startEnabled) : Module(startEnabled) {
}

ModuleOscuridad::~ModuleOscuridad() {
}

bool ModuleOscuridad::Start() {
	textura_oscuridad = App->textures->Load(FI_Mapa_Overlay.c_str());

	
	/*startTime = SDL_GetTicks();
	App->audio->PlayMusic(FA_Music_Ambient.c_str(), 1.0f);

	for (int i = 0; i < _numFiles; i++)
	{
		for (int k = 0; k < _numFramesPerFila; k++)
			_animPortada.PushBack({ 1920 * k, 1080 * i, 1920, 1080 });
	}

	ArrayImagesStart[0] = App->textures->Load(FI_Animacio_Start.c_str());

	_animPortada.loop = true;
	_animPortada.speed = 0.2f;App->render->Blit(textura_oscuridad, 0, 0);

	_currentAnimation = &_animPortada;*/

	return true;
}

Update_Status ModuleOscuridad::Update() {
	/*if (App->input->controlP1.dash == Key_State::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->sceneTests, 60);
	}*/


	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleOscuridad::PostUpdate() {

	//Uint32 currentTime = SDL_GetTicks() - startTime;

	//if (currentTime >= 500 && currentTime < 15000) {
	//	_currentAnimation->Update();
	//	App->render->Blit(textura, 0, 0, &_currentAnimation->GetCurrentFrame());
	App->render->Blit(textura_oscuridad, App->player->position.x -1856, App->player->position.y-1856);
	//	App->render->Blit(ArrayImagesStart[0], 220, 900, NULL);//espacio_sprite

	//}

	//if (currentTime >= 13000) {
	//	App->fade->FadeToBlack(this, (Module*)App->sceneTests, 60);//canviar Tests

	//}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleOscuridad::CleanUp() {
	return true;
}