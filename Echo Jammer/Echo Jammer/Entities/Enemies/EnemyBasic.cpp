#include "EnemyBasic.h"
#include "../../Application/Application.h"
#include "../../Modules/Gameplay/ModulePlayer.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"
#include "../../Utils/EnemyStateMachine.h"
#include "TransitionConditionsBasic.h"
#include "../../Utils/Collider.h"

EnemyBasic::EnemyBasic(int x_, int y_) : Enemy(x_, y_, Enemy_Type::BASIC)
{
	_speed = 5;
	_aggro = 0;
	_aggroMax = 50;
	_attackRange = 5;
	_visionRange = 10;
	_searchRange = 15;
	InitStateMachine();
}

EnemyBasic::~EnemyBasic()
{
}

void EnemyBasic::InitStateMachine()
{
	// Explicació de funcions lambda
	// https://www.geeksforgeeks.org/lambda-expression-in-c/s

	ModulePlayer* player = App->player;
	if (_stateMachine == nullptr) _stateMachine = new EnemyStateMachine();

	_stateMachine->AddTransition(Enemy_State::PATRULLANT, Enemy_State::PERSEGUINT,
		[this, &player]() -> bool { return Transitions_Basic::Patrulla_Perseguir(*this, player->position); });

	_stateMachine->AddTransition(Enemy_State::PERSEGUINT, Enemy_State::CERCANT,
		[this, &player]() -> bool { return Transitions_Basic::Perseguir_Cerca(*this, player->position); });

	_stateMachine->AddTransition(Enemy_State::PERSEGUINT, Enemy_State::ATACANT,
		[this, &player]() -> bool { return Transitions_Basic::Perseguir_Atacar(*this, player->position); });

	_stateMachine->AddTransition(Enemy_State::CERCANT, Enemy_State::PERSEGUINT,
		[this, &player]() -> bool { return Transitions_Basic::Cerca_Perseguir(*this, player->position); });

	_stateMachine->AddTransition(Enemy_State::CERCANT, Enemy_State::PATRULLANT,
		[this]() -> bool { return Transitions_Basic::Cerca_Patrulla(*this); });

	_stateMachine->AddTransition(Enemy_State::ATACANT, Enemy_State::PERSEGUINT,
		[&player]() -> bool { return Transitions_Basic::Atacar_Perseguir(*player); });

	_stateMachine->AddTransition(Enemy_State::ATACANT, Enemy_State::JOC_FINALITZAT,
		[&player]() -> bool { return Transitions_Basic::Atacar_Final(*player); });

}
