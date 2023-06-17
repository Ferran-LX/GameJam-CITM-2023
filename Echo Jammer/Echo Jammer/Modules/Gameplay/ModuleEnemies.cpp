#include "ModuleEnemies.h"

#include "../../Application/Application.h"
#include "../../Application/FileNames.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleAudio.h"

#include "../../Entities/Enemies/Enemy.h"
#include "../../Entities/Enemies/EnemyBasic.h"
#include "../../Entities/Enemies/TransitionConditionsBasic.h"
#include "../../Utils/EnemyStateMachine.h"


#define SPAWN_MARGIN 100


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled) {
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
	_stateMachine = new EnemyStateMachine();
}

ModuleEnemies::~ModuleEnemies() {
	delete _stateMachine;
}

bool ModuleEnemies::Start() {
	return true;
}


Update_Status ModuleEnemies::PreUpdate() {
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete) {
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::Update() {
	if (!stopGame)
	{
		HandleEnemiesSpawn();

		for (uint i = 0; i < MAX_ENEMIES; ++i) {
			if (enemies[i] != nullptr)
				enemies[i]->Update();
		}

		HandleEnemiesDespawn();
	}
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::PostUpdate() {
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp() {
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr) {
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (spawnQueue[i].type == Enemy_Type::NO_TYPE) {
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;

			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn() {
	// TODO cambiar logica de spawn

	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE) {
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].y > App->render->camera.y) {
				//LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn() {
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr) {
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.x < -300 && enemies[i]->position.x >1200 && enemies[i]->position.y == 1100) {
				//LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				enemies[i]->SetToDelete();
			}
		}
	}
}


void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info) {
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] == nullptr) {
			switch (info.type) {
			case Enemy_Type::BASIC: enemies[i] = new EnemyBasic(info.x, info.y); break;
			default: break;
			}

			//enemies[i]->destroyedFx = enemyDestroyedFx;

			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2) {
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1) {
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			
		}
	}
}