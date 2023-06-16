#include "Enemy.h"

#include "../../Application/Application.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Core/ModuleParticles.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleRender.h"

Enemy::Enemy(int x, int y) : position(x, y) {
	spawnPos = position;
}

Enemy::~Enemy() {
	if (collider != nullptr) 
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const {
	return collider;
}

void Enemy::Update() {
	if (currentAnim != nullptr) 
		currentAnim->Update();

	if (collider != nullptr) 
		collider->SetPos(position.x, position.y);
}

void Enemy::Draw() {
	if (currentAnim != nullptr) 
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider) {
	/*App->particles->AddParticle(App->particles->explosion2, position.x, position.y);*/
	App->audio->PlayFx(destroyedFx);

	SetToDelete();
}

void Enemy::SetToDelete() {
	pendingToDelete = true;

	if (collider != nullptr) 
		collider->pendingToDelete = true;
}