#include "PatrolPath.h"

#define IN_RANGE 50

void PatrolPath::PushBack(iPoint coords)
{
	steps.push_back(coords);
}

iPoint PatrolPath::GetNext()
{
	if (steps.size() == 0) { LOG("EMPTY PATROL PATH"); return {0, 0}; }
	if (pathDirection == -1) return steps[steps.size() - 1 - currentStep];
	else return steps[currentStep];
}

void PatrolPath::CheckReached(iPoint position)
{
	if (position.DistanceManhattan(steps[currentStep]) < IN_RANGE) {
		currentStep = 0;
		pathDirection = -pathDirection;
	}
}
