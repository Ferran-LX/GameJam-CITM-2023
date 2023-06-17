#include "EnemyStateMachine.h"



void EnemyStateMachine::AddTransition(Enemy_State originState, Enemy_State destState, std::function<bool()> condition)
{
	_transitions[originState].push_back({ destState, condition });
}

const std::vector<EnemyStateTransition> EnemyStateMachine::GetTransitions(Enemy_State state) const
{
	return _transitions[state];
}

Enemy_State EnemyStateMachine::CheckTransitions(Enemy_State currentState)
{
	for (EnemyStateTransition t : _transitions[currentState]) {
		if (t.condition != nullptr && t.condition()) {
			currentState = t.target;
			break;
		}
	}

	return currentState;
}
