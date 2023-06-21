#include "EnemyBasic.h"
#include "TransitionConditionsBasic.h"
#include "../../Application/Application.h"
#include "../../Modules/Gameplay/ModulePlayer.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"
#include "../../Utils/EnemyStateMachine.h"
#include "../../Utils/Collider.h"
#include "../../Utils/p2Point.h"
#include "../../Utils/DirectionHelper.h"
#include <SDL_timer.h>


EnemyBasic::EnemyBasic(int x_, int y_, Collider* collider_) : Enemy(x_, y_, Enemy_Type::BASIC, collider_)
{
	_speed = 4;
	_aggro = 50;
	_aggroMax = 50;
	_attackRange = 20;
	_visionRange = 270;
	_searchRange = 230;
	_attackDelay = 1000;
	InitStateMachine();

	_collisionCallback = [&](Collider* c1, Collider* c2) -> void {
		//LOG("EnemyBasic: Collision at (%i,%i)", position.x, position.y);
		OnCollision(c2);
	};

	if (_collider != nullptr)
		_collider->AddListener(&_collisionCallback);

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

	_stateMachine->AddTransition(Enemy_State::PATRULLANT, Enemy_State::PERSEGUINT, 0,
		[this, &player]() -> bool { return Transitions_Basic::Patrulla_Perseguir(*this, App->player); });

	_stateMachine->AddTransition(Enemy_State::PERSEGUINT, Enemy_State::CERCANT, 0,
		[this, &player]() -> bool { return Transitions_Basic::Perseguir_Cerca(*this, App->player); });

	_stateMachine->AddTransition(Enemy_State::PERSEGUINT, Enemy_State::ATACANT, 0,
		[this, &player]() -> bool { return Transitions_Basic::Perseguir_Atacar(*this, App->player); });

	_stateMachine->AddTransition(Enemy_State::CERCANT, Enemy_State::PERSEGUINT,	0,
		[this, &player]() -> bool { return Transitions_Basic::Cerca_Perseguir(*this, App->player); });

	_stateMachine->AddTransition(Enemy_State::CERCANT, Enemy_State::PATRULLANT,	0,
		[this]() -> bool { return Transitions_Basic::Cerca_Patrulla(*this); });

	_stateMachine->AddTransition(Enemy_State::ATACANT, Enemy_State::PERSEGUINT,	1000,
		[&player]() -> bool { return Transitions_Basic::Atacar_Perseguir(*(App->player)); });

	_stateMachine->AddTransition(Enemy_State::ATACANT, Enemy_State::JOC_FINALITZAT,	1000,
		[&player]() -> bool { return Transitions_Basic::Atacar_Final(*(App->player)); });

}

void EnemyBasic::UpdateBehaviour(const ModulePlayer* player)
{
	HandleMove();

	_currState = _stateMachine->CheckTransitions(_currState);

	switch (_currState)
	{
	case PATRULLANT: {
		patrolPath.CheckReached(position);
		_currDirection = DirectionHelper::GetDirection(position, patrolPath.GetNext());
		if (position.DistanceTo(App->player->position) < _visionRange) {
			_aggro++;
		}
		break;
	}
	case PERSEGUINT: {
		_currDirection = ChangeDirection();

		break;
	}
	case ATACANT: {
		//iPoint dirVec = player->position - position;
		_currDirection = ChangeDirection();
		//Preparar i executar atac
		if (_attackStart == 0)
			_attackStart = SDL_GetTicks();
		else if (_collider != nullptr && (_attackStart + _attackDelay) <= SDL_GetTicks()) {
			//Si hi ha col·lisio despres del temps d'inici d'atac, el jugador ha mort
			if (_collider->Intersects(App->player->collider->rect))
				App->player->alive = false;
			_attackStart = 0;
		}
		break;
	}
	case CERCANT: {
		// Segueix Recte (si entra en aquest mode quan s'allunya del jugador, seguira allunyant-se tal com està ara
		_aggro--;
		break;
	}
	case BLOQUEJAT: {
		// No es mou (?)
		_aggro--;
		break;
	}
	case JOC_FINALITZAT: {
		_moving = false;
		break;
	}
	default:
		break;
	}
}
