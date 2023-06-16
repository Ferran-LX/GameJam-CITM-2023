#ifndef __MODULE_PARTICLES_H__
#define __MODULE_PARTICLES_H__

#include "../../Modules/Module.h"

#include "../../Application/Globals.h"
#include "../../Entities/Particle.h"
#include "../../Application/Application.h"
#include "../../Utils/Collider.h"

#define MAX_ACTIVE_PARTICLES 500

struct SDL_Texture;
struct Collider;

class ModuleParticles : public Module {

public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticles(bool startEnabled);

	//Destructor
	~ModuleParticles();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all particles pending to delete
	Update_Status PreUpdate() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	Particle* AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);


public:
	//Template particle for an explosion
	Particle explosion;
	Particle bomb;
	Particle bomb2;

	//Template particle for a laser
	Particle laser1;
	Particle laser2;

	//Template for extra shots
	Particle axeright;
	Particle axeleft;

	Particle kniferight;
	Particle knifeleft;

	Particle sword;
	Particle greenpart;


	//Template for deads
	Particle playerdead;
	Particle FlyTankdead;
	//wizard shoot
	Particle wizardshoot;
	//goblinship shoot
	Particle goblinshot;
	//dragonshoot / turtle shoot
	Particle minifireshot;
	Particle minifireshottank;

	//disparos para tortuga
	Particle minifireshot1;
	Particle minifireshot2;
	Particle minifireshot3;
	Particle minifireshot4;
	Particle minifireshot5;
	Particle minifireshot6;



private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;
	SDL_Texture* texture2 = nullptr;
	SDL_Texture* texture3 = nullptr;
	SDL_Texture* texture4 = nullptr;
	SDL_Texture* texture5 = nullptr;

	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

};

#endif // !__MODULEPARTICLES_H__