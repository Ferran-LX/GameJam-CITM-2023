#include "EnemyBasic.h"
#include "TransitionConditionsBasic.h"
#include "../../Application/Application.h"
#include "../../Modules/Gameplay/ModulePlayer.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"
#include "../../Utils/EnemyStateMachine.h"
#include "../../Utils/Collider.h"
#include "../../Utils/p2Point.h"
#include "../../Utils/DirectionHelper.h"


EnemyBasic::EnemyBasic(int x_, int y_) : Enemy(x_, y_, Enemy_Type::BASIC)
{
	_speed = 5;
	_aggro = 0;
	_aggroMax = 50;
	_attackRange = 20;
	_visionRange = 270;
	_searchRange = 230;
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
		[this, &player]() -> bool { return Transitions_Basic::Patrulla_Perseguir(*this, App->player); });

	_stateMachine->AddTransition(Enemy_State::PERSEGUINT, Enemy_State::CERCANT,
		[this, &player]() -> bool { return Transitions_Basic::Perseguir_Cerca(*this, App->player); });

	_stateMachine->AddTransition(Enemy_State::PERSEGUINT, Enemy_State::ATACANT,
		[this, &player]() -> bool { return Transitions_Basic::Perseguir_Atacar(*this, App->player); });

	_stateMachine->AddTransition(Enemy_State::CERCANT, Enemy_State::PERSEGUINT,
		[this, &player]() -> bool { return Transitions_Basic::Cerca_Perseguir(*this, App->player); });

	_stateMachine->AddTransition(Enemy_State::CERCANT, Enemy_State::PATRULLANT,
		[this]() -> bool { return Transitions_Basic::Cerca_Patrulla(*this); });

	_stateMachine->AddTransition(Enemy_State::ATACANT, Enemy_State::PERSEGUINT,
		[&player]() -> bool { return Transitions_Basic::Atacar_Perseguir(*(App->player)); });

	_stateMachine->AddTransition(Enemy_State::ATACANT, Enemy_State::JOC_FINALITZAT,
		[&player]() -> bool { return Transitions_Basic::Atacar_Final(*(App->player)); });

}

void EnemyBasic::UpdateBehaviour(const ModulePlayer* player)
{
	HandleMove();

	_currState = _stateMachine->CheckTransitions(_currState);

	switch (_currState)
	{
	case PATRULLANT: {
		_currDirection = Directions::NONE;
		if (position.DistanceTo(App->player->position) < _visionRange) {
			_aggro++;
		}
		break;
	}
	case PERSEGUINT: {
		//TODO canviar per direcció de pathfinding
		iPoint dirVec = player->position - position;
		_currDirection = DirectionHelper::GetDirection(dirVec);

		break;
	}
	case ATACANT: {
		iPoint dirVec = player->position - position;
		_currDirection = DirectionHelper::GetDirection(dirVec);
		//Preparar i executar atac
		break;
	}
	case CERCANT: {
		// No es mou (?)
		_aggro--;
		break;
	}
	case BLOQUEJAT: {
		// No es mou (?)
		_aggro--;
		break;
	}
	case JOC_FINALITZAT: {

		break;
	}
	default:
		break;
	}
}
