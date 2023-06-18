#pragma once
#include "../Module.h"

class SceneTestArea : public Module {
public:
	//Constructor
	SceneTestArea(bool startEnabled);
	//Destructor
	~SceneTestArea();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	//Called at the end of the application
	bool CleanUp() override;

private:

	// Dependencies
	ModuleEnemies* enemies = nullptr;
	ModulePlayer* player = nullptr;


	// Imatges de l'escena
#define NUM_IMAGES 1
	SDL_Texture* _imageArray[NUM_IMAGES] = { nullptr };

};

