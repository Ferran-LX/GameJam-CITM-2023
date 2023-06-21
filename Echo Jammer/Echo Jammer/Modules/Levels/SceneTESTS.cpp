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
	rectFondo.w = weigthNivell;
	rectFondo.h = heightNivell;

	//// POSITION INITIAL CAMERA
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();

	// TODO: Poner en la posicion inical / puerta del nivel
	App->player->position.x = 400;
	App->player->position.y = 500;
	App->player->collider->SetPos(400, 500);


	App->enemies->AddEnemy(Enemy_Type::BASIC, 10, 100);

	
	

	App->collisions->AddCollider({ 1088, 1600, 576, 64 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1088, 1664, 320, 128 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1088, 1792, 64, 448 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 1088, 2496, 64, 192 }, Collider::Type::WALL);
	
	App->collisions->AddCollider({ 1792, 1600, 128, 512 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 1152, 960, 128, 360 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1280, 1088, 128, 232 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1408 , 1216 , 128, 103  }, Collider::Type::WALL);

	App->collisions->AddCollider({ 1536 , 572+236 +32 , 128 , 100 }, Collider::Type::WALL);

	return true;
}

Update_Status SceneTESTS::Update() {


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
