#ifndef __SCENE_LEVEL1_FOREGROUND_H__
#define __SCENE_LEVEL1_FOREGROUND_H__

#include "../../Modules/Module.h"
#include "../../Utils/Animation.h"

struct SDL_Texture;

class SceneLevel1_Foreground : public Module {

public:
	//Constructor
	SceneLevel1_Foreground(bool startEnabled);

	//Destructor
	~SceneLevel1_Foreground();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();


public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* texture_columna = nullptr;
	SDL_Texture* texture_hermosa = nullptr;
	SDL_Texture* texture_adorable = nullptr;
	
	int velocitatNivell;
};

#endif