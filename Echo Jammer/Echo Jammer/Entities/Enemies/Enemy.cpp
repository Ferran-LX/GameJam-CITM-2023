#include "Enemy.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Core/ModuleParticles.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleRender.h"

Enemy::Enemy(int x_, int y_, Enemy_Type type_) : position(x_, y_), type(type_)
{
	_speed = 0;
	_spawnPos = position;
}

Enemy::~Enemy() {
	if (_collider != nullptr) 
		_collider->pendingToDelete = true;
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
	/*App->particles->AddParticle(App->particles->explosion2, position.x, position.y);*/
	//App->audio->PlayFx(destroyedFx);

	SetToDelete();
}

void Enemy::SetToDelete() {
	pendingToDelete = true;

	if (_collider != nullptr) 
		_collider->pendingToDelete = true;
}

//void Enemy::SetSpeed(int nSpeed)
//{
//	_speed = nSpeed;
//}

void Enemy::SetCollider(Collider* nCollider)
{
	if (_collider != nullptr && _collider != nCollider)
		_collider->pendingToDelete = true;

	_collider = nCollider;
}

//const Collider* Enemy::GetCollider() const {
//	return _collider;
//}

void Enemy::SetTexture(SDL_Texture* nTexture)
{
	_texture = nTexture;
}

//const SDL_Texture* Enemy::GetTexture() const
//{
//	return _texture;
//}
