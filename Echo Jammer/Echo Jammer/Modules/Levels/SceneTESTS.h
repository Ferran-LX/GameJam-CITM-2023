#ifndef __SCENE_TESTS_H__
#define __SCENE_TESTS_H__

#include "../Module.h"
#include "../../Utils/Animation.h"
#include "../../Application/FileNames.h"

struct SDL_Texture;

class SceneTESTS : public Module {

public:
	SceneTESTS(bool startEnabled);
	~SceneTESTS();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();

	SDL_Texture* textura_fondo = nullptr;
	SDL_Rect rectFondo;
	Collider* botcoll = nullptr;
	Collider* topcoll = nullptr;
	Collider* leftcoll = nullptr;
	Collider* raightcoll = nullptr;

	bool stopGame = false;
	int start_time;
	int velocitatNivell = 0;

	int weigthNivell = 1920;
	int heightNivell = 2688;
};

#endif