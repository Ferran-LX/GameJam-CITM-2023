#ifndef __SCENE_PANTALLALOSE_H__
#define __SCENE_PANTALLALOSE_H__

#include "../../Modules/Module.h"
#include "../../Utils/Animation.h"

struct SDL_Texture;

class ScenePantallaLose : public Module {

public:
	//Constructor
	ScenePantallaLose(bool startEnabled);

	//Destructor
	~ScenePantallaLose();

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
	#define NUM_IMAGES 9
	SDL_Texture* ArrayImagesContinue[NUM_IMAGES];
	int currentImage = 0;
	float timer = 0.0f;
	int startTime;
	bool play = true;
};

#endif
