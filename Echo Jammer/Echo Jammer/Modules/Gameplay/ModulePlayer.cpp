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

	_currentAnimation = &_idleSouthAnim;

	position.x = 300;
	position.y = 300;

#pragma region IDLE
	// IDLE NORTH
	for (int i = 0; i < _numFrames - 8; i++)
		_idleNorthAnim.PushBack({ 128 * i, 128 * 11, 128, 128 });
	_idleNorthAnim.loop = true;
	_idleNorthAnim.speed = 0.2f;

	// IDLE NORTH - EAST
	for (int i = 0; i < _numFrames - 8; i++)
		_idleNorthEastAnim.PushBack({ 128 * i, 128 * 11, 128, 128 });
	_idleNorthEastAnim.loop = true;
	_idleNorthEastAnim.speed = 0.2f;

	// IDLE EAST
	for (int i = 0; i < _numFrames - 8; i++)
		_idleEastAnim.PushBack({ 128 * i, 128 * 9, 128, 128 });
	_idleEastAnim.loop = true;
	_idleEastAnim.speed = 0.2f;

	// IDLE SOUTH - EAST
	for (int i = 0; i < _numFrames - 8; i++)
		_idleSouthEastAnim.PushBack({ 128 * i, 128 * 10, 128, 128 });
	_idleSouthEastAnim.loop = true;
	_idleSouthEastAnim.speed = 0.2f;

	// IDLE SOUTH
	for (int i = 0; i < _numFrames - 8; i++)
		_idleSouthAnim.PushBack({ 128 * i, 128 * 10, 128, 128 });
	_idleSouthAnim.loop = true;
	_idleSouthAnim.speed = 0.2f;

	// IDLE SOUTH - WEAST
	for (int i = 0; i < _numFrames - 8; i++)
		_idleSouthWeastAnim.PushBack({ 128 * i, 128 * 10, 128, 128 });
	_idleSouthWeastAnim.loop = true;
	_idleSouthWeastAnim.speed = 0.2f;

	// IDLE WEAST
	for (int i = 0; i < _numFrames - 8; i++)
		_idleWeastAnim.PushBack({ 128 * i, 128 * 8, 128, 128 });
	_idleWeastAnim.loop = true;
	_idleWeastAnim.speed = 0.2f;

	// IDLE NORTH - WEAST
	for (int i = 0; i < _numFrames - 8; i++)
		_idleNorthWeastAnim.PushBack({ 128 * i, 128 * 11, 128, 128 });
	_idleNorthWeastAnim.loop = true;
	_idleNorthWeastAnim.speed = 0.2f;

#pragma endregion


#pragma region MOVES
	// NORTH
	for (int i = 0; i < _numFrames; i++)
		_northAnim.PushBack({ 128 * i, 128 * 3, 128, 128 });
	_northAnim.loop = true;
	_northAnim.speed = 0.5f;

	// NORTH - EAST
	for (int i = 0; i < _numFrames; i++)
		_northEastAnim.PushBack({ 128 * i, 128 * 5, 128, 128 });
	_northEastAnim.loop = true;
	_northEastAnim.speed = 0.5f;

	// EAST
	for (int i = 0; i < _numFrames; i++)
		_eastAnim.PushBack({ 128 * i, 128 * 1, 128, 128 });
	_eastAnim.loop = true;
	_eastAnim.speed = 0.5f;

	// SOUTH - EAST
	for (int i = 0; i < _numFrames; i++)
		_southEastAnim.PushBack({ 128 * i, 128 * 6, 128, 128 });
	_southEastAnim.loop = true;
	_southEastAnim.speed = 0.5f;

	// SOUTH
	for (int i = 0; i < _numFrames; i++)
		_southAnim.PushBack({ 128 * i, 128 * 2, 128, 128 });
	_southAnim.loop = true;
	_southAnim.speed = 0.5f;

	// SOUTH - WEAST
	for (int i = 0; i < _numFrames; i++)
		_southWeastAnim.PushBack({ 128 * i, 128 * 7, 128, 128 });
	_southWeastAnim.loop = true;
	_southWeastAnim.speed = 0.5f;

	// WEAST
	for (int i = 0; i < _numFrames; i++)
		_weastAnim.PushBack({ 128 * i, 128 * 0, 128, 128 });
	_weastAnim.loop = true;
	_weastAnim.speed = 0.5f;

	// NORTH - WEAST
	for (int i = 0; i < _numFrames; i++)
		_northWeastAnim.PushBack({ 128 * i, 128 * 4, 128, 128 });
	_northWeastAnim.loop = true;
	_northWeastAnim.speed = 0.5f;

	for (int i = 0; i < 26; i++)
		_deathAnim.PushBack({ 128 * i, 128 * 16, 128, 128 });
	_deathAnim.loop = true;
	_deathAnim.speed = 0.5f;

	_currentAnimation = &_deathAnim;

#pragma endregion

	return true;
}

Update_Status ModulePlayer::Update() {
	//switch (_actualDirection)
	//{
	//case Directions::NORTH: LOG("DIR actual: NORTH"); break;
	//case Directions::NORTH_EAST: LOG("DIR actual: NORTH-EAST"); break;
	//case Directions::EAST: LOG("DIR actual: EAST"); break;
	//case Directions::SOUTH_EAST: LOG("DIR actual: SOUTH-EAST"); break;
	//case Directions::SOUTH: LOG("DIR actual: SOUTH"); break;
	//case Directions::SOUTH_WEST: LOG("DIR actual: SOUTH-WEST"); break;
	//case Directions::WEST: LOG("DIR actual: WEST"); break;
	//case Directions::NORTH_WEST: LOG("DIR actual: NORTH-WEST"); break;
	//default: break;
	//}

	//if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	//{ // NORTH - EAST
	//	_currentAnimation = &_northEastAnim;
	//	position.y -= speed;
	//	position.x += speed;
	//	_actualDirection = Directions::NORTH_EAST;
	//}
	//else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT) {
	//	// SOUTH - EAST
	//	_currentAnimation = &_southEastAnim;
	//	position.y += speed;
	//	position.x += speed;
	//	_actualDirection = Directions::SOUTH_EAST;
	//}
	//else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) {
	//	// SOUTH - WEAST
	//	_currentAnimation = &_southWeastAnim;
	//	position.y += speed;
	//	position.x -= speed;
	//	_actualDirection = Directions::SOUTH_WEST;
	//}
	//else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) {
	//	// NORTH - WEAST
	//	_currentAnimation = &_northWeastAnim;
	//	position.y -= speed;
	//	position.x -= speed;
	//	_actualDirection = Directions::NORTH_WEST;
	//}
	//else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT) {
	//	// NORTH
	//	_currentAnimation = &_northAnim;
	//	position.y -= speed;
	//	_actualDirection = Directions::NORTH;
	//}
	//else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) {
	//	// SOUTH
	//	_currentAnimation = &_southAnim;
	//	position.y += speed;
	//	_actualDirection = Directions::SOUTH;
	//}
	//else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT) {
	//	// EAST
	//	_currentAnimation = &_eastAnim;
	//	position.x += speed;
	//	_actualDirection = Directions::EAST;
	//}
	//else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) {
	//	// WEAST
	//	_currentAnimation = &_weastAnim;
	//	position.x -= speed;
	//	_actualDirection = Directions::WEST;
	//}
	//else
	//{
	//	// Per defecte IDLE
	//	if (_actualDirection == Directions::NORTH) _currentAnimation = &_idleNorthAnim;
	//	else if (_actualDirection == Directions::NORTH_EAST) _currentAnimation = &_idleNorthEastAnim;
	//	else if (_actualDirection == Directions::EAST) _currentAnimation = &_idleEastAnim;
	//	else if (_actualDirection == Directions::SOUTH_EAST) _currentAnimation = &_idleSouthEastAnim;
	//	else if (_actualDirection == Directions::SOUTH) _currentAnimation = &_idleSouthAnim;
	//	else if (_actualDirection == Directions::SOUTH_WEST) _currentAnimation = &_idleSouthWeastAnim;
	//	else if (_actualDirection == Directions::WEST) _currentAnimation = &_idleWeastAnim;
	//	else if (_actualDirection == Directions::NORTH_WEST) _currentAnimation = &_idleNorthWeastAnim;
	//	else _currentAnimation = &_idleSouthAnim;
	//}


	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate() {
	_currentAnimation->Update();
	App->render->Blit(texture, position.x, position.y, &_currentAnimation->GetCurrentFrame());
	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {




}