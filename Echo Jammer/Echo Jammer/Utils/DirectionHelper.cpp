#pragma once
#include "DirectionHelper.h"
#include "p2Point.h"

#define DEADZONE 0.38

Directions DirectionHelper::GetDirection(iPoint fromPoint, iPoint toPoint) {

	iPoint iVec = toPoint - fromPoint;

	fPoint vectorDir = { (float)iVec.x,(float)iVec.y };
	vectorDir = vectorDir.Normalized();

	if (vectorDir.x <= DEADZONE && vectorDir.x >= -DEADZONE) {
		// Sol vertical
		if (vectorDir.y < 0) {
			return Directions::NORTH;
		}
		else {
			return Directions::SOUTH;
		}

	}
	else if (vectorDir.y <= DEADZONE && vectorDir.y >= -DEADZONE) {
		// Sol horitzontal
		if (vectorDir.x < 0) {
			return Directions::WEST;
		}
		else {
			return Directions::EAST;
		}
	}
	else {
		// Diagonals
		if (vectorDir.y < 0) {
			// North
			if (vectorDir.x < 0) {
				return Directions::NORTH_WEST;
			}
			else {
				return Directions::NORTH_EAST;
			}
		}
		else {
			// South
			if (vectorDir.x < 0) {
				return Directions::SOUTH_WEST;
			}
			else {
				return Directions::SOUTH_EAST;
			}
		}
	}
}