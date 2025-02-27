#pragma once
#include <functional>
#include <vector>
#include "../Modules/Gameplay/ModuleEnemies.h"

struct EnemyStateTransition {
	Enemy_State target;
	std::function<bool()> condition = nullptr;
	uint delay = 0;
	uint timer = 0;
};

struct EnemyStateMachine
{
public:

	void AddTransition(Enemy_State originState, Enemy_State destState, uint delay, std::function<bool()> condition);

	const std::vector<EnemyStateTransition> GetTransitions(Enemy_State state) const;

	Enemy_State CheckTransitions(Enemy_State currentState);

private:
	//Array que cont� vectors de transicions.
	std::vector<EnemyStateTransition> _transitions[Enemy_State::MAX_STATES];

};

