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

	void PlaceHolderMove();

	Directions GetInputDirection();

	void ApplyMovement();

	int lives = 3;
	bool godMode = false;
	bool alive = true;
	iPoint position;
	iPoint positionAnterior;
	bool stopGame = false;
	int speed = 5;
	SDL_Texture* texture = nullptr;
	Collider* collider = nullptr;
	Collider* secCollider = nullptr;

private:
	int _numFrames = 36; // Frames que tiene cada fila
	int _start_time;
	Directions _actualDirection;

	Animation* _currentAnimation = nullptr;

	Animation _deathAnim;

	Animation _northAnim;
	Animation _northEastAnim;
	Animation _eastAnim;
	Animation _southEastAnim;
	Animation _southAnim;
	Animation _southWeastAnim;
	Animation _weastAnim;
	Animation _northWeastAnim;

	Animation _idleNorthAnim;
	Animation _idleNorthEastAnim;
	Animation _idleEastAnim;
	Animation _idleSouthEastAnim;
	Animation _idleSouthAnim;
	Animation _idleSouthWeastAnim;
	Animation _idleWeastAnim;
	Animation _idleNorthWeastAnim;
};

#endif 