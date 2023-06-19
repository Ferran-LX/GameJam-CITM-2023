#ifndef __SCENE_0_PORTADA_H__
#define __SCENE_0_PORTADA_H__

#include "../Module.h"
#include "../../Utils/Animation.h"
#include "../../Application/FileNames.h"

struct SDL_Texture;

class Scene0Portada : public Module {

public:
	Scene0Portada(bool startEnabled);
	~Scene0Portada();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();

	SDL_Texture* textura = nullptr;

private:
	int _numFrames = 16;
	Animation* _currentAnimation = nullptr;
	Animation _animPortada;
};

#endif