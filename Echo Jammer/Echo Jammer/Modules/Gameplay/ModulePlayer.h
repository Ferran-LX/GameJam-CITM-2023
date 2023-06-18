#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "../../Modules/Module.h"
#include "../../Utils/Animation.h"
#include "../../Utils/p2Point.h"
#include "../../Utils/Directions.h"


struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module {

public:
	ModulePlayer(bool startEnabled);
	~ModulePlayer();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	void OnCollision(Collider* c1, Collider* c2) override;

	int numFrames = 36; // Frames que tiene cada fila

	int lives = 3;
	bool godMode = false;
	int start_time;
	bool alive = true;
	bool stopGame = false;
	iPoint position;	

	int speed = 4;

	Directions actualDirection;
	SDL_Texture* texture = nullptr;
	Animation* currentAnimation = nullptr;

	Animation northAnim;
	Animation northEastAnim;
	Animation eastAnim;
	Animation southEastAnim;
	Animation southAnim;
	Animation southWeastAnim;
	Animation weastAnim;
	Animation northWeastAnim;

	Animation idleNorthAnim;	
	Animation idleNorthEastAnim;
	Animation idleEastAnim;
	Animation idleSouthEastAnim;
	Animation idleSouthAnim;
	Animation idleSouthWeastAnim;
	Animation idleWeastAnim;
	Animation idleNorthWeastAnim;

	// The player's collider
	Collider* collider = nullptr;
	Collider* colliderblue = nullptr;


	// A countdown to when the player gets destroyed. After a while, the game exits
	uint destroyedCountdown = 120;

	bool debugGamepadInfo = false;
};

#endif 