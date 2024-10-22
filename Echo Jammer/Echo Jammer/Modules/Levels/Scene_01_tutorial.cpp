#include "Scene_01_tutorial.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"
#include "../../Modules/Gameplay/ModulePlayer.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleOscuridad.h"
#include "../../Entities/Enemies/Enemy.h"
#include "../../Modules/Core/ModuleFadeToBlack.h"

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

	App->oscuridad->Enable();
	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	App->player->position.x = 64*7;
	App->player->position.y = 600;
	App->player->positionAnterior = App->player->position;
	App->player->collider->rect.x = 1600;
	App->player->collider->rect.y = 600;

	App->enemies->AddEnemy(Enemy_Type::BASIC, 64 * 2, 540)->SetVisionRange(999999999);
	App->enemies->AddEnemy(Enemy_Type::BASIC, 64 * 2, 604)->SetVisionRange(999999999);
	App->enemies->AddEnemy(Enemy_Type::BASIC, 64 * 2, 668)->SetVisionRange(999999999);
	App->enemies->AddEnemy(Enemy_Type::BASIC, 64 * 2, 732)->SetVisionRange(999999999);
	App->enemies->AddEnemy(Enemy_Type::BASIC, 1426, 594)->SetSearchRange(999999999);

	//App->collisions->AddCollider({ 3712 , 540, 128 , 256 }, Collider::Type::TR_NIVELL_T1);

	App->collisions->AddCollider({ 0, 796, 1920 * 2,476 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 0, 1920 * 2,476 }, Collider::Type::WALL);



	App->collisions->AddCollider({ widthNivell - 300, heightNivell/4, 300, 700 }, Collider::Type::TR_NIVELL_T1);

	return true;
}

Update_Status Scene_01_tutorial::Update() {

	if (!App->player->alive) {
		App->fade->FadeToBlack((Module*)this, (Module*)App->scene_01_tutorial, 60);
	}

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
	App->oscuridad->Disable();
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	App->player->lives = 3;
	return true;
}