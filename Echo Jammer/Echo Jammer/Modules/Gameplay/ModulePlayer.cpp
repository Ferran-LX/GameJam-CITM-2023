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

	currentAnimation = &idleSouthAnim;

	position.x = 300;
	position.y = 300;

#pragma region IDLE
	// IDLE NORTH
	for (int i = 0; i < numFrames - 8; i++)
		idleNorthAnim.PushBack({ 128 * i, 128 * 11, 128, 128 });
	idleNorthAnim.loop = true;
	idleNorthAnim.speed = 0.2f;

	// IDLE NORTH - EAST
	for (int i = 0; i < numFrames - 8; i++)
		idleNorthEastAnim.PushBack({ 128 * i, 128 * 11, 128, 128 });
	idleNorthEastAnim.loop = true;
	idleNorthEastAnim.speed = 0.2f;

	// IDLE EAST
	for (int i = 0; i < numFrames - 8; i++)
		idleEastAnim.PushBack({ 128 * i, 128 * 9, 128, 128 });
	idleEastAnim.loop = true;
	idleEastAnim.speed = 0.2f;

	// IDLE SOUTH - EAST
	for (int i = 0; i < numFrames - 8; i++)
		idleSouthEastAnim.PushBack({ 128 * i, 128 * 10, 128, 128 });
	idleSouthEastAnim.loop = true;
	idleSouthEastAnim.speed = 0.2f;

	// IDLE SOUTH
	for (int i = 0; i < numFrames - 8; i++)
		idleSouthAnim.PushBack({ 128 * i, 128 * 10, 128, 128 });
	idleSouthAnim.loop = true;
	idleSouthAnim.speed = 0.2f;

	// IDLE SOUTH - WEAST
	for (int i = 0; i < numFrames - 8; i++)
		idleSouthWeastAnim.PushBack({ 128 * i, 128 * 10, 128, 128 });
	idleSouthWeastAnim.loop = true;
	idleSouthWeastAnim.speed = 0.2f;

	// IDLE WEAST
	for (int i = 0; i < numFrames - 8; i++)
		idleWeastAnim.PushBack({ 128 * i, 128 * 8, 128, 128 });
	idleWeastAnim.loop = true;
	idleWeastAnim.speed = 0.2f;

	// IDLE NORTH - WEAST
	for (int i = 0; i < numFrames - 8; i++)
		idleNorthWeastAnim.PushBack({ 128 * i, 128 * 11, 128, 128 });
	idleNorthWeastAnim.loop = true;
	idleNorthWeastAnim.speed = 0.2f;

#pragma endregion


#pragma region MOVES
	// NORTH
	for (int i = 0; i < numFrames; i++)
		northAnim.PushBack({ 128 * i, 128 * 3, 128, 128 });
	northAnim.loop = true;
	northAnim.speed = 0.5f;

	// NORTH - EAST
	for (int i = 0; i < numFrames; i++)
		northEastAnim.PushBack({ 128 * i, 128 * 5, 128, 128 });
	northEastAnim.loop = true;
	northEastAnim.speed = 0.5f;

	// EAST
	for (int i = 0; i < numFrames; i++)
		eastAnim.PushBack({ 128 * i, 128 * 1, 128, 128 });
	eastAnim.loop = true;
	eastAnim.speed = 0.4f;

	// SOUTH - EAST
	for (int i = 0; i < numFrames; i++)
		southEastAnim.PushBack({ 128 * i, 128 * 6, 128, 128 });
	southEastAnim.loop = true;
	southEastAnim.speed = 0.5f;

	// SOUTH
	for (int i = 0; i < numFrames; i++)
		southAnim.PushBack({ 128 * i, 128 * 2, 128, 128 });
	southAnim.loop = true;
	southAnim.speed = 0.5f;

	// SOUTH - WEAST
	for (int i = 0; i < numFrames; i++)
		southWeastAnim.PushBack({ 128 * i, 128 * 7, 128, 128 });
	southWeastAnim.loop = true;
	southWeastAnim.speed = 0.5f;

	// WEAST
	for (int i = 0; i < numFrames; i++)
		weastAnim.PushBack({ 128 * i, 128 * 0, 128, 128 });
	weastAnim.loop = true;
	weastAnim.speed = 0.4f;

	// NORTH - WEAST
	for (int i = 0; i < numFrames; i++)
		northWeastAnim.PushBack({ 128 * i, 128 * 4, 128, 128 });
	northWeastAnim.loop = true;
	northWeastAnim.speed = 0.4f;

#pragma endregion

	return true;
}

Update_Status ModulePlayer::Update() {
	switch (actualDirection)
	{
	case Directions::NORTH: LOG("DIR actual: NORTH"); break;
	case Directions::NORTH_EAST: LOG("DIR actual: NORTH-EAST"); break;
	case Directions::EAST: LOG("DIR actual: EAST"); break;
	case Directions::SOUTH_EAST: LOG("DIR actual: SOUTH-EAST"); break;
	case Directions::SOUTH: LOG("DIR actual: SOUTH"); break;
	case Directions::SOUTH_WEST: LOG("DIR actual: SOUTH-WEST"); break;
	case Directions::WEST: LOG("DIR actual: WEST"); break;
	case Directions::NORTH_WEST: LOG("DIR actual: NORTH-WEST"); break;
	default: break;
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{ // NORTH - EAST
		currentAnimation = &northEastAnim;
		position.y -= speed;
		position.x += speed - 1;
		actualDirection = Directions::NORTH_EAST;
	}
	else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT) {
		// SOUTH - EAST
		currentAnimation = &southEastAnim;
		position.y += speed;
		position.x += speed - 1;
		actualDirection = Directions::SOUTH_EAST;
	}
	else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) {
		// SOUTH - WEAST
		currentAnimation = &southWeastAnim;
		position.y += speed;
		position.x -= speed - 1;
		actualDirection = Directions::SOUTH_WEST;
	}
	else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) {
		// NORTH - WEAST
		currentAnimation = &northWeastAnim;
		position.y -= speed;
		position.x -= speed - 1;
		actualDirection = Directions::NORTH_WEST;
	}
	else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT) {
		// NORTH
		currentAnimation = &northAnim;
		position.y -= speed;
		actualDirection = Directions::NORTH;
	}
	else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) {
		// SOUTH
		currentAnimation = &southAnim;
		position.y += speed;
		actualDirection = Directions::SOUTH;
	}
	else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT) {
		// EAST
		currentAnimation = &eastAnim;
		position.x += speed - 1;
		actualDirection = Directions::EAST;
	}
	else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) {
		// WEAST
		currentAnimation = &weastAnim;
		position.x -= speed - 1;
		actualDirection = Directions::WEST;
	}
	else
	{
		// Per defecte IDLE
		if (actualDirection == Directions::NORTH) currentAnimation = &idleNorthAnim;
		else if (actualDirection == Directions::NORTH_EAST) currentAnimation = &idleNorthEastAnim;
		else if (actualDirection == Directions::EAST) currentAnimation = &idleEastAnim;
		else if (actualDirection == Directions::SOUTH_EAST) currentAnimation = &idleSouthEastAnim;
		else if (actualDirection == Directions::SOUTH) currentAnimation = &idleSouthAnim;
		else if (actualDirection == Directions::SOUTH_WEST) currentAnimation = &idleSouthWeastAnim;
		else if (actualDirection == Directions::WEST) currentAnimation = &idleWeastAnim;
		else if (actualDirection == Directions::NORTH_WEST) currentAnimation = &idleNorthWeastAnim;
		else currentAnimation = &idleSouthAnim;
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