#include "EnemyBasic.h"
#include "../../Application/Application.h"
#include "../../Modules/Gameplay/ModulePlayer.h"
#include "../../Modules/Gameplay/ModuleEnemies.h"
#include "../../Utils/EnemyStateMachine.h"
#include "TransitionConditionsBasic.h"

EnemyBasic::EnemyBasic(int x_, int y_) : Enemy(x_, y_, Enemy_Type::BASIC)
{
	SetSpeed(5);
	InitStateMachine();
}

EnemyBasic::~EnemyBasic()
{
	delete _stateMachine;
}

void EnemyBasic::InitStateMachine()
{
	//Funció lambda, explicació breu
	// [] - conté les variables capturades (o sigui, les que es poden utilitzar a la funció lambda)
	// posar-hi '&' significa acces de només lectura a tot l'scope de la funció on es troba la definició de la lambda
	// especificar el nom dona accés a la variable amb aquell nom (es poden separar per comes)
	// -> bool es el valor que retorna la funció lambda
	// () - permet posar paràmetres, però en aquesta implementació no n'hi ha ja que s'utilitza de wrapper

	ModulePlayer* player = App->player;
	_stateMachine = new EnemyStateMachine();
	_stateMachine->AddTransition(Enemy_State::PATRULLANT, Enemy_State::PERSEGUINT,
		[this, &player]() -> bool { return Transitions_Basic::Patrulla_Perseguir(*this, player->position); });

	_stateMachine->AddTransition(Enemy_State::PERSEGUINT, Enemy_State::CERCANT,
		[this, &player]() -> bool { return Transitions_Basic::Perseguir_Cerca(*this, player->position); });

	_stateMachine->AddTransition(Enemy_State::CERCANT, Enemy_State::PERSEGUINT,
		[this, &player]() -> bool { return Transitions_Basic::Cerca_Perseguir(*this, player->position); });

	_stateMachine->AddTransition(Enemy_State::CERCANT, Enemy_State::PATRULLANT,
		[this]() -> bool { return Transitions_Basic::Cerca_Patrulla(*this); });

	_stateMachine->AddTransition(Enemy_State::PERSEGUINT, Enemy_State::ATACANT,
		[this, &player]() -> bool { return Transitions_Basic::Perseguir_Atacar(*this, player->position); });

	_stateMachine->AddTransition(Enemy_State::ATACANT, Enemy_State::PERSEGUINT,
		[&player]() -> bool { return Transitions_Basic::Atacar_Perseguir(*player); });

	_stateMachine->AddTransition(Enemy_State::ATACANT, Enemy_State::JOC_FINALITZAT,
		[&player]() -> bool { return Transitions_Basic::Atacar_Final(*player); });

}

void EnemyBasic::Update()
{
}

void EnemyBasic::OnCollision(Collider* collider)
{
}
