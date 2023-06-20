#include "SceneTESTS.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"
#include "../../Modules/Gameplay/ModulePlayer.h"
#include "../../Modules/Core/ModuleAudio.h"

SceneTESTS::SceneTESTS(bool startEnabled) : Module(startEnabled) {

}

SceneTESTS::~SceneTESTS() {
}

bool SceneTESTS::Start()
{

	textura_fondo = App->textures->Load(FI_Mapa_Level1.c_str());

	App->audio->PlayMusic(FA_Music_Ambient.c_str(), 1.0f);

	rectFondo.x = 0;
	rectFondo.y = 0;
	rectFondo.w = 1920;
	rectFondo.h = 1080;


	//// POSITION INITIAL CAMERA
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();

	App->enemies->AddEnemy(Enemy_Type::BASIC, 10, 10);

	App->collisions->AddCollider({ 700, 400, 64,64 },Collider::Type::WALL);

	return true;
}

Update_Status SceneTESTS::Update() {

	if (App->player->position.x <= 10) App->player->position.x = 10;
	if (App->player->position.x >= weigthNivell - 10) App->player->position.x = weigthNivell - 10;
	if (App->player->position.y <= 10) App->player->position.y = 10;
	if (App->player->position.y >= heightNivell - 10) App->player->position.y = heightNivell - 10;


	if (App->player->position.x > 0 && App->player->position.x < weigthNivell - 1920) App->render->camera.x = App->player->position.x;
	if (App->player->position.y > 0 && App->player->position.y < heightNivell - 1080) App->render->camera.y = App->player->position.y;


	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneTESTS::PostUpdate() {
	App->render->Blit(textura_fondo, 0, 0, &rectFondo);
	return Update_Status::UPDATE_CONTINUE;
}

bool SceneTESTS::CleanUp() {
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	App->player->lives = 3;
	return true;
}
