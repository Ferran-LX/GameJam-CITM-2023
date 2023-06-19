#include "EnemyStateMachine.h"
#include "../../SDLs/SDL/include/SDL_timer.h"



void EnemyStateMachine::AddTransition(Enemy_State originState, Enemy_State destState, uint delay, std::function<bool()> condition)
{
	_transitions[originState].push_back({ destState, condition, delay });
}

const std::vector<EnemyStateTransition> EnemyStateMachine::GetTransitions(Enemy_State state) const
{
	return _transitions[state];
}

Enemy_State EnemyStateMachine::CheckTransitions(Enemy_State currentState)
{
	// Aquesta implementacio de temporitzador per a transicions no es molt bona, es pot millorar
	// La implementació actual nomes requereix que la condicio sigui true quan comença el temporitzador i quan ja ha passat el temps necessari
	for (EnemyStateTransition& t : _transitions[currentState]) {
		if (t.condition != nullptr && t.condition()) {
			if (t.delay == 0) {
				LOG("(NO-DELAY) Enemic ha canviat d'estat: %i -> %i", currentState, t.target);
				currentState = t.target;
				break;
			}
			else {
				// Hi ha delay
				if (t.timer == 0) {
					// Inicia temporitzador
					t.timer = SDL_GetTicks();
				}
				else if ((t.timer+t.delay) <= SDL_GetTicks()) {
					// Reinicia temporitzadors i acaba la transicio
					for (EnemyStateTransition& t : _transitions[currentState])
					{
						t.timer = 0;
					}
					LOG("(DELAY) Enemic ha canviat d'estat: %i -> %i", currentState, t.target);
					currentState = t.target;
				}
			}
		}
	}

	return currentState;
}
