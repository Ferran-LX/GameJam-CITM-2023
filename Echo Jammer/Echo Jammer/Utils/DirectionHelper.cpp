#pragma once
#include "DirectionHelper.h"
#include "p2Point.h"

Directions DirectionHelper::GetDirection(iPoint vectorDir) {
	if (vectorDir.x == 0) {
		// Sol vertical
		if (vectorDir.y < 0) {
			return Directions::NORTH;
		}
		else {
			return Directions::SOUTH;
		}

	}
	else if (vectorDir.y == 0) {
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