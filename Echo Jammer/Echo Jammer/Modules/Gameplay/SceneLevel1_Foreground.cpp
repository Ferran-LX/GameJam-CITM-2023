#include "SceneLevel1_Foreground.h"

#include "../../Application/Application.h"
#include "../../Application/FileNames.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Core/ModuleInput.h"
#include "../Gameplay/ModuleEnemies.h"
#include "../Gameplay/ModulePlayer.h"
#include "../Gameplay/SceneLevel1.h"


SceneLevel1_Foreground::SceneLevel1_Foreground(bool startEnabled) : Module(startEnabled){
}

SceneLevel1_Foreground::~SceneLevel1_Foreground() {
}

bool SceneLevel1_Foreground::Start(){
	LOG("Loading background assets SCENE 1");

	bool ret = true;

	velocitatNivell = App->sceneLevel_1->velocitatNivell;



	texture_columna = App->textures->Load(FI_background_precolumnas.c_str());
	//texture_bonita = App->textures->Load(BORRAR_2.c_str());
	//texture_hermosa = App->textures->Load(BORRAR_3.c_str());


	return ret;
}

Update_Status SceneLevel1_Foreground::Update(){
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneLevel1_Foreground::PostUpdate(){

	// Aqui pintem totes les imatges que van sobre de enemics i scena1, pero no de player
	

	App->render->Blit(texture_columna, 0, -SCREEN_HEIGHT * -1, NULL);
	 //Aqui pintem totes les imatges que van sobre de enemics i scena1, pero no de player
	//App->render->Blit(texture_adorable, 0, (Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	//App->render->Blit(texture_bonita, 0, (Height_background_forest1 + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);
	//App->render->Blit(texture_hermosa, 0, (Height_background_forest1 + Height_background_forest1 + Height_background_forest1 - SCREEN_HEIGHT) * -1, NULL);



	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1_Foreground::CleanUp(){
	return true;
}
