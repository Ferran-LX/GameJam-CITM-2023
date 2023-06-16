#ifndef __SCENE_PREINTRO_H__
#define __SCENE_PREINTRO_H__

#include "../../Modules/Module.h"
#include "../../Utils/Animation.h"

struct SDL_Texture;


class ScenePreintro : public Module {

public:
	//Constructor
	ScenePreintro(bool startEnabled);
	//Destructor
	~ScenePreintro();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;


public:

	//Amb GetTicks
#define NUM_IMAGES 1
	int startTime;
	SDL_Texture* ArrayImagesPreintro[NUM_IMAGES];

	uint tokenFx = 0;
};

#endif
	