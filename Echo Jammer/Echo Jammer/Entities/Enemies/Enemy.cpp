#include "Enemy.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Core/ModuleParticles.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"

Enemy::Enemy(int x_, int y_, Enemy_Type type_) : position(x_, y_), type(type_)
{
	_speed = 0;
	_aggro = 0;
	_aggroMax = 50;
	_attackRange = 0;
	_visionRange = 0;
	_searchRange = 0;
	_currState = Enemy_State::PATRULLANT;
	_spawnPos = position;
}

Enemy::~Enemy() {
	if (_collider != nullptr) 
		_collider->pendingToDelete = true;

	delete _stateMachine;
}

void Enemy::InitStateMachine() {}

void Enemy::Update() {
	if (_currentAnim != nullptr) 
		_currentAnim->Update();

	if (_collider != nullptr) 
		_collider->SetPos(position.x, position.y);
}

void Enemy::Draw() {
	if (_currentAnim != nullptr) 
		App->render->Blit(_texture, position.x, position.y, &(_currentAnim->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider) {
}

void Enemy::SetToDelete() {
	pendingToDelete = true;

	if (_collider != nullptr) 
		_collider->pendingToDelete = true;
}

void Enemy::SetCollider(Collider* nCollider)
{
	if (_collider != nullptr && _collider != nCollider)
		_collider->pendingToDelete = true;

	_collider = nCollider;
}