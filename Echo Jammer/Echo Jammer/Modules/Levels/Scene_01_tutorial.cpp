#include "Scene_01_tutorial.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"
#include "../../Modules/Gameplay/ModulePlayer.h"
#include "../../Modules/Core/ModuleAudio.h"

Scene_01_tutorial::Scene_01_tutorial(bool startEnabled) : Module(startEnabled) {

}

Scene_01_tutorial::~Scene_01_tutorial() {
}

bool Scene_01_tutorial::Start()
{

	textura_fondo = App->textures->Load(FI_Mapa_Tutorial.c_str());

	App->audio->PlayMusic(FA_Music_Ambient.c_str(), 1.0f);

	rectFondo.x = 0;
	rectFondo.y = 0;
	rectFondo.w = widthNivell;
	rectFondo.h = heightNivell;


	//// POSITION INITIAL CAMERA
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	

	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	App->player->position.x = 1600;
	App->player->position.y = 600;
	App->player->positionAnterior = App->player->position;
	App->player->collider->rect.x = 1600;
	App->player->collider->rect.y = 600;

	App->enemies->AddEnemy(Enemy_Type::BASIC, 64 * 10, 540);
	App->enemies->AddEnemy(Enemy_Type::BASIC, 64 * 10, 604);
	App->enemies->AddEnemy(Enemy_Type::BASIC, 64 * 10, 668);
	App->enemies->AddEnemy(Enemy_Type::BASIC, 64 * 10, 732);

	App->collisions->AddCollider({ 0, 796, 1920 * 2,476 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 0, 1920 * 2,476}, Collider::Type::WALL);



	App->collisions->AddCollider({ 0, 0, 12, 220 }, Collider::Type::TR_NIVELL_T1);

	return true;
}

Update_Status Scene_01_tutorial::Update() {

	

	if (App->player->position.x <= 10)
		App->player->position.x = 10;
	if (App->player->position.x >= widthNivell - 10)
		App->player->position.x = widthNivell - 10;
	if (App->player->position.y <= 10)
		App->player->position.y = 10;
	if (App->player->position.y >= heightNivell - 128 - 10)
		App->player->position.y = heightNivell - 10;
	/*if (App->render->camera.x <= 0)
		App->render->camera.x = 0;
	if (App->render->camera.x < weigthNivell - 1920)
		App->render->camera.x = weigthNivell -1920;*/

	if (App->player->position.x >= 400 && App->player->position.x <= 3440)
	{
		App->render->camera.x = App->player->position.x - 400;
	}
	if (App->player->position.x < 400)
	{
		App->render->camera.x = 0;
	}
	if (App->render->camera.x > 1920)
	{
		App->render->camera.x = 1920;
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Scene_01_tutorial::PostUpdate() {
	App->render->Blit(textura_fondo, 0, 0, &rectFondo);
	return Update_Status::UPDATE_CONTINUE;
}

bool Scene_01_tutorial::CleanUp() {
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	App->player->lives = 3;
	return true;
}