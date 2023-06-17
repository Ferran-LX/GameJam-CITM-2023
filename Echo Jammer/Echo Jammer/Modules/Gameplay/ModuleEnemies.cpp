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

bool ModuleEnemies::Init()
{
	//Transicions robot bàsic
	EnemyStateTransition transition;
	transition.target = Enemy_State::PERSEGUINT;
	transition.condition = [&]() -> bool {return Transitions_Basic::Patrulla_Perseguir()}
	

	return true;
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

			//	// props
			//case Enemy_Type::CHEST_BLUE:enemies[i] = new Enemy_CHESS(info.x, info.y);break;
			//case Enemy_Type::Bluebook:enemies[i] = new Enemy_Bluebook(info.x, info.y);break;
			//case Enemy_Type::CHEST_GREEN:enemies[i] = new Enemy_GreenChess(info.x, info.y);break;
			//case Enemy_Type::Greenbook:enemies[i] = new Enemy_GreenBook(info.x, info.y);break;
			//case Enemy_Type::CHEST_RED:enemies[i] = new Enemy_RedChess(info.x, info.y);break;
			//case Enemy_Type::Redbook:enemies[i] = new Enemy_Redbook(info.x, info.y);break;
			//case Enemy_Type::ANGEL:enemies[i] = new Enemy_Angel(info.x, info.y);break;
			//case Enemy_Type::BOMB:enemies[i] = new Enemy_BOMB(info.x, info.y);break;
			//case Enemy_Type::GOLD:enemies[i] = new Enemy_Gold(info.x, info.y);break;
			//case Enemy_Type::COIN:enemies[i] = new Enemy_Coin(info.x, info.y);break;

			//	//Satge 1
			//case Enemy_Type::STAGE: enemies[i] = new Enemy_Stage(info.x, info.y); break;
			//case Enemy_Type::NUM1: enemies[i] = new Enemy_Num1(info.x, info.y); break;
			//case Enemy_Type::FLAG: enemies[i] = new Enemy_Flag(info.x, info.y); break;

			////Warning
			//case Enemy_Type::WARL: enemies[i] = new Enemy_WarnL(info.x, info.y); break;
			//case Enemy_Type::WARR: enemies[i] = new Enemy_WarnR(info.x, info.y); break;
			//case Enemy_Type::FLECH: enemies[i] = new Enemy_Flecha(info.x, info.y); break;
			////Stageclear
			//case Enemy_Type::STAGECLEAR: enemies[i] = new Enemy_Sclear(info.x, info.y); break;
			////Enemies

			//case Enemy_Type::DRAGON: enemies[i] = new Enemy_Dragon(info.x, info.y, info.wave);break;
			//case Enemy_Type::REDWIZARD: enemies[i] = new Enemy_RedWizard(info.x, info.y, info.wave);break;
			//case Enemy_Type::RED_BALL: enemies[i] = new Enemy_RedBall(info.x, info.y, info.wave);break;
			//case Enemy_Type::TANK: enemies[i] = new Enemy_Tank(info.x, info.y, info.wave);break;
			//case Enemy_Type::TURTLE: enemies[i] = new Enemy_Turtle(info.x, info.y, info.wave);break;
			//case Enemy_Type::MINIDRAGON: enemies[i] = new Enemy_MiniDragon(info.x, info.y, info.wave);break;
			//case Enemy_Type::FLYTANK: enemies[i] = new Enemy_FlyTank(info.x, info.y, info.wave);break;
			//case Enemy_Type::BIGTANK: enemies[i] = new Enemy_BigTank(info.x, info.y, info.wave);break;
			//case Enemy_Type::REDBAT: enemies[i] = new Enemy_RedBat(info.x, info.y, info.wave);break;
			//case Enemy_Type::BOSS: enemies[i] = new Boss_BreathDragon(info.x, info.y, info.wave); break;
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
			//c1->pendingToDelete = true;

			/*if (c2->type == Collider::Type::PLAYER_SHOT)
			{

				delete enemies[i];
				enemies[i] = nullptr;
			}
			break;*/
		}
	}
}