//#include "Scene_01_tutorial.h"
//
//#include "../../Application/Application.h"
//#include "../../Modules/Core/ModuleTextures.h"
//#include "../../Modules/Core/ModuleRender.h"
//#include "../../Modules/Core/ModuleCollisions.h"
//#include "../../Modules/Gameplay/ModuleEnemies.h"
//#include "../../Modules/Gameplay/ModulePlayer.h"
//#include "../../Modules/Core/ModuleAudio.h"
//
//Scene_01_tutorial::Scene_01_tutorial(bool startEnabled) : Module(startEnabled) {
//
//}
//
//Scene_01_tutorial::~Scene_01_tutorial() {
//}
//
//bool Scene_01_tutorial::Start()
//{
//
//	textura_fondo = App->textures->Load(FI_Mapa_Tutorial.c_str());
//
//	App->audio->PlayMusic(FA_Music_Ambient.c_str(), 1.0f);
//
//	rectFondo.x = 0;
//	rectFondo.y = 0;
//	rectFondo.w = widthNivell;
//	rectFondo.h = heightNivell;
//
//
//	//// POSITION INITIAL CAMERA
//
//	App->player->Enable();
//	App->enemies->Enable();
//	App->collisions->Enable();
//
//	App->render->camera.x = 0;
//	App->render->camera.y = 0;
//	
//
//	App->enemies->AddEnemy(Enemy_Type::BASIC, 64 * 10, 540);
//	App->enemies->AddEnemy(Enemy_Type::BASIC, 64 * 10, 604);
//	App->enemies->AddEnemy(Enemy_Type::BASIC, 64 * 10, 668);
//	App->enemies->AddEnemy(Enemy_Type::BASIC, 64 * 10, 732);
//
//	//App->collisions->AddCollider({ 0, 0, 1920*2,540-64}, Collider::Type::WALL);
//	//App->collisions->AddCollider({ 0, 796, 1920 * 2,256 }, Collider::Type::WALL);
//	App->collisions->AddCollider({ 100, 540 ,100,256 }, Collider::Type::WALL);
//
//	return true;
//}
//
//Update_Status Scene_01_tutorial::Update() {
//
//	//// Limites paredes X
//	//if (App->player->position.x <= 10)
//	//	App->player->position.x = 10;
//	//if (App->player->position.x >= weigthNivell - 10 - 128)
//	//	App->player->position.x = weigthNivell - 10 - 128;
//
//	//// Limites paredes Y
//	//if (App->player->position.y <= 10)
//	//	App->player->position.y = 10;
//	//if (App->player->position.y >= heightNivell - 128 - 10)
//	//	App->player->position.y = heightNivell - 128 - 10;
//
//	//// Hacer que camera siga al jugador
//	//if (App->player->position.x > 1920/2 && App->player->position.x < weigthNivell - 1920 + 1920/2)
//	//	// Si esta dentro del rango, tiene la misma posicion que el jugador
//	//	App->render->camera.x = App->player->position.x - 1920/2;
//	//if (App->player->position.y > 0 && App->player->position.y < heightNivell - 1080 + 540)
//	//	App->render->camera.y = App->player->position.y;
//
//
//	//if (App->player->position.x <= 10)
//	//	App->player->position.x = 10;
//	//if (App->player->position.x >= weigthNivell - 10)
//	//	App->player->position.x = weigthNivell - 10;
//	//if (App->player->position.y <= 10)
//	//	App->player->position.y = 10;
//	//if (App->player->position.y >= heightNivell - 128 - 10)
//	//	App->player->position.y = heightNivell - 10;
//
//
//
//	///*if (App->render->camera.x <= 0)
//	//	App->render->camera.x = 0;
//	//if (App->render->camera.x < weigthNivell - 1920)
//	//	App->render->camera.x = weigthNivell -1920;*/
//
//	SDL_Rect& camera = App->render->camera;
//	SDL_Rect& player = App->player->collider->rect;
//
//	if (player.x >= camera.w && player.x <= widthNivell-camera.w)
//	{
//		camera.x = player.x-camera.w>>1;
//	}
//	else if (camera.x < 0)
//	{
//		camera.x = 0;
//	}
//	else if (camera.x+camera.w > widthNivell)
//	{
//		App->render->camera.x = widthNivell-camera.w;
//	}
//
//
//	return Update_Status::UPDATE_CONTINUE;
//}
//
//Update_Status Scene_01_tutorial::PostUpdate() {
//	App->render->Blit(textura_fondo, 0, 0, &rectFondo);
//	return Update_Status::UPDATE_CONTINUE;
//}
//
//bool Scene_01_tutorial::CleanUp() {
//	App->player->Disable();
//	App->enemies->Disable();
//	App->collisions->Disable();
//	App->player->lives = 3;
//	return true;
//}
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

	App->enemies->AddEnemy(Enemy_Type::BASIC, 64 * 10, 540);
	App->enemies->AddEnemy(Enemy_Type::BASIC, 64 * 10, 604);
	App->enemies->AddEnemy(Enemy_Type::BASIC, 64 * 10, 668);
	App->enemies->AddEnemy(Enemy_Type::BASIC, 64 * 10, 732);

	App->collisions->AddCollider({ 0, 0, 1920 * 2,256 }, Collider::Type::WALL);

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