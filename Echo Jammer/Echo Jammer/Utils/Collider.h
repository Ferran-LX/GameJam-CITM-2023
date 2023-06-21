#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include <SDL_rect.h>
#include <functional>

#define MAX_LISTENERS 5

class Module;

struct Collider {
	enum Type {
		NONE = -1,
		WALL,
		PLAYER,
		ENEMY,
		// TRIGGERS
		TR_NIVELL_T1, // Tutorial -> Nivel 1
		TR_NIVELL_12, // Nivel 1 -> Nivel 2
		TR_NIVELL_23, // Nivel 2 -> Nivel 3
		TR_NIVELL_3F, // Nivel 3 -> FINAL
		ECO,
		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener);

	Collider(SDL_Rect rectangle, Type type, std::function<void(Collider*, Collider*)>* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	// Añade módulo cuya funcion OnCollision llamar cuando colisiona
	void AddListener(Module* listener);

	// Añade funcion a llamar cuando colisiona
	void AddListener(std::function<void(Collider*, Collider*)>* listener);

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };


	std::function<void(Collider*, Collider*)>* listenerFunctions[MAX_LISTENERS]{ nullptr };
};


#endif // !__COLLIDER_H__

