#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include <SDL_rect.h>

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

	Collider(SDL_Rect rectangle, Type type, void (*listener)(Collider*, Collider*) = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	// Añade módulo cuya funcion OnCollision llamar cuando colisiona
	void AddListener(Module* listener);

	// Añade funcion a llamar cuando colisiona
	void AddListener(void (*listener)(Collider*, Collider*));

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };


	void (*listenerFunctions[MAX_LISTENERS])(Collider*, Collider*) = { nullptr };
};


#endif // !__COLLIDER_H__

