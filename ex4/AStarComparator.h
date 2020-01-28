#ifndef FLIGHTSIMULATOR_ASTARCOMPARATOR_H
#define FLIGHTSIMULATOR_ASTARCOMPARATOR_H
#include "State.h"
//template <typename T>
class AStarComparator {
public:

	bool operator ()(State<std::pair<int,int>>* lhs, State<std::pair<int, int>>* rhs) {
		//return lhs->getCost() + manhatanDistance(lhs) > rhs->getCost()+ manhatanDistance(rhs);
		return lhs->getCost() + lhs->getHeuristicVal() > rhs->getCost() +rhs->getHeuristicVal();
	}
};
#endif