#include "SceneTESTS.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"
#include "../../Modules/Gameplay/ModulePlayer.h"

SceneTESTS::SceneTESTS(bool startEnabled) : Module(startEnabled) {
	
}

SceneTESTS::~SceneTESTS() {
}

bool SceneTESTS::Start()
{
	textura_fondo = App->textures->Load(FI_Mapa_Level1.c_str());
		
	rectFondo.x = 0;
	rectFondo.y = 0;
	rectFondo.w = 1920;
	rectFondo.h = 1080;
	

	//// POSITION INITIAL CAMERA
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();
	//App->collisions->Enable();

	App->enemies->AddEnemy(Enemy_Type::BASIC, 10, 10);

	return true;
}

Update_Status SceneTESTS::Update() {
	
	//LOG("Player POSX:%d POSY:%d", App->player->position.x, App->player->position.y);
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneTESTS::PostUpdate() {
	App->render->Blit(textura_fondo, 0, 0, &rectFondo);
	return Update_Status::UPDATE_CONTINUE;
}

bool SceneTESTS::CleanUp() {
	App->player->Disable();
	App->enemies->Disable();
	//App->collisions->Disable();
	App->player->lives = 3;
	return true;
}
