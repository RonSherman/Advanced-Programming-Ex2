#ifndef FLIGHTSIMULATOR_STATECOMPARATOR_H
#define FLIGHTSIMULATOR_STATECOMPARATOR_H
#include "State.h"
template <typename T>
class StateComparator{
	//false- means Best, true- is A*
	//private bool algo= false;
public:
	bool operator ()(State<T>* lhs, State<T>* rhs){
		return lhs->getCost() > rhs->getCost();
	}
};
#endif