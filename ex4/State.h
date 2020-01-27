#ifndef FLIGHTSIMULATOR_STATE_H
#define FLIGHTSIMULATOR_STATE_H
#include <vector>
#include <iostream>
#include <string>
template <typename T>
class State {
protected:
	T state;
	double cost;
	State<T>* father;
	int movingCost;
public:
	State(T t) : state(t) {};
	virtual bool equals(State <T>* otherState) =0;
	double getCost() { return this->cost; };
	int getMovingCost() { return this->movingCost; };
	void setCost(double d) { this->cost = d; }
	T getState() { return state; };
	virtual std::vector<State<T>*> backtrack()=0;
	State<T>* getFather() {return this->father;};
	void setParent(State<T>* state) { this->father = state; }
	friend std::ostream& operator<<(std::ostream& os, const State& dt) {
		//os << cost;
	};
	virtual std::string toString()=0;
};
#endif