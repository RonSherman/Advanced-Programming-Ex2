#ifndef FLIGHTSIMULATOR_STATECOMPARATOR_H
#define FLIGHTSIMULATOR_STATECOMPARATOR_H
#include "State.h"
template <typename T>
class StateComparator{
	bool operator ()(const State<T>* lhs, const State<T>* rhs){
		return lhs->getCost() > rhs->getCost();
	}
};
#endif