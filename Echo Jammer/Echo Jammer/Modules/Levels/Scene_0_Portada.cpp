#include "Scene_0_Portada.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"

Scene0Portada::Scene0Portada(bool startEnabled) : Module(startEnabled) {
}

Scene0Portada::~Scene0Portada() {
}

bool Scene0Portada::Start() {
	textura = App->textures->Load(FI_Animacio_Portada.c_str());

	for (int i = 0; i < _numFrames / 2; i++)
		_animPortada.PushBack({ 1920 * i, 1080 * 0, 1920, 1080 });

	for (int i = 0; i < _numFrames / 2; i++)
		_animPortada.PushBack({ 1920 * i, 1080 * 1, 1920, 1080 });

	_animPortada.loop = true;
	_animPortada.speed = 0.2f;

	_currentAnimation = &_animPortada;

	return true;
}

Update_Status Scene0Portada::Update() {
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Scene0Portada::PostUpdate() {
	_currentAnimation->Update();
	App->render->Blit(textura, 0, 0, &_currentAnimation->GetCurrentFrame());
	return Update_Status::UPDATE_CONTINUE;
}

bool Scene0Portada::CleanUp() {
	return true;
}
