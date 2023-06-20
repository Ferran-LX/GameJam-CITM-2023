#include "Enemy.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Core/ModuleParticles.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"
#include "../../Modules/Gameplay/ModulePlayer.h"
#include "../../Utils/EnemyStateMachine.h"
#include "../../Utils/DirectionHelper.h"

#include "../../../SDLs/SDL/include/SDL_timer.h"

#define DIR_CHANGE_DELAY 500

Enemy::Enemy(int x_, int y_, Enemy_Type type_, Collider* collider_) : position(x_, y_), type(type_), _collider(collider_)
{
	_speed = 0;
	_aggro = 0;
	_aggroMax = 50;
	_attackRange = 0;
	_visionRange = 0;
	_searchRange = 0;
	_currState = Enemy_State::PATRULLANT;
	_currDirection = Directions::NONE;
	_spawnPos = position;
}

Enemy::~Enemy() {
	if (_collider != nullptr)
		_collider->pendingToDelete = true;

	delete _stateMachine;
}

void Enemy::InitStateMachine() {}

void Enemy::Update() {
	if (_moving) {
		if (_currentAnim != nullptr && _currentAnim == &(_animSet)[_currState][DirToInt(_currDirection)]) {
			_currentAnim->Update();
		}
		else {
			_currentAnim = &(_animSet)[_currState][DirToInt(_currDirection)];
		}
	}
	else {
		LOG("Can't move");
	}

	if (_collider != nullptr)
		_collider->SetPos(position.x, position.y);
}

void Enemy::UpdateBehaviour(const ModulePlayer* player)
{
}

void Enemy::Draw() {
	if (_currentAnim != nullptr)
		App->render->Blit(_texture, position.x, position.y, &(_currentAnim->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* otherCol) {
	iPoint enemyCenter = { position.x + (_collider->rect.w >> 1), position.y + (_collider->rect.h >> 1) };
	iPoint colCenter = { otherCol->rect.x + (otherCol->rect.w >> 1), otherCol->rect.y + (otherCol->rect.h >> 1) };
	iPoint distVector = colCenter - position;

	Directions dir = DirectionHelper::GetDirection(enemyCenter, colCenter);
	LOG("Distance to collider center: (%i,%i)", distVector.x, distVector.y);
	LOG("Direction to collider center: %i", DirToInt(dir));


	fPoint normalizedDir = { (float)distVector.x, (float)distVector.y };
	normalizedDir = normalizedDir.Normalized();
	normalizedDir *= 3;

	iPoint pushVect = { (int)-normalizedDir.x, (int)-normalizedDir.y };

	position += pushVect;

}

void Enemy::SetToDelete() {
	pendingToDelete = true;

	if (_collider != nullptr)
		_collider->pendingToDelete = true;
}

Directions Enemy::ChangeDirection()
{
	uint currTicks = SDL_GetTicks();
	if (_dirChangeTimer < currTicks) {
		_dirChangeTimer = SDL_GetTicks() + DIR_CHANGE_DELAY;

		return DirectionHelper::GetDirection(position, App->player->position);
	}
	return _currDirection;
}

void Enemy::HandleMove()
{
	//_moving = (position.DistanceTo(App->player->position) >= 20);
	if (_moving)
		Move(_currDirection);
}

bool Enemy::Move(Directions dir)
{

	switch (dir)
	{
	case Directions::NORTH: {
		position.y -= _speed;
		break;
	}
	case Directions::EAST: {
		position.x += _speed;
		break;
	}
	case Directions::NORTH_EAST: {
		position.x += _speed;
		position.y -= _speed;
		break;
	}
	case Directions::SOUTH: {
		position.y += _speed;
		break;
	}
	case Directions::SOUTH_EAST: {
		position.x += _speed;
		position.y += _speed;
		break;
	}
	case Directions::WEST: {
		position.x -= _speed;
		break;
	}
	case Directions::SOUTH_WEST: {
		position.x -= _speed;
		position.y += _speed;
		break;
	}
	case Directions::NORTH_WEST: {
		position.x -= _speed;
		position.y -= _speed;
		break;
	}
	case Directions::NONE:
	default:
		return false;
	}

	return true;
}

void Enemy::SetCollider(Collider* nCollider)
{
	if (_collider != nullptr && _collider != nCollider)
		_collider->pendingToDelete = true;

	_collider = nCollider;
	_collider->AddListener(&_collisionCallback);
}