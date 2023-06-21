#ifndef __SCENE_02_NIVEL1_H__
#define __SCENE_02_NIVEL1_H__

#include "../Module.h"
#include "../../Utils/Animation.h"
#include "../../Application/FileNames.h"

struct SDL_Texture;

class Scene_02_nivel1 : public Module {

public:
	Scene_02_nivel1(bool startEnabled);
	~Scene_02_nivel1();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();

	SDL_Texture* textura_fondo = nullptr;
	SDL_Texture* textura_oscuridad = nullptr;
	SDL_Rect rectFondo;
	Collider* botcoll = nullptr;
	Collider* topcoll = nullptr;
	Collider* leftcoll = nullptr;
	Collider* raightcoll = nullptr;

	bool stopGame = false;
	int start_time;
	int velocitatNivell = 0;

private:
	Animation _deathAnim;

	int weigthNivell = 1920;
	int heightNivell = 2688;
};

#endif