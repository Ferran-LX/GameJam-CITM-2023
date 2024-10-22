#include "Scene_03_level2.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"
#include "../../Modules/Gameplay/ModulePlayer.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleOscuridad.h"
#include "../../Modules/Core/ModuleFadeToBlack.h"

Scene_03_nivel2::Scene_03_nivel2(bool startEnabled) : Module(startEnabled) {

}

Scene_03_nivel2::~Scene_03_nivel2() {
}

bool Scene_03_nivel2::Start()
{

	textura_fondo3 = App->textures->Load(FI_Mapa_Level2.c_str());
	textura_oscuridad = App->textures->Load(FI_Mapa_Overlay.c_str());

	App->audio->PlayMusic(FA_Music_Ambient.c_str(), 1.0f);

	rectFondo.x = 0;
	rectFondo.y = 0;
	rectFondo.w = weigthNivell;
	rectFondo.h = heightNivell;

	//// POSITION INITIAL CAMERA
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->oscuridad->Enable();
	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();

	// TODO: Poner en la posicion inical / puerta del nivel
	App->player->position.x = 64;
	App->player->position.y = 1700;
	App->player->collider->SetPos(400, 500);





	/*App->collisions->AddCollider({ 0, 0, weigthNivell, 220 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 700, 400, 200,200 }, Collider::Type::WALL);*/

	App->collisions->AddCollider({ 0, 0, 1920, 192 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 192, 384, 128 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 320, 128, 512 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1088, 192, 128, 448 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1216, 192, 384, 128 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1792, 192, 128, 512 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 1152, 128, 512 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 128, 1600, 704, 64 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 384, 1664, 448, 64 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 640, 1728, 192, 448 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 768, 2176, 64, 64 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 768, 2496, 64, 192 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 2176, 128,512 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 128, 2528, 256,128 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 448, 1184, 256,96 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 704, 832, 128,448 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 1088, 1600, 576, 64 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1088, 1664, 320, 128 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1088, 1792, 64, 448 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 1088, 2496, 64, 192 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 1792, 1600, 128, 512 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 1152, 960, 128, 360 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1280, 1088, 128, 232 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1408 , 1216 , 128, 103 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 1536 , 572 + 236 + 32 , 128 , 100 }, Collider::Type::WALL);


	App->collisions->AddCollider({ 1600 , 192, 256 , 128 }, Collider::Type::TR_NIVELL_23);

	App->enemies->AddEnemy(Enemy_Type::BASIC, 960, 1500);
	App->enemies->AddEnemy(Enemy_Type::BASIC, 1420, 1500);
	App->enemies->AddEnemy(Enemy_Type::BASIC, 1420, 620);
	App->enemies->AddEnemy(Enemy_Type::BASIC, 600, 620);

	return true;
}

Update_Status Scene_03_nivel2::Update() {

	if (!App->player->alive) {
		App->fade->FadeToBlack((Module*)this, (Module*)App->scene_01_tutorial, 60);
	}

	if (App->player->position.x <= 10)
		App->player->position.x = 10;
	if (App->player->position.x >= weigthNivell - 10 - 128)
		App->player->position.x = weigthNivell - 10 - 128;

	if (App->player->position.y <= 10)
		App->player->position.y = 10;
	if (App->player->position.y >= heightNivell - 128 - 10)
		App->player->position.y = heightNivell - 128 - 10;


	if (App->player->position.x > 0 && App->player->position.x < weigthNivell - 1920) App->render->camera.x = App->player->position.x;
	if (App->player->position.y > 540 && App->player->position.y < heightNivell - 1080 + 540) App->render->camera.y = App->player->position.y - 540;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Scene_03_nivel2::PostUpdate() {
	App->render->Blit(textura_fondo3, 0, 0, &rectFondo);
	return Update_Status::UPDATE_CONTINUE;
}

bool Scene_03_nivel2::CleanUp() {
	App->oscuridad->Disable();
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	App->player->lives = 3;
	return true;
}
