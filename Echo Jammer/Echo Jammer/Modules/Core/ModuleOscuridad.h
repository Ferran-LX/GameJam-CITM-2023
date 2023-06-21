#ifndef __MODULE_OSCURIDAD_H__
#define __MODULE_OSCURIDAD_H__

#include "../Module.h"
#include "../../Utils/Animation.h"
#include "../../Application/FileNames.h"


struct SDL_Texture;

class ModuleOscuridad : public Module {

public:
	ModuleOscuridad(bool startEnabled);
	~ModuleOscuridad();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();
//#define NUM_IMAGES 1
//	SDL_Texture* ArrayImagesStart[NUM_IMAGES];

	SDL_Texture* textura_oscuridad = nullptr;

private:
	int _numFramesPerFila = 8;
	int _numFiles = 6;
	int startTime;
	int oscuridad_x = 0;
	int oscuridad_y = 0;
	Animation* _currentAnimation = nullptr;
	Animation _animPortada;
};

#endif