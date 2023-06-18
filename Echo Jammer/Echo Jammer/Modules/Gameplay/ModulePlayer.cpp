#include "ModulePlayer.h"

#include <stdio.h>
#include <SDL_timer.h>

#include "../../Application/Application.h"
#include "../../Application/FileNames.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleInput.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Core/ModuleParticles.h"
#include "../../Modules/Core/ModuleAudio.h"
#include "../../Modules/Core/ModuleCollisions.h"
#include "../../Modules/Core/ModuleFadeToBlack.h"
#include "../../Modules/Core/ModuleFonts.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled) {


}

ModulePlayer::~ModulePlayer() {
}

bool ModulePlayer::Start()
{
	texture = App->textures->Load(FI_Player_moveset.c_str());
	collider = App->collisions->AddCollider({ position.x, position.y, 128, 128 }, Collider::Type::PLAYER, this);

	currentAnimation = &idleAnim;

	position.x = 300;
	position.y = 300;


	// ---MOVES

	// IDLE
	for (int i = 0; i < numFrames; i++)
		idleAnim.PushBack({ 128 * i, 128 * 3, 128, 128 });
	idleAnim.loop = true;
	idleAnim.speed = 0.5f;

	// NORTH
	for (int i = 0; i < numFrames; i++)
		northAnim.PushBack({ 128 * i, 128 * 3, 128, 128 });
	northAnim.loop = true;
	northAnim.speed = 0.5f;

	// EAST
	for (int i = 0; i < numFrames; i++)
		eastAnim.PushBack({ 128 * i, 128 * 1, 128, 128 });
	eastAnim.loop = true;
	eastAnim.speed = 0.4f;

	// SOUTH
	for (int i = 0; i < numFrames; i++)
		southAnim.PushBack({ 128 * i, 128 * 2, 128, 128 });
	southAnim.loop = true;
	southAnim.speed = 0.5f;

	// WEAST
	for (int i = 0; i < numFrames; i++)
		weastAnim.PushBack({ 128 * i, 128 * 0, 128, 128 });
	weastAnim.loop = true;
	weastAnim.speed = 0.4f;

	//northEastAnim;	
	//southEastAnim;
	//southWeastAnim;
	//northWeastAnim;

	return true;
}

Update_Status ModulePlayer::Update() {

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT) {
		currentAnimation = &northAnim;
		position.y -= speed;
	}
	else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) {
		currentAnimation = &southAnim;
		position.y += speed;
	}
	else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		currentAnimation = &eastAnim;
		position.x += speed - 1;
	}
	else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		currentAnimation = &weastAnim;
		position.x -= speed - 1;
	}
	else
	{
		// Per defecte IDLE
		currentAnimation = &idleAnim;
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate() {
	currentAnimation->Update();
	App->render->Blit(texture, position.x, position.y, &currentAnimation->GetCurrentFrame());
	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {


}