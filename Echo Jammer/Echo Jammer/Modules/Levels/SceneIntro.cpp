#include "SceneIntro.h"
#include <SDL_image.h>

#include "../../Application/Application.h"
#include "../../Application/FileNames.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleInput.h"
#include "../../Modules/Core/ModuleFadeToBlack.h"
#include "../../Utils/p2Point.h"
#include "../../Utils/Animation.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"


SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled) {
}

SceneIntro::~SceneIntro() {
}

// Load assets
bool SceneIntro::Start() {
	LOG("Loading background assets SCENE INTRO");

	bool ret = true;

	startTime = SDL_GetTicks();
	
	

	

	//Carga de Audio ////TURMO MUY IMPORTANTE, TIENES QUE CUADRAR EL AUDIO CON LA INTRO SEGUN LAS IMAGENES QUE APAREZCAN///
	//esta musica hay que cambiarla turmo

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	

	return ret;
}

//NO TOCAR NADA //FadeToBlack de Intro -> Juego
Update_Status SceneIntro::Update() {
	GamePad& pad = App->input->pads[0];
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true) {
		App->fade->FadeToBlack(this, (Module*)App->sceneStart, 60);
		/*App->fade->FadeToBlack(this, (Module*)App->sceneOutro, 60); */          //OUTRO --> descomentar para probar, comentar arriba.

	}

	if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_DOWN)
	{
		//tokenFx = App->audio->LoadFx(FA_Fx_token.c_str());
	};
	////Update path positions
	//fuegos.Update();
	////Update Animations
	//fuegos.GetCurrentAnimation()->Update();

	return Update_Status::UPDATE_CONTINUE;

}

// Update: draw background
Update_Status SceneIntro::PostUpdate() {
	//DIBUJADO DE LAS IMAGENES DE LA INTRO
	Uint32 currentTime = SDL_GetTicks() - startTime;

	if (currentTime >= 3000 && currentTime < 5500) {

		App->render->Blit(ArrayImagesIntro[0], 0, 0, NULL);//jovani

	}

	if (currentTime >= 6000 && currentTime < 9000) {

		App->render->Blit(ArrayImagesIntro[1], 0, 0, NULL);//Raizing

	}

	if (currentTime >= 9000) {

		App->render->Blit(ArrayImagesIntro2[8], 0, 0, NULL);//fondonegro [sirve para no cubrir espacios]

	}

	if (currentTime >= 28500) {
		int y = (currentTime - 28500) / 1.1;
		App->render->Blit(ArrayImagesIntro[15], 0, y - 3000, NULL);//fondobatman 1

	}

	if (currentTime >= 28500) {
		int y = (currentTime - 28500) / 1.1;
		App->render->Blit(ArrayImagesIntro[15], 0, y - 6000, NULL);//fondobatman 2

	}

	if (currentTime >= 9000 && currentTime < 13000) {

		App->render->Blit(ArrayImagesIntro[2], -10, 0, NULL);//Primertextocolor

	}

	if (currentTime >= 10000 && currentTime < 18000) {
		//Adalt
		int x1 = (currentTime - 10000) / 100;
		App->render->Blit(ArrayImagesIntro2[7], -x1, -20, NULL);//holalluc
		App->render->Blit(ArrayImagesIntro2[7], -x1 + 200, -20, NULL);//holalluc
		if(play)
			{
			//App->audio->PlayMusic(FA_Music_introTitle.c_str());
			play = false;
			}
		//Abaix
		int x2 = (currentTime - 10000) / 100;//velocidad
		App->render->Blit(ArrayImagesIntro2[2], -x2 - 180, -100, NULL);//alientocho
		App->render->Blit(ArrayImagesIntro2[2], -x2 + 20, -100, NULL);//alientocho
		App->render->Blit(ArrayImagesIntro2[2], -x2 + 200, -100, NULL);//alientocho
		App->render->Blit(ArrayImagesIntro2[2], -x2 + 350, -100, NULL);//alientocho
		App->render->Blit(ArrayImagesIntro2[2], -x2 + 500, -100, NULL);//alientocho
		App->render->Blit(ArrayImagesIntro2[2], -x2 + 650, -100, NULL);//alientocho
		App->render->Blit(ArrayImagesIntro2[2], -x2 + 800, -100, NULL);//alientocho

		//foc 1

	
		//App->render->Blit(ArrayImagesIntro[4], -x2 + 285, -345, &(fuegos.GetCurrentAnimation()->GetCurrentFrame()));//fuego1

		App->render->Blit(ArrayImagesIntro2[9], -x2 + 435, -345, NULL);//fuego1
		App->render->Blit(ArrayImagesIntro2[9], -x2 + 285, -345, NULL);//fuego1
		App->render->Blit(ArrayImagesIntro2[9], -x2 + 135, -345, NULL);//fuego1
		App->render->Blit(ArrayImagesIntro2[9], -x2 - 15, -345, NULL);//fuego1
		App->render->Blit(ArrayImagesIntro2[9], -x2 - 195, -345, NULL);//fuego1
		App->render->Blit(ArrayImagesIntro2[9], -x2 - 375, -345, NULL);//fuego1


		//foc 2

		//foc 3


	}

	if (currentTime >= 13000 && currentTime < 18000) {

		App->render->Blit(ArrayImagesIntro[5], 0, 0, NULL);//segundotextocolor

	}

	if (currentTime >= 14000 && currentTime < 18000) {

		App->render->Blit(ArrayImagesIntro2[0], 0, 20, NULL);//alienarribafondo

		//nave1
		int x = (currentTime - 14000) / 100;
		int y = (currentTime - 14000) / 120;
		App->render->Blit(ArrayImagesIntro2[12], -x - 230, -y + 460, NULL);
		App->render->Blit(ArrayImagesIntro2[12], -x - 300, -y + 340, NULL);
		//nave2
		App->render->Blit(ArrayImagesIntro2[13], -x - 100, -y + 400, NULL);

		//rápidas
		int z = (currentTime - 14000) / 20;
		int u = (currentTime - 14000) / 25;
		App->render->Blit(ArrayImagesIntro2[13], -z + 100, -u + 400, NULL);
		App->render->Blit(ArrayImagesIntro2[13], -z + 200, -u + 400, NULL);
		App->render->Blit(ArrayImagesIntro2[13], -z + 250, -u + 400, NULL);
		//nave3
		App->render->Blit(ArrayImagesIntro2[14], -x + 300, -y + 400, NULL);
		//nave4
		App->render->Blit(ArrayImagesIntro2[15], -x + 300, -y + 270, NULL);

	}

	if (currentTime >= 18500 && currentTime < 22500) {

		App->render->Blit(ArrayImagesIntro[8], 0, 0, NULL);//tercertextocolor

	}

	if (currentTime >= 23000 && currentTime < 26000) {

		App->render->Blit(ArrayImagesIntro[10], 0, 0, NULL); //cuartotextocolor

	}
	//hasta 26000
	if (currentTime >= 23200) {
		//carauno
		int x = 0;
		int y = 0;
		if (currentTime >= 26000) {
			x = ((currentTime - 26000) / 1.5) * -1;
			y = ((currentTime - 26000) / 1.5) * -1;
		}
		App->render->Blit(ArrayImagesIntro2[6], x, y, NULL);

	}

	if (currentTime >= 23800) {
		//carados
		int x = 0;
		int y = 0;
		if (currentTime >= 26000) {
			x = ((currentTime - 26000) / 1.5);
			y = ((currentTime - 26000) / 1.5) * -1;
		}
		App->render->Blit(ArrayImagesIntro2[4], x, y, NULL);
	}

	if (currentTime >= 23400) {
		//caratres
		int x = 0;
		int y = 0;
		if (currentTime >= 26000) {
			x = ((currentTime - 26000) / 1.5);
			y = ((currentTime - 26000) / 1.5);
		}
		App->render->Blit(ArrayImagesIntro2[5], x, y, NULL);
	}

	if (currentTime >= 23600) {
		//caracuatro
		int x = 0;
		int y = 0;
		if (currentTime >= 26000) {
			x = ((currentTime - 26000) / 1.5) * -1;
			y = ((currentTime - 26000) / 1.5);
		}
		App->render->Blit(ArrayImagesIntro2[3], x, y, NULL);
	}

	if (currentTime >= 27500) {

		App->render->Blit(ArrayImagesIntro[13], 0, 0, NULL);//quintotextocolor

	}

	if (currentTime >= 28500) {

		App->render->Blit(ArrayImagesIntro[16], 0, 0, NULL);//Batman

	}

	if (currentTime >= 32000) {

		App->fade->FadeToBlack(this, (Module*)App->sceneStart, 60);

	}


	return Update_Status::UPDATE_CONTINUE;

}