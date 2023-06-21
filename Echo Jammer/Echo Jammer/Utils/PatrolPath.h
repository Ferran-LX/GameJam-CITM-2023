#pragma once
#include <vector>
#include "p2Point.h"



class PatrolPath {
public:
	void PushBack(iPoint coords);

	iPoint GetNext();

	void CheckReached(iPoint position);


	uint currentStep = 0;

	int pathDirection = 1;

	std::vector<iPoint> steps;
};