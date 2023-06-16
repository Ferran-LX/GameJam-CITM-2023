#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "../../SDLs/SDL/include/SDL_rect.h"

#define MAX_LISTENERS 5

class Module;

struct Collider {
	enum Type {
		NONE = -1,
		WALL,
		PLAYER,
		ENEMY,
		PLAYER_SHOT,
		ENEMY_SHOOT,
		CHEST,
		POWER_UP,
		WALL_PLAYER,
		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__

