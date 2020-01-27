#ifndef FLIGHTSIMULATOR_ASTARCOMPARATOR_H
#define FLIGHTSIMULATOR_ASTARCOMPARATOR_H
#include "State.h"
//template <typename T>
class AStarComparator {
	//false- means Best, true- is A*
	//private bool algo= false;
public:
	bool operator ()(State<std::pair<int,int>>* lhs, State<std::pair<int, int>>* rhs) {
		return lhs->getCost() + manhatanDistance(lhs) > rhs->getCost()+ manhatanDistance(rhs);
	}
	int manhatanDistance(State<std::pair<int, int>>* state) {
		//TODO fill it
		return 2;
	}
};
#endif