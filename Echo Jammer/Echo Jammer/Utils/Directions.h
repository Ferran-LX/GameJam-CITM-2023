#pragma once

enum class Directions
{
	// Sentit del rellotge
	NONE,
	NORTH,
	NORTH_EAST,
	EAST,
	SOUTH_EAST,
	SOUTH,
	SOUTH_WEST,
	WEST,
	NORTH_WEST,

	DIRECTIONS_TOTAL
};

constexpr int DirToInt(Directions dir) {
	return static_cast<int>(dir);
}
