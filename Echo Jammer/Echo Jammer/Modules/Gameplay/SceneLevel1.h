#ifndef __SCENE_LEVEL1_H__
#define __SCENE_LEVEL1_H__

#include "../../Modules/Module.h"
#include "../../Utils/Animation.h"
#include "../../Application/FileNames.h"

struct SDL_Texture;

class SceneLevel1 : public Module {

public:
	//Constructor
	SceneLevel1(bool startEnabled);

	//Destructor
	~SceneLevel1();

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
	SDL_Texture* texture_beach = nullptr;
	SDL_Texture* texture_sea = nullptr;
	SDL_Texture* texture_sea2 = nullptr;
	SDL_Texture* texture_forest1 = nullptr;
	SDL_Texture* texture_forest2 = nullptr;
	SDL_Texture* texture_castle = nullptr;
	SDL_Texture* texture_start = nullptr;
	SDL_Texture* texture_colum = nullptr;
	SDL_Texture* texture_arboles = nullptr;

	Collider* botcoll = nullptr;
	Collider* topcoll = nullptr;
	Collider* leftcoll = nullptr;
	Collider* raightcoll = nullptr;


	bool stopGame = false;
	int start_time;
	int velocitatNivell = 0;

	int xt = 0;
	int yt = 3000;
	int wt = SCREEN_WIDTH;
	int ht = 10;
	int TP = -(Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_forest1 + Height_background_sea + Height_background_sea + Height_background_castle-2000);

	int xb = 0;
	int yb = 4070;
	int wb = SCREEN_WIDTH;
	int hb = 10;


	int xl = 0;
	int yl = 3000;
	int wl = 10;
	int hl = SCREEN_HEIGHT;

	int xr = SCREEN_WIDTH - 10;
	int yr = 3000;
	int wr = 10;
	int hr = SCREEN_HEIGHT;

private:
	bool controlSalidaAeropuerco1 = false;
	bool controlSalidaAeropuerco2 = false;
	bool controlSalidaAeropuerco3 = false;
	bool controlSalidaAeropuerco4 = false;
	bool controlLlegadaCastillo1 = false;
	bool controlLlegadaCastillo2 = false;
	bool controlLlegadaBoss = false;
};

#endif