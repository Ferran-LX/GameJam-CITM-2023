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
#include "../../Utils/DirectionHelper.h"

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
	position.y = 00;

#pragma region IDLE
	// IDLE NORTH
	for (int i = 0; i < _numFrames - 10; i++)
		_idleNorthAnim.PushBack({ 128 * i, 128 * 12, 128, 128 });
	_idleNorthAnim.loop = true;
	_idleNorthAnim.speed = 0.2f;

	// IDLE NORTH - EAST
	for (int i = 0; i < _numFrames - 10; i++)
		_idleNorthEastAnim.PushBack({ 128 * i, 128 * 12, 128, 128 });
	_idleNorthEastAnim.loop = true;
	_idleNorthEastAnim.speed = 0.2f;

	// IDLE EAST
	for (int i = 0; i < _numFrames - 10; i++)
		_idleEastAnim.PushBack({ 128 * i, 128 * 14, 128, 128 });
	_idleEastAnim.loop = true;
	_idleEastAnim.speed = 0.2f;

	// IDLE SOUTH - EAST
	for (int i = 0; i < _numFrames - 10; i++)
		_idleSouthEastAnim.PushBack({ 128 * i, 128 * 13, 128, 128 });
	_idleSouthEastAnim.loop = true;
	_idleSouthEastAnim.speed = 0.2f;

	// IDLE SOUTH
	for (int i = 0; i < _numFrames - 10; i++)
		_idleSouthAnim.PushBack({ 128 * i, 128 * 13, 128, 128 });
	_idleSouthAnim.loop = true;
	_idleSouthAnim.speed = 0.2f;

	// IDLE SOUTH - WEAST
	for (int i = 0; i < _numFrames - 10; i++)
		_idleSouthWeastAnim.PushBack({ 128 * i, 128 * 13, 128, 128 });
	_idleSouthWeastAnim.loop = true;
	_idleSouthWeastAnim.speed = 0.2f;

	// IDLE WEAST
	for (int i = 0; i < _numFrames - 10; i++)
		_idleWeastAnim.PushBack({ 128 * i, 128 * 15, 128, 128 });
	_idleWeastAnim.loop = true;
	_idleWeastAnim.speed = 0.2f;

	// IDLE NORTH - WEAST
	for (int i = 0; i < _numFrames - 10; i++)
		_idleNorthWeastAnim.PushBack({ 128 * i, 128 * 15, 128, 128 });
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
	App->player->positionAnterior = App->player->position;

	PlaceHolderMove();

	collider->SetPos(position.x, position.y);

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate() {
	_currentAnimation->Update();
	App->render->Blit(texture, position.x, position.y, &_currentAnimation->GetCurrentFrame());
	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {

	if (c2->type == Collider::WALL) {
		if (c1->rect.x < c2->rect.x + c2->rect.w
			&& c1->rect.x + c1->rect.w > c2->rect.x
			&& c1->rect.y < c2->rect.y + c2->rect.h
			&& c1->rect.y + c1->rect.h > c2->rect.y) {

			position = positionAnterior;
			//LOG("Hay superposici�n");
		}
	}

	if (c2->type == Collider::TR_NIVELL_T1) {
		App->player->Disable();
		App->enemies->Disable();
		App->collisions->Disable();

		// TODO: Disable scene tutorial, ascensor, and enable scene level 1
		// TODO: En la escena fer un enable de los apartados anteriores
	}

	if (c2->type == Collider::TR_NIVELL_12) {

	}

	if (c2->type == Collider::TR_NIVELL_23) {

	}

	if (c2->type == Collider::TR_NIVELL_3F) {

	}




	//iPoint enemyCenter = { position.x + (c1->rect.w >> 1), position.y + (c1->rect.h >> 1) };
	//iPoint colCenter = { c2->rect.x + (c2->rect.w >> 1), c2->rect.y + (c2->rect.h >> 1) };
	//iPoint distVector = colCenter - position;

	//Directions dir = DirectionHelper::GetDirection(enemyCenter, colCenter);
	////LOG("Distance to collider center: (%i,%i)", distVector.x, distVector.y);
	////LOG("Direction to collider center: %i", DirToInt(dir));


	//fPoint normalizedDir = { (float)distVector.x, (float)distVector.y };
	//normalizedDir = normalizedDir.Normalized();
	//normalizedDir *= 3;

	//iPoint pushVect = { (int)-normalizedDir.x, (int)-normalizedDir.y };

	//position += pushVect;


}

void ModulePlayer::PlaceHolderMove()
{
	const PlayerInput& controller = App->input->controlP1;

	if (controller.moveUp == Key_State::KEY_REPEAT && controller.moveRight == Key_State::KEY_REPEAT)
	{ // NORTH - EAST
		_currentAnimation = &_northEastAnim;
		position.y -= speed;
		position.x += speed;
		_actualDirection = Directions::NORTH_EAST;
	}
	else if (controller.moveDown == Key_State::KEY_REPEAT && controller.moveRight == Key_State::KEY_REPEAT) {
		// SOUTH - EAST
		_currentAnimation = &_southEastAnim;
		position.y += speed;
		position.x += speed;
		_actualDirection = Directions::SOUTH_EAST;
	}
	else if (controller.moveDown == Key_State::KEY_REPEAT && controller.moveLeft == Key_State::KEY_REPEAT) {
		// SOUTH - WEAST
		_currentAnimation = &_southWeastAnim;
		position.y += speed;
		position.x -= speed;
		_actualDirection = Directions::SOUTH_WEST;
	}
	else if (controller.moveUp == Key_State::KEY_REPEAT && controller.moveLeft == Key_State::KEY_REPEAT) {
		// NORTH - WEAST
		_currentAnimation = &_northWeastAnim;
		position.y -= speed;
		position.x -= speed;
		_actualDirection = Directions::NORTH_WEST;
	}
	else if (controller.moveUp == Key_State::KEY_REPEAT) {
		// NORTH
		_currentAnimation = &_northAnim;
		position.y -= speed;
		_actualDirection = Directions::NORTH;
	}
	else if (controller.moveDown == Key_State::KEY_REPEAT) {
		// SOUTH
		_currentAnimation = &_southAnim;
		position.y += speed;
		_actualDirection = Directions::SOUTH;
	}
	else if (controller.moveRight == Key_State::KEY_REPEAT) {
		// EAST
		_currentAnimation = &_eastAnim;
		position.x += speed;
		_actualDirection = Directions::EAST;
	}
	else if (controller.moveLeft == Key_State::KEY_REPEAT) {
		// WEAST
		_currentAnimation = &_weastAnim;
		position.x -= speed;
		_actualDirection = Directions::WEST;
	}
	else
	{
		// Per defecte IDLE
		if (_actualDirection == Directions::NORTH) _currentAnimation = &_idleNorthAnim;
		else if (_actualDirection == Directions::NORTH_EAST) _currentAnimation = &_idleNorthEastAnim;
		else if (_actualDirection == Directions::EAST) _currentAnimation = &_idleEastAnim;
		else if (_actualDirection == Directions::SOUTH_EAST) _currentAnimation = &_idleSouthEastAnim;
		else if (_actualDirection == Directions::SOUTH) _currentAnimation = &_idleSouthAnim;
		else if (_actualDirection == Directions::SOUTH_WEST) _currentAnimation = &_idleSouthWeastAnim;
		else if (_actualDirection == Directions::WEST) _currentAnimation = &_idleWeastAnim;
		else if (_actualDirection == Directions::NORTH_WEST) _currentAnimation = &_idleNorthWeastAnim;
		else _currentAnimation = &_idleSouthAnim;
	}

}

Directions ModulePlayer::GetInputDirection()
{
	const PlayerInput& p1 = App->input->controlP1;
	iPoint dirVect;

	dirVect.y += (int)(p1.moveUp == Key_State::KEY_REPEAT ? -1 : 0);
	dirVect.y += (int)(p1.moveDown == Key_State::KEY_REPEAT ? 1 : 0);
	dirVect.x += (int)(p1.moveLeft == Key_State::KEY_REPEAT ? -1 : 0);
	dirVect.x += (int)(p1.moveRight == Key_State::KEY_REPEAT ? 1 : 0);

	Directions ret = DirectionHelper::GetDirection({ 0,0 }, dirVect);
	return ret;
}

void ModulePlayer::ApplyMovement() {
}
