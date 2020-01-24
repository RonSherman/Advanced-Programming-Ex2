#ifndef FLIGHTSIMULATOR_STATE_H
#define FLIGHTSIMULATOR_STATE_H
#include <vector>
template <typename T>
class State {
protected:
	T state;
	double cost;
	State<T>* father;
public:
	State(T t) : state(t) {};
	virtual bool equals(State <T>* otherState) =0;
	double getCost() { return this->cost; };
	T* getState() { return &state; };
	virtual std::vector<State<T>*> backtrack()=0;
	State<T>* getFather() {return this->father;};
};
#endif