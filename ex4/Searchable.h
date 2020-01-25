#ifndef FLIGHTSIMULATOR_SEARCHABLE_H
#define FLIGHTSIMULATOR_SEARCHABLE_H

#include "State.h"
#include <vector>
template <typename T>
class Searchable {
protected:
	State<T>* initial;
	State<T>* goal;
public:
	virtual State<T>* getInitialState()=0;
	virtual State<T>* getGoalState() =0;
	//List<State<T>> getAllNeighbors(State<T> state)=0;
	virtual std::vector<State<T>*> getAllNeighbors(State<T>* state)=0;
	virtual int getMovingCost(State<T>* state)=0;

};
#endif