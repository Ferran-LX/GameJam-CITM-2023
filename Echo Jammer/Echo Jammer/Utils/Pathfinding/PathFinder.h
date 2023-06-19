#pragma once
#include <vector>
#include "../p2Point.h"
#include "../Path.h"

class NodeBase;

class PathFinder {
public:

	PathFinder();

	void SetGridSize(int rows, int columns);

	std::vector<NodeBase*> FindPath(iPoint start, iPoint target);


private:

	//A_STAR_SEARCH _aStar;

};