#pragma once

#include "../../Application/Application.h"
#include "../../Application/FileNames.h"

#include "../Core/ModuleTextures.h"
#include "../Core/ModuleRender.h"

#include "../Gameplay/ModuleEnemies.h"
#include "../Gameplay/ModulePlayer.h"

#include "SceneTestArea.h"

SceneTestArea::SceneTestArea(bool startEnabled) : Module(startEnabled)
{
}

SceneTestArea::~SceneTestArea()
{
}

bool SceneTestArea::Start()
{
	LOG("Loading assets SCENE TEST AREA");

	// _imageArray[0] = App->textures->Load() // Inserta imatge de fons

	enemies = App->enemies;
	enemies->Enable();

	player = App->player;
	player->Enable();

	enemies->AddEnemy(Enemy_Type::BASIC, 10, 10);

	return true;
}

Update_Status SceneTestArea::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneTestArea::PostUpdate()
{
	// TODO posar background
	return Update_Status::UPDATE_CONTINUE;
}

bool SceneTestArea::CleanUp()
{
	enemies->Disable();
	enemies = nullptr;

	player->Disable();
	player = nullptr;

	return true;
}
