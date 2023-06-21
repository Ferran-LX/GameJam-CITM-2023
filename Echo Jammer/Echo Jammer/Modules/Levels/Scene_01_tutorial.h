#ifndef __SCENE_01_TUTORIAL_H__
#define __SCENE_01_TUTORIAL_H__

#include "../Module.h"
#include "../../Utils/Animation.h"
#include "../../Application/FileNames.h"

struct SDL_Texture;

class Scene_01_tutorial : public Module {

public:
	Scene_01_tutorial(bool startEnabled);
	~Scene_01_tutorial();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();

	SDL_Texture* textura_fondo = nullptr;
	SDL_Texture* textura_detecion = nullptr;
	SDL_Rect rectFondo;
	Collider* botcoll = nullptr;
	Collider* topcoll = nullptr;
	Collider* leftcoll = nullptr;
	Collider* raightcoll = nullptr;

	bool stopGame = false;

	bool detectionActive = false;

	int start_time;
	int velocitatNivell = 0;

	int widthNivell = 1920*2;
	int heightNivell = 1080;

	Animation _animDetecion;
};

#endif