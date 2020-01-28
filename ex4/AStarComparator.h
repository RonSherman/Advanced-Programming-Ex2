#ifndef FLIGHTSIMULATOR_ASTARCOMPARATOR_H
#define FLIGHTSIMULATOR_ASTARCOMPARATOR_H
#include "State.h"
//template <typename T>
class AStarComparator {
	//false- means Best, true- is A*
	//private bool algo= false;

	//State<std::pair<int, int>>* goal;

public:
   // AStarComparator(State<std::pair<int, int>> *goal) : goal(goal) {}

	bool operator ()(State<std::pair<int,int>>* lhs, State<std::pair<int, int>>* rhs) {
		//return lhs->getCost() + manhatanDistance(lhs) > rhs->getCost()+ manhatanDistance(rhs);
		return lhs->getCost() + lhs->getHeuristicVal() > rhs->getCost() +rhs->getHeuristicVal();
	}
	//int manhatanDistance(State<std::pair<int, int>>* state) {
	//	return (abs(state->getState().first - goal->getState().first) +
	//	abs(state->getState().second - goal->getState().second));
//	}
};
#endif