#include "ModuleEnemies.h"

#include "../../Application/Application.h"
#include "../../Application/FileNames.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleCollisions.h"

#include "../../Entities/Enemies/Enemy.h"
#include "../../Entities/Enemies/EnemyBasic.h"
#include "../../Entities/Enemies/TransitionConditionsBasic.h"
#include "../../Utils/EnemyStateMachine.h"
#include "../../Utils/Pathfinding/PathFinder.h"


#define SPAWN_MARGIN 100


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled),
		_animVec(Enemy_State::MAX_STATES, std::vector<Animation>(DirToInt(Directions::DIRECTIONS_TOTAL)))
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		_enemies[i] = nullptr;

	_pathfinder = new PathFinder();

#pragma region ROBOT_BASIC

	//Patrulla
	_animVec[Enemy_State::PATRULLANT][DirToInt(Directions::NONE)].PushBack({ 0,128,64,64 });
	for (int i = 0; i < 20; i++)
	{
		_animVec[Enemy_State::PATRULLANT][DirToInt(Directions::WEST)].PushBack({ 64 * i,64 * 0,64,64 });
		_animVec[Enemy_State::PATRULLANT][DirToInt(Directions::EAST)].PushBack({ 64 * i,64 * 1,64,64 });
		_animVec[Enemy_State::PATRULLANT][DirToInt(Directions::SOUTH)].PushBack({ 64 * i,64 * 2,64,64 });
		_animVec[Enemy_State::PATRULLANT][DirToInt(Directions::NORTH)].PushBack({ 64 * i,64 * 3,64,64 });
		_animVec[Enemy_State::PATRULLANT][DirToInt(Directions::NORTH_WEST)].PushBack({ 64 * i,64 * 4,64,64 });
		_animVec[Enemy_State::PATRULLANT][DirToInt(Directions::NORTH_EAST)].PushBack({ 64 * i,64 * 5,64,64 });
		_animVec[Enemy_State::PATRULLANT][DirToInt(Directions::SOUTH_EAST)].PushBack({ 64 * i,64 * 6,64,64 });
		_animVec[Enemy_State::PATRULLANT][DirToInt(Directions::SOUTH_WEST)].PushBack({ 64 * i,64 * 7,64,64 });
	}

	//Persecucio es la mateixa que patrulla
	_animVec[Enemy_State::PERSEGUINT] = _animVec[Enemy_State::PATRULLANT];

	//Per ara tots els estats tenen les mateixes animacions
	_animVec[Enemy_State::CERCANT] = _animVec[Enemy_State::PATRULLANT];
	_animVec[Enemy_State::ATACANT] = _animVec[Enemy_State::PATRULLANT];
	_animVec[Enemy_State::CANSAT] = _animVec[Enemy_State::PATRULLANT];
	_animVec[Enemy_State::BLOQUEJAT] = _animVec[Enemy_State::PATRULLANT];
	_animVec[Enemy_State::JOC_FINALITZAT] = _animVec[Enemy_State::PATRULLANT];

#pragma endregion

#pragma region ROBOT_BIG

#pragma endregion

}

ModuleEnemies::~ModuleEnemies() {
}

bool ModuleEnemies::Start() {
	LOG("Loading enemy assets");

	_textureBasic = App->textures->Load(FI_Enemy_Basic.c_str());
	//_textureBasic = App->textures->Load(FI_Enemy_Speedy.c_str());
	//_textureBasic = App->textures->Load(FI_Enemy_Big.c_str());
	//_textureBasic = App->textures->Load(FI_Enemy_Invisible.c_str());

	return true;
}


Update_Status ModuleEnemies::PreUpdate() {
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (_enemies[i] != nullptr && _enemies[i]->pendingToDelete) {
			delete _enemies[i];
			_enemies[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::Update() {
	if (!stopGame)
	{
		HandleEnemiesSpawn();

		for (uint i = 0; i < MAX_ENEMIES; ++i) {
			if (_enemies[i] != nullptr)
				_enemies[i]->Update();
		}

		HandleEnemiesDespawn();

		HandleEnemyMovement();


	}
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::PostUpdate() {
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (_enemies[i] != nullptr)
			_enemies[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp() {
	LOG("Freeing all _enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (_enemies[i] != nullptr) {
			delete _enemies[i];
			_enemies[i] = nullptr;
		}
	}

	LOG("Unloading textures");

	App->textures->Unload(_textureBasic);	_textureBasic	= nullptr;
	App->textures->Unload(_textureSpeedy);	_textureSpeedy	= nullptr;
	App->textures->Unload(_textureBig);		_textureBig		= nullptr;
	App->textures->Unload(_textureInvis);	_textureInvis	= nullptr;

	return true;
}

Enemy* ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y)
{
	EnemySpawnpoint info;
	info.type = type;
	info.x = x;
	info.y = y;
	SpawnEnemy(info);

	return SpawnEnemy(info);
	/*bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (_spawnQueue[i].type == Enemy_Type::NO_TYPE) {
			_spawnQueue[i].type = type;
			_spawnQueue[i].x = x;
			_spawnQueue[i].y = y;

			ret = true;
			break;
		}
	}

	return ret;*/
}

void ModuleEnemies::HandleEnemiesSpawn() {
	// TODO cambiar logica de spawn

	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (_spawnQueue[i].type != Enemy_Type::NO_TYPE) {
			// Spawn a new enemy if the screen has reached a spawn position
			if (_spawnQueue[i].y > App->render->camera.y) {
				//LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(_spawnQueue[i]);
				_spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn() {
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (_enemies[i] != nullptr) {
			// Delete the enemy when it has reached the end of the screen
			if (_enemies[i]->position.x < -300 && _enemies[i]->position.x >1200 && _enemies[i]->position.y == 1100) {
				//LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				_enemies[i]->SetToDelete();
			}
		}
	}
}

void ModuleEnemies::HandleEnemyMovement() {
	for (uint i = 0; i < MAX_ENEMIES; i++)
	{
		if (_enemies[i] != nullptr) {
			_enemies[i]->UpdateBehaviour(App->player);
		}
	}
}

bool ModuleEnemies::CheckLineOfSight(const Enemy& e, const iPoint& p) {
	bool ret = true;

	return ret;
}


Enemy* ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info) {
	Enemy* ret = nullptr;
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (_enemies[i] == nullptr) {
			switch (info.type) {
			case Enemy_Type::BASIC: {
				_enemies[i] = ret = new EnemyBasic(info.x, info.y);
				_enemies[i]->SetTexture(_textureBasic);
				_enemies[i]->SetState(Enemy_State::PATRULLANT);
				_enemies[i]->ChangeAnimationSet(_animVec);
				_enemies[i]->SetCollider(App->collisions->AddCollider({ 0,0,64,64 }, Collider::Type::ENEMY));
				break;
			}
			default: break;
			}

			//enemies[i]->destroyedFx = enemyDestroyedFx;

			break;
		}
	}
	return ret;
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2) {
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (_enemies[i] != nullptr && _enemies[i]->GetCollider() == c1) {
			_enemies[i]->OnCollision(c2); //Notify the enemy of a collision

		}
	}
}