#ifndef __SCENE_03_NIVEL2_H__
#define __SCENE_03_NIVEL2_H__

#include "../Module.h"
#include "../../Utils/Animation.h"
#include "../../Application/FileNames.h"

struct SDL_Texture;

class Scene_03_nivel2 : public Module {

public:
	Scene_03_nivel2(bool startEnabled);
	~Scene_03_nivel2();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();

	SDL_Texture* textura_fondo3 = nullptr;
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