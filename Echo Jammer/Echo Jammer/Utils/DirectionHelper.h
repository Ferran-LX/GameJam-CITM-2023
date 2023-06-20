#pragma once
#include "Directions.h"
#include "p2Point.h"

class DirectionHelper {
public:

	// Retorna direcció tenint en compte eixos de moviment en SDL
	static Directions GetDirection(iPoint fromPoint, iPoint toPoint);

	static Directions GetOpposite(Directions dir);

};