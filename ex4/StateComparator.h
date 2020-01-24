#ifndef FLIGHTSIMULATOR_STATECOMPARATOR_H
#define FLIGHTSIMULATOR_STATECOMPARATOR_H
#include "State.h"
template <typename T>
class StateComparator{
public:
	bool operator ()(State<T>* lhs, State<T>* rhs){
		return lhs->getCost() > rhs->getCost();
	}
};
#endif