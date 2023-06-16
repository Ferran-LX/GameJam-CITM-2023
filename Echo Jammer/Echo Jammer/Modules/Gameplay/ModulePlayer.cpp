#include "ModulePlayer.h"

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
#include "../../Modules/Gameplay/SceneLevel1.h"
#include "../../Modules/Gameplay/ScenePantallaLose.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"

#include <stdio.h>
#include <SDL_timer.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled) {

	// idle animation - just one sprite
	idleAnim.PushBack({ 97, 687, 119, 111 });

	// move rightF
	rightAnim.PushBack({ 97, 363, 119, 111 });
	rightAnim.loop = false;
	rightAnim.speed = 0.5f;

	// Move left
	leftAnim.PushBack({ 353, 523, 119, 111 });

	leftAnim.loop = false;
	leftAnim.speed = 0.5f;

	//BLUE BUFF	
	// Change sprite
	blueBUFF.PushBack({ 50, 683, 217, 118 });
	blueBUFF.speed = 0.1f;

	//Move right
	blueright.PushBack({ 53, 363, 217, 118 });
	blueright.loop = false;
	blueright.speed = 0.5f;

	// Move left
	blueleft.PushBack({ 56, 520, 217, 118 });
	blueleft.loop = false;
	blueleft.speed = 0.5f;

	//PINK BUFF
	// Change sprite
	pinkBUFF.PushBack({ 300, 684, 217, 118 });
	pinkBUFF.speed = 0.1f;

	//Move right
	pinkright.PushBack({ 300, 360, 217, 118 });
	pinkright.loop = false;
	pinkright.speed = 0.5f;

	// Move left
	pinkleft.PushBack({ 298, 522, 217, 118 });
	pinkleft.loop = false;
	pinkleft.speed = 0.5f;

	pinkBUFF.PushBack({ 300, 684, 217, 118 });
	pinkBUFF.speed = 0.1f;

	//GREEN BUFF
	// Change sprite
	greenBUFF.PushBack({ 551, 684, 217, 118 });
	greenBUFF.speed = 0.1f;

	//Move right
	greenright.PushBack({ 553, 363, 217, 118 });
	greenright.loop = false;
	greenright.speed = 0.5f;

	// Move left
	greenleft.PushBack({ 552, 518, 217, 118 });
	greenleft.loop = false;
	greenleft.speed = 0.5f;

}

ModulePlayer::~ModulePlayer() {
}

bool ModulePlayer::Start() {
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load(FI_spritePlayer_1.c_str());
	currentAnimation = &idleAnim;

	explosionjugadorFx = App->audio->LoadFx(FA_Fx_explosionJ.c_str()); ;

	position.x = 183;
	position.y = 3665;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 119, 111 }, Collider::Type::PLAYER, this);
	backupPosition.x = 100;
	backupPosition.y = position.y - SCREEN_HEIGHT;
	return ret;
}

Update_Status ModulePlayer::Update() {

if (!stopGame) {
	GamePad& pad = App->input->pads[0];
	
	// Moving the player with the camera scroll
	App->player->position.y += App->sceneLevel_1->velocitatNivell;
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN || pad.l1==true)
		godMode = !godMode;

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT || pad.l_y < 0.0f) position.y -= speed;
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT || pad.l_y > 0.0f) position.y += speed;
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT || pad.l_x > 0.0f)
	{
		position.x += speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT || pad.l_x < 0.0f)
	{
		position.x -= speed;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true)
	{
		if (canshootlaser)
		{
			start_time = SDL_GetTicks();
			canshootlaser = false;
			if (Powerupred)
			{
				App->particles->AddParticle(App->particles->knifeleft, position.x + 25, position.y, Collider::Type::PLAYER_SHOT, 0);
				App->particles->AddParticle(App->particles->kniferight, position.x + 150, position.y, Collider::Type::PLAYER_SHOT, 0);
				App->particles->AddParticle(App->particles->knifeleft, position.x - 25, position.y, Collider::Type::PLAYER_SHOT, 0);
				App->particles->AddParticle(App->particles->kniferight, position.x + 200, position.y, Collider::Type::PLAYER_SHOT, 0);
				App->particles->AddParticle(App->particles->laser2, position.x + 60, position.y - 50, Collider::Type::PLAYER_SHOT, 0);
			}
			if (Powerupblue)
			{
				App->particles->AddParticle(App->particles->laser2, position.x + 60, position.y - 50, Collider::Type::PLAYER_SHOT, 0);

				App->particles->AddParticle(App->particles->axeleft, position.x - 5, position.y, Collider::Type::PLAYER_SHOT, 0);

				App->particles->AddParticle(App->particles->axeright, position.x + 140, position.y, Collider::Type::PLAYER_SHOT, 0);
			}
			if (Powerupgreen)
			{
				App->particles->AddParticle(App->particles->sword, position.x, position.y-150, Collider::Type::PLAYER_SHOT, 0);
				App->particles->AddParticle(App->particles->sword, position.x + 165, position.y-150, Collider::Type::PLAYER_SHOT, 0);
				App->particles->AddParticle(App->particles->laser2, position.x + 60, position.y - 50, Collider::Type::PLAYER_SHOT, 0);
			}
			if (!Powerupblue && !Powerupgreen && !Powerupred)
			{
				App->particles->AddParticle(App->particles->laser1, position.x + 35, position.y, Collider::Type::PLAYER_SHOT, 0);
			}
		}
		if (SDL_GetTicks() - start_time >= 50)
		{
			canshootlaser = true;
		}
	}

	// Spawn explosion particles when pressing B
	if (App->input->keys[SDL_SCANCODE_B] == Key_State::KEY_DOWN || pad.x == true)
	{
		if (canshootbomb && bombs > 0)
		{
			start_time = SDL_GetTicks();
			canshootbomb = false;
			if (Powerupblue)
			{
				App->particles->AddParticle(App->particles->bomb, position.x-40, position.y - 130, Collider::Type::PLAYER_SHOT, 0);
			}
			if (Powerupred)
			{
				App->particles->AddParticle(App->particles->bomb, position.x-40 , position.y - 130, Collider::Type::PLAYER_SHOT, 0);
			}
			if (Powerupgreen)
			{
				App->particles->AddParticle(App->particles->bomb, position.x-40, position.y - 130, Collider::Type::PLAYER_SHOT, 0);
			}
			if (!Powerupblue && !Powerupgreen && !Powerupred)
			{
				App->particles->AddParticle(App->particles->bomb, position.x-85, position.y - 130, Collider::Type::PLAYER_SHOT, 0);
			}
			bombs--;
		}
		if (SDL_GetTicks()-start_time>=2000)
		{
			canshootbomb = true;
		}
	}

	// If no up/down movement detected, set the current animation back to idle
	if (pad.enabled)
	{
		if (pad.l_x == 0.0f && pad.l_y == 0.0f)
			currentAnimation = &idleAnim;
	}
	else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		currentAnimation = &idleAnim;

	//update collider
	collider->SetPos(position.x, position.y);
	currentAnimation->Update();

	if (Powerupblue == true)
	{
		currentAnimation = &blueBUFF;
		collider->rect.w = 217;
		collider->rect.h = 118;

		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT || pad.l_x > 0.0f)

		{
			position.x += speed;
			if (currentAnimation != &blueright)
			{
				blueright.Reset();
				currentAnimation = &blueright;
			}
		}
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT || pad.l_x < 0.0f)

		{
			position.x -= speed;
			if (currentAnimation != &blueleft)
			{
				blueleft.Reset();
				currentAnimation = &blueleft;
			}
		}
	}
	if (Powerupgreen == true)
	{
		currentAnimation = &greenBUFF;
		collider->rect.w = 217;
		collider->rect.h = 118;

		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT || pad.l_x > 0.0f)
		{
			position.x += speed;
			if (currentAnimation != &greenright)
			{
				blueright.Reset();
				currentAnimation = &greenright;
			}
		}
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT || pad.l_x < 0.0f)
		{
			position.x -= speed;
			if (currentAnimation != &greenleft)
			{
				blueleft.Reset();
				currentAnimation = &greenleft;
			}
		}
	}
	if (Powerupred == true)
	{
		currentAnimation = &pinkBUFF;
		collider->rect.w = 217;
		collider->rect.h = 118;

		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT || pad.l_x > 0.0f)
		{
			position.x += speed;
			if (currentAnimation != &pinkright)
			{
				blueright.Reset();
				currentAnimation = &pinkright;
			}
		}
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT || pad.l_x < 0.0f)
		{
			position.x -= speed;
			if (currentAnimation != &pinkleft)
			{
				blueleft.Reset();
				currentAnimation = &pinkleft;
			}
		}
	}

	if (destroyed)
	{
		destroyedCountdown--;
		if (destroyedCountdown == 0)
		{
			destroyed = false;
			destroyedCountdown = 50;
			canshootbomb = false;
			canshootlaser = false;
			collider->type = Collider::Type::PLAYER;
		}
	}

	// WIN CONDITION
		if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN || pad.r2 == true)
		{
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneOutro, 60); //Menu start no intro
		}

		// LOSE CONDITION
		if (lives == 0 || App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN || pad.l2 == true)
		{
			App->sceneLevel_1->stopGame = true;
			App->player->stopGame = true;
			App->enemies->stopGame = true;
			App->scenePantallaLose->Enable();
		}

}
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate() {
	if (!destroyed) {
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}
	else
	{
		canshootbomb = false;
		canshootlaser = false;
		if (destroyedCountdown <= 0)
		{
			position.x = backupPosition.x;
			position.y = backupPosition.y;
			destroyed = false;
		}
	}

	

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {

	// TODO: POWERUP, pendiente a resolver
	//if (c1->Intersects(c2->rect) || c2->Intersects(c1->rect) && c1->type == Collider::Type::OBJECTCHEST)
	//{
	//	// Change sprite
	//	currentAnimation = &blueBUFF;
	//Cuan colisiona el jugador amb l'enemic 
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY && !destroyed && !godMode)//Cuando tengamos godmode se le dara uso
	{

		App->particles->AddParticle(App->particles->playerdead, position.x, position.y, Collider::Type::NONE, 0);
		collider->type = Collider::Type::NONE;
		destroyed = true;
		LOG("player dead");
		position.x = 100;
		position.y = position.y + SCREEN_HEIGHT;

		//Powerup = false;
		collider->rect.w = 119;
		Powerupblue = false;
		Powerupgreen = false;
		Powerupred = false;
		lives--;

	}
	//Cuan colisiona amb Power up
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::POWER_UP)
	{
		//Green
		if (c2->rect.w == 63)
		{
			Powerupgreen = true;
			Powerupblue = false;
			Powerupred = false;
		}
		//Blue
		if (c2->rect.w==62)
		{
			Powerupblue = true;
			Powerupgreen = false;
			Powerupred = false;
		}
		//Red
		if (c2->rect.w==64)
		{
			Powerupred = true;
			Powerupgreen = false;
			Powerupblue = false;
		}
		//+1 bomba
		if (c2->rect.w == 116)
		{
			bombs++;
		}
		// + Score
		if (c2->rect.w == 46)
		{
			score += 23;
		}
	}
}