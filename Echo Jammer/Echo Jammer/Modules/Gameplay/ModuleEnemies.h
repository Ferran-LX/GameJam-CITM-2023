#ifndef __MODULE_ENEMIES_H__
#define __MODULE_ENEMIES_H__

#include "../../Modules/Module.h"
#include "../../Utils/Animation.h"
#include "../../Utils/Directions.h"
#include "../../Utils/p2Point.h"

#define MAX_ENEMIES 200

enum class Enemy_Type {
	NO_TYPE,
	BASIC,
	SPEEDY,
	BIG,
	INVISIBLE,

	ENEMY_TYPE_COUNT
};

enum Enemy_State {
	PATRULLANT,
	PERSEGUINT,
	ATACANT,
	CERCANT,
	BLOQUEJAT,
	CANSAT,
	JOC_FINALITZAT,

	MAX_STATES
};

struct EnemySpawnpoint {
	Enemy_Type type = Enemy_Type::NO_TYPE;
	int x, y;
};

class Enemy;
class PathFinder;
//struct EnemyStateMachine;
struct SDL_Texture;

class ModuleEnemies : public Module {

public:
	// Constructor
	ModuleEnemies(bool startEnabled);

	// Destructor
	~ModuleEnemies();

	bool stopGame = false;

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all enemies pending to delete
	Update_Status PreUpdate() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Deprecated. Use function callbacks instead
	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an enemy into the queue to be spawned later
	bool AddEnemy(Enemy_Type type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandleEnemiesSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleEnemiesDespawn();

	//Updates enemy paths and position
	void HandleEnemyMovement();

	// Retorna true si l'enemic veu el punt especificat
	bool CheckLineOfSight(const Enemy& e, const iPoint& p);


private:
	// Spawns a new enemy using the data from the queue
	void SpawnEnemy(const EnemySpawnpoint& info);


private:
	// A queue with all spawn points information
	EnemySpawnpoint _spawnQueue[MAX_ENEMIES];

	// All spawned enemies in the scene
	Enemy* _enemies[MAX_ENEMIES] = { nullptr };

	// The enemies' sprite sheets
	SDL_Texture* _textureBasic = nullptr;
	SDL_Texture* _textureSpeedy = nullptr;
	SDL_Texture* _textureBig = nullptr;
	SDL_Texture* _textureInvis = nullptr;

	// Animation sets

	Animation _animBasic[Enemy_State::MAX_STATES][DirToInt(Directions::DIRECTIONS_TOTAL)];
	Animation _animSpeedy[Enemy_State::MAX_STATES][DirToInt(Directions::DIRECTIONS_TOTAL)];
	Animation _animBig[Enemy_State::MAX_STATES][DirToInt(Directions::DIRECTIONS_TOTAL)];
	Animation _animInvis[Enemy_State::MAX_STATES][DirToInt(Directions::DIRECTIONS_TOTAL)];

	// Els enemics obtenen les seves rutes amb aixo
	PathFinder* _pathfinder = nullptr;

};

#endif // __MODULE_ENEMIES_H__