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
#define NUM_IMAGES 1
	SDL_Texture* ArrayImagesStart[NUM_IMAGES];

	SDL_Texture* textura = nullptr;

private:
	int _numFramesPerFila = 8;
	int _numFiles = 6;
	int startTime;
	Animation* _currentAnimation = nullptr;
	Animation _animPortada;
};

#endif